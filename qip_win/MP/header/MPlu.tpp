// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPlu.tpp - LU decomposition.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPlu.tpp
//! \brief	LU decomposition.
//! \details	LU decomposition for solving systems of linear equations. 
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_lu.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_lu.out

namespace MP {

//! \addtogroup lapack
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_LUdcmp:
//
// Decompose square matrix A into LU lower and upper triangular matrices.
// Matrix L has 1's along its diagonal; Matrix U has a general diagonal.
// The LU decomposition overwrites A. Partial (implicit) pivoting is used.
//
// index is an output array (already allocated) that records the row
// permutation due to pivoting.
//
// The parity of the number of row interchanges is returned in d.
// Thus, d is set to +1 for an even number of row changes; -1 for odd.
// This is useful for determining the sign of the determinant, which
// can be efficiently computed from the LU decomposition.
//
// This is a wrapper routine for the LAPACK function dgetrf_
//! \brief	Decompose square matrix A into LU lower and upper
//!		triangular matrices
//! \details	Decompose square matrix <em>A</em> into LU lower and
//!		upper triangular matrices.  Matrix L has 1's along its
//!		diagonal; Matrix U has a general diagonal.  The LU
//!		decomposition overwrites <em>A</em>.  Partial pivoting
//!		is used.
//!
//!		<em>index</em> is an output array (already allocated) that
//!		records the row permutation due to pivoting.
//!
//!		The parity of the number of row interchanges is
//!		returned in <em>d</em>.  Thus, d is set to +1 for an
//!		even number of row changes; -1 for odd.  This is
//!		useful for determining the sign of the determinant,
//!		which can be efficiently computed from the LU
//!		decomposition.
//!
//!		This is a wrapper routine for the LAPACK function DGETRF.
//! \param[in,out]	A	Matrix to decompose.
//! \param[out]		index	Pivot matrix.
//! \param[out]		d	Row exchange parity.
//
template<class T1>
inline void
MP_LUdcmp(T1 &A, integer *index, double &d)
{
	integer M   = A.rows();		// # of rows
	integer N   = A.cols();		// # of columns
	integer K   = MP_min(M, N);	// square dimension 
	integer LDA = A.rows();		// leading dimension (rows)
	integer INFO;			// return value

	// convert to column-major form (Fortran)
	T1 AT = A.transpose();

	// dispatch call to LAPACK
	dgetrf_(&M, &N, &AT[0], &LDA, index, &INFO);

	if(INFO < 0) {		// illegal value
		fprintf(stderr, "dgetrf_: illegal value detected\n");
		return;
	} else if(INFO > 0) {	// singular matrix
		fprintf(stderr, "dgetrf_: singular matrix detected\n");
		return;
	}

	// convert back to row-major form (C/C++)
	A = AT.transpose();

	// compute parity
	d = 1.0;
	for(int i=0; i<K; i++) {
	     if(i != index[i] - 1)
		  d = -d;
	}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_LUbksb:
//
// Linear equation solution by LU backsubstitution. Solves AX=B.
// A is the LU decomposition of a square matrix.
// B contains a solution vector.
// The function will overwrite B with its corresponding solution vector X.
//! \brief	Compute an LU factorization of a general non-square matrix.
//! \details	Linear equation solution by LU backsubstitution.
//!		Solves AX=B.
//!
//!		A is the LU decomposition of a square matrix.
//!
//!		B contains right hand sides.
//!
//!		The function will overwrite B with its corresponding
//!		solution vector X.
//!
//!		This is a wrapper routine for the LAPACK function DGETRS.
//! \param[in]	   A	 LU matrix.
//! \param[in]	   index Pivot matrix.
//! \param[in,out] B	 On entry, the right hand side matrix B.<br>
//!			 On exit, the solution matrix X. The RHS matrix.
//
template<class T1, class T2>
inline void
MP_LUbksb(T1 &A, integer *index, T2 &B)
{
	using namespace std;

	assert(A.rows() == A.cols());	// A must be square

	char	TRANS	= 'N';		// no transpose
	integer N	= A.rows();	// the order of the matrix A
	integer NRHS	= B.cols();	// # of columns
	integer LDA	= A.rows();	// leading dimension (rows) of A
	integer LDB	= B.rows();	// leading dimension (rows) of B
	integer INFO;			// return value

	// convert to column-major form (Fortran)
	T1 AT = A.transpose();
	T2 BT = B.transpose();

	dgetrs_(&TRANS, &N, &NRHS, &AT[0], &LDA, index, &BT[0], &LDB, &INFO);

	if(INFO < 0) {		// illegal value
		fprintf(stderr, "dgetrs_: illegal value detected\n");
		return;
	}

	// convert back to row-major form (C/C++)
	B = BT.transpose();
}
//@}

}	// namespace MP
