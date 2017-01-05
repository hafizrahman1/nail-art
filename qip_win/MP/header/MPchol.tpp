// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPchol.tpp - Cholesky decomposition.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPchol.tpp
//! \brief	Cholesky decomposition.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_chol.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_chol.out

namespace MP {

//! \addtogroup lapack
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_choleskyDecomp:
//
// Cholesky factorization of A, a real symmetric positive definite matrix.
// The factorization has the form A=U^TU, where U is an upper triangular
// matrix and L is a lower triangular matrix.
// This is a wrapper routine for the CLAPACK function dpotrf_
//! \brief	Cholesky decomposition.
//! \details	Cholesky factorization of A, a real symmetric positive
//!		definite matrix. The factorization has the form
//!		\f[\mathbf A=\mathbf U^T\mathbf U,\f], where U is an
//!		upper triangular matrix and L is lower triangular.
//!		This is a wrapper routine for the CLAPACK function dpotrf_
//! \param[in]	 A - Input matrix.
//! \param[out]	CD - Output matrix.
//! \return	Integer.
//
template<class T1, class T2>
inline int
MP_choleskyDecomp(const T1 &A, T2 &CD)
{
	using namespace std;

	char    UPLO = 'U';
	integer N    = A.rows();
	integer LDA  = A.rows();
	integer INFO;

	// convert input matrix to column-major ordering (Fortran)
	MatrixN AT = A.transpose();

	// dispatch call to clapack
	dpotrf_(&UPLO, &N, &AT[0], &LDA, &INFO);

	// copy upper triangle to output using row-major ordering (C/C++)
	CD.clear();
	for(int i=0; i<N; i++)
	  for(int j=i; j<N; j++)
		  CD(i, j) = AT(j, i);

	// print an error message
	if(INFO < 0) {
		cerr << "MP_choleskyDecomp: illegal value at index "
		     << (-INFO) << ".\n";
	} else if(INFO > 0)
		cerr << "MP_choleskyDecomp: matrix is not positive definite.\n";

	return ((int) INFO);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_choleskySolve:
//
// Solve a system of linear equations AX=B, where A is a symmetric positive
// definite matrix. Use the Cholesky factorization A=U^T U computed by DPOTRF.
//! \brief	Cholesky solver.
//! \details	Solve the linear system AX=B by applying Cholesky
//!		factorization to A, a real symmetric positive
//!		definite square matrix. The factorization has the form
//!		\f[\mathbf A=\mathbf U^T\mathbf U,\f] where U is an
//!		upper triangular matrix and L is lower triangular.
//!		This is a wrapper routine for the CLAPACK function dpotrf_
//! \param[in]	A - NxN  input matrix.
//! \param[out]	B - NxN output matrix.
//! \return	Integer.
//
template<class T1, class T2>
inline int
MP_choleskySolve(const T1 &A, T2 &B)
{
	using namespace std;

	char     UPLO = 'U';
	integer	 N    = A.rows();
	integer  NRHS = B.cols();
	integer  LDA  = A.rows();
	integer  LDB  = B.rows();
	integer  INFO;

	// convert input matrices to column-major ordering (Fortran)
	MatrixN AT = A.transpose();
	MatrixN BT = B.transpose();

	// dispatch calls to LAPACK
	dpotrf_(&UPLO, &N, &AT[0], &LDA, &INFO);

	// print an error message
	if(INFO < 0) {
		cerr << "MP_choleskySolve: illegal value at index "
		     << (-INFO) << ".\n";
		return static_cast<int>(INFO);
	} else if(INFO > 0) {
		cerr << "MP_choleskySolve: matrix is not positive definite.\n";
		return static_cast<int>(INFO);
	}

	dpotrs_(&UPLO, &N, &NRHS, &AT[0], &LDA, &BT[0], &LDB, &INFO);

	// convert output matrix to row-major ordering (C/C++)
	B = BT.transpose();

	// print an error message
	if(INFO < 0)
		cerr << "MP_choleskySolve: " << "illegal value at index "
		     << (-INFO) << ".\n";

	return static_cast<int>(INFO);
}
//@}

}	// namespace MP
