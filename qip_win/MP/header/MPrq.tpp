// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPrq.tpp - RQ decomposition.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPrq.tpp
//! \brief	RQ decomposition
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_rq.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_rq.out

namespace MP {

//! \addtogroup lapack
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_rq:
//
// Compute an RQ factorization of a real M-by-N matrix A.
//
// This is a wrapper routine for the LAPACK functions DGERQF
// and DORGRQ.
//
// DGERQF computes an RQ factorization of a real M-by-N	matrix A:
// A = R * Q.
//
// DORGRQ generates an M-by-N real matrix Q with orthonormal rows,
// which is defined as the last M rows of a product of K elementary
// reflectors of order N
//
//       Q  =  H(1) H(2) . . . H(k)
//
// as returned by DGERQF.
//! \brief	Compute an RQ factorization of a real M-by-N matrix A.
//! \details	Compute an RQ factorization of a real M-by-N matrix A.
//!
//!		This is a wrapper routine for the LAPACK functions DGERQF
//!		and DORGRQ.
//!
//!		DGERQF computes an RQ factorization of a real M-by-N
//!		matrix A:  A = R * Q.
//!
//!		DORGRQ generates an M-by-N real matrix Q with
//!		orthonormal rows, which is defined as the last
//!		M rows of a product of K elementary reflectors
//!		of order N
//!
//!		Q  =  H(1) H(2) . . . H(k)
//!
//!		as returned by DGERQF.
//! \param[in]	A	- The M-by-N matrix A to factor.
//! \param[out]	R	- if M <= N, the upper triangle contains
//!			the M-by-M upper triangular matrix R;<br>
//!			if M >= N, the M-by-N upper trapezoidal
//!			matrix R;
//! \param[out]	Q	- The M-by-N matrix Q.
//
template<class T1, class T2, class T3>
inline int
MP_RQdcmp(const T1 &A, T2 &R, T3 &Q)
{
	integer	    M	  = A.rows();
	integer	    N	  = A.cols();
	integer	    K	  = MP_min(M, N);
	integer	    LDA	  = MP_max((integer) 1, M);
	doublereal *TAU;
	doublereal *WORK;
	integer	    LWORK = -1;
	doublereal  SIZE;
	integer	    INFO;
	integer	    i, j;

	assert(M >= 0 && N >= 0);

	// Transpose the input matrix to column-major order.
	T1 AT = A.transpose();

	// Allocate workspace.
	TAU  = new doublereal[K];
	dgerqf_(&M, &N, &AT[0], &LDA, TAU, &SIZE, &LWORK, &INFO);
	LWORK = static_cast<integer>(SIZE);
	WORK = new doublereal[LWORK];

	// Compute the RQ factorization of A.
	dgerqf_(&M, &N, &AT[0], &LDA, TAU, WORK, &LWORK, &INFO);

	// Check error condition.
	if(INFO < 0) {
		std::cerr << "dgerqf_: Illegal value at argument "
			  << MP_abs(INFO) << std::endl;
		return static_cast<int>(INFO);
	}

	if (M <= N) {
		// Extract R from the input/output matrix A.
		R.clear();
		for(i=0; i<M; ++i)
			for(j=i; j<M; ++j)
				R(i, j) = AT(N-M+j, i);

		// Reallocate workspace, if necessary.
		doublereal TMP = SIZE;	// Remember old workspace size
		LWORK = -1;		// Request a new size
		dorgrq_(&M, &N, &M, &AT[0], &LDA, TAU, &SIZE, &LWORK, &INFO);
		LWORK = (integer) SIZE;
		if(SIZE > TMP) {
			delete [] WORK;
			WORK = new doublereal[LWORK];
		}

		// Form Q.
		dorgrq_(&M, &N, &M, &AT[0], &LDA, TAU, WORK, &LWORK, &INFO);

		// Copy Q to the row-major output matrix.
		Q = AT.transpose();

	} else {	// M > N
		// Extract the M x N matrix R; transposed to row-major order.
		R = AT.transpose();

		// Zero below the (M - N)'th subdiagonal.
		for(i=M-N; i<M; ++i) {
			for(j=0; j<i-1; ++j) {
				R(i, j) = 0.0;
			}
		}

		// Extract the N x N matrix of elementary reflectors.
		MatrixN H(N, N);
		for(i=0; i<N; ++i)
			for(j=0; j<N; ++j)
				H(j, i) = AT(j, M-N+i);

		// Reallocate workspace, if necessary.
		doublereal TMP = SIZE;	// Remember old workspace size
		LWORK = -1;		// Request a new size
		dorgrq_(&N, &N, &N, &H[0], &N, TAU, &SIZE, &LWORK, &INFO);
		LWORK = (integer) SIZE;
		if(SIZE > TMP) {
			delete [] WORK;
			WORK = new doublereal[LWORK];
		}

		// Form Q.
		dorgrq_(&N, &N, &N, &H[0], &N, TAU, WORK, &LWORK, &INFO);

		// Check error condition.
		if(INFO < 0)
			std::cerr << "dorgrq_: Illegal value at argument "
				  << MP_abs(INFO) << std::endl;

		// Copy Q to the row-major output matrix.
		Q = H.transpose();
	}

	delete [] WORK;
	delete [] TAU;

	return static_cast<int>(INFO);
}
//@}

}	// namespace MP
