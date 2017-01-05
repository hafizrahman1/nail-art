// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPeigen.tpp - Eigenvalues/eigenvectors computation.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPeigen.tpp
//! \brief	Eigenvalues/eigenvectors computation.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_eigen.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_eigen.out

namespace MP {

//! \addtogroup lapack
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_eigenvalues:
//
// Compute the eigenvalues and eigenvectors of a real symmetric matrix A.
// The eigenvalues  are saved in ascending order in W.
// The eigenvectors are saved in ascending order in V.
// This is a wrapper routine for the CLAPACK function dsyev_
//! \brief	Compute eigenvalues and eigenvectors.
//! \details	Compute eigenvalues/eigenvectors of a real symmetric matrix A.
//!		The eigenvalues  are saved in ascending order in W.
//!		The eigenvectors are saved in ascending order in V.
//!		This is a wrapper routine for the LAPACK function DSYEV.
//! \param[in]	Matrix A - real symmetric input matrix.
//! \param[out]	Vector W - eigenvalues  in ascending order.
//! \param[out]	Vector V - eigenvectors in ascending order.
//! \return	Integer.
//
template<class T1, class T2, class T3>
inline int
MP_eigenvalues(const T1 &A, T2 &W, T3 &V)
{
	using namespace std;

	char    JOBZ  = 'V';
	char    UPLO  = 'U';
	integer N     = A.rows();
	integer LDA   = A.rows();
	integer LWORK = MP_max(MP_DEFAULT_WORKSPACE, (int) (3*N-1));
	integer INFO;

	// convert input matrix to column-major ordering (Fortran)
	MatrixN AT = A.transpose();

	// allocate workspace
	double *wk = new double[LWORK];

	// dispatch call to clapack
	dsyev_(&JOBZ, &UPLO, &N, &AT[0], &LDA, &W[0], wk, &LWORK, &INFO);

	// clean up workspace
	delete [] wk;

	// convert output matrix to row-major ordering (C/C++)
	V = AT.transpose();

	if(INFO < 0)
		cerr << "MP_eigenvalues: Invalid argument at index "
		     << (-INFO) << ".\n";
	else if(INFO > 0)
		cerr << "MP_eigenvalues: Failed to converge.\n";

	return ((int) INFO);
}
//@}

}	// namespace MP
