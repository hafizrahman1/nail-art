// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPsvd.tpp - Singular value decomposition.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPsvd.tpp
//! \brief	Singular value decomposition
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_svd.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_svd.out

namespace MP {

//! \addtogroup lapack
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_svd:
//
// Compute the singular value decomposition of a real MxN matrix A,
// optionally computing the left and/or right singular vectors.
// This is a wrapper routine for CLAPACK function dgesvd_ 
//
// The SVD is written A=U(S)V^T, where
// S is an min(M,N)x1 column vector containing the singular values of A,
// U is an MxN orthogonal matrix, and
// V is an NxN orthogonal matrix.
// The singular values are real and non-negative, and are returned in
// descending order.  The first min(M,N) columns of U and V are the left
// and right singular vectors of A.
// NOTE: the function returns V^T, not V, following MATLAB.
// 
// If the econ flag is true, MP_svd uses the "economy size"
// version of DGESV.  Thus, U is m x n, S is n x n, and V is
// n x n, saving m(m-n) columns of U.
// The economy size version is only valid for m >= n, that is,
// for well-posed and overdetermined problems.
//
// Vector versions return a vector s containing N singular values arranged
// in descending order.
//! \brief 	Compute the singular value decomposition of a real
//!		MxN matrix A, optionally computing the left and/or
//!		right singular vectors.
//! \details	Compute the singular value decomposition of a real
//!		MxN matrix A, optionally computing the left and/or
//!		right singular vectors.
//!
//!		This is a wrapper routine for CLAPACK function dgesvd_ 
//!
//!		The SVD is written A=U(S)V^T, where
//!
//!		S is an min(M,N)-element column vector containing the
//!		singular values of A,
//!
//!		U is an MxN orthogonal matrix, and
//!
//!		V is an NxN orthogonal matrix.
//!
//!		The singular values are real and non-negative, and
//!		are returned in	descending order.  The first min(M,N)
//!		columns of U and V are the left and right singular
//!		vectors of A.
//!
//! \note	The function returns V^T, not V, following MATLAB.
//!
//!		If the econ flag is true, MP_svd uses the "economy size"
//!		version of DGESV.  Thus, U is m x n, S is n x n, and V is
//!		n x n, saving m(m-n) columns of U.
//!		The economy size version is only valid for m >= n, that is,
//!		for well-posed and overdetermined problems.
//!
//!		Vector versions return a vector s containing N
//!		singular values arranged in descending order.
//! \param[in,out]	A
//!		On entry, the M-by-N matrix A.<br>
//!		On exit, the contents of A are destroyed.
//! \param[out]	U On exit,
//!		<ul>
//!		<li>If econ = false, U contains the M-by-M orthogonal
//!		matrix U;</li>
//!		<li>if econ = true, U contains the first min(m,n) columns
//!		of U (the left singular vectors, stored columnwise);</li>
//!		</ul>
//! \param[out]	S	The singular values of A, sorted so that S(i) >= S(i+1).
//!		S can be either a vector with N elements or an N-by-N matrix.
//!		If S is a matrix, the singular values are returned along the diagonal.
//! \param[out] VT	On exit,
//!		<ul>
//!		<li>If econ = false, VT contains the N-by-N orthogonal
//!		matrix V**T;</li>
//!		<li>if econ = true, VT contains the first min(m,n)
//!		rows of V**T (the right singular vectors, stored rowwise);</li>
//!		</ul>
//! \param[in] econ	If true, use "economy size" version of DGESVD.
//
template<class T1, class T2, class T3, class T4>
inline int
MP_svd(const T1 &A, T2 &U, T3 &S, T4 &V, bool econ)
{
	char JOBU  = 'A';
	char JOBVT = 'A';

	integer M     = A.rows();
	integer N     = A.cols();
	integer LDA   = M;
	integer LDU   = M;
	integer LDVT  = N;
	integer LWORK = MP_max((integer) MP_SMALL_WORKSPACE,
			       MP_max(3*MP_min(M,N) + MP_max(M,N),
				      5*MP_min(M,N)));
	integer INFO;

	// convert to column-major ordering (Fortran)
	MatrixN AT = A.transpose();
	MatrixN UT;

	if (econ) {
		JOBU  = 'S';
		JOBVT = 'S';
		assert(U.rows() == M && U.cols() == N);
		UT.reserve(N, M);
	} else {
		assert(U.rows() == M && U.cols() == M);
		UT.reserve(M, M);
	}

	// allocate an array to hold the singular values
	VectorN s(N);

	// allocate workspace
	double *wk = new double[LWORK];

	// dispatch call to clapack
	dgesvd_(&JOBU, &JOBVT, &M, &N, &AT[0], &LDA, &s[0], &UT[0],
		&LDU, &V[0], &LDVT, wk, &LWORK, &INFO);

	delete [] wk;

	// convert back to row-major ordering (C/C++)
	U = UT.transpose();
	// V already transposed

	if(S.rows()==N && S.cols()==1) {	// S is a vector
		S = s;
	} else if(S.rows()==N && S.cols()==N) {	// S is a square matrix
		S.clear();
		MP_setDiag(s, S, 0);
	} else {			// the type of S is incompatible
		std::cerr << "MP_svd: S is neither N-by-1 nor N-by-N.\n";
	}

	if(INFO < 0)
		std::cerr << "MP_svd: Invalid argument at index "
			  << (-INFO) << ".\n";
	else if(INFO > 0)
		std::cerr << "MP_svd: Failed to converge.\n";

	return static_cast<int>(INFO);
}
//@}

}	// namespace MP
