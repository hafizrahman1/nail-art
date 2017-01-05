// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPqr.tpp - QR decomposition.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPqr.tpp
//! \brief	QR decomposition
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_qr.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_qr.out

namespace MP {

//! \addtogroup lapack
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_qr:
//
// Compute a QR factorization of a real M-by-N matrix A.
//
// This is a wrapper routine for the LAPACK functions DGEQRF
// and DORGQR.
//
// DGEQRF computes a QR factorization of a real M-by-N matrix A:
// A = Q * R.
//
// DORGQR generates an M-by-N real matrix Q with orthonormal columns,
// which is defined as the first N columns of a product of K elementary
// reflectors of order M
//
//        Q  =  H(1) H(2) . . . H(k)
//
// as returned by DGEQRF.
//! \brief	Compute a QR factorization of a real M-by-N matrix A
//! \details	Compute a QR factorization of a real M-by-N matrix A.
//!
//!		This is a wrapper routine for the LAPACK functions
//!		DGEQRF and DORGQR.
//!
//!		DGEQRF computes a QR factorization of a real M-by-N
//!		matrix A:  A = Q * R.
//!
//!		DORGQR generates an M-by-N real matrix Q with
//!		orthonormal columns, which is defined as the first N
//!		columns of a product of K elementary reflectors of
//!		order M
//!
//!		       Q  =  H(1) H(2) . . . H(k)
//!
//!		as returned by DGEQRF.
//! \param[in]	A	- The M-by-N matrix A to factor.
//! \param[out]	Q	- The M-by-N matrix Q.
//! \param[out]	R	- The min(M,N)-by-N upper trapezoidal matrix
//!			(The R is upper triangular if m >= n).
//
template<class T1, class T2, class T3>
inline int
MP_QRdcmp(const T1 &A, T2 &Q, T3 &R)
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
	int	    i, j;

	assert(M >= N);

	T1 AT = A.transpose();

	// Allocate workspace
	TAU  = new doublereal[K];
	dgeqrf_(&M, &N, &AT[0], &LDA, TAU, &SIZE, &LWORK, &INFO);
	LWORK = (integer) SIZE;
	WORK = new doublereal[LWORK];

	// Compute the QR factorization of A
	dgeqrf_(&M, &N, &AT[0], &LDA, TAU, WORK, &LWORK, &INFO);

	// Check error condition
	if(INFO < 0) {
		std::cerr << "dgeqrf_: Illegal value at argument "
			  << MP_abs(INFO) << std::endl;
		return static_cast<int>(INFO);
	}

	// Store R and replace it with TAU on the diagonal + zeroes
	R.clear();
	for(i=0; i<K; ++i) {
		for(j=i; j<N; ++j) {
			R (i, j) = AT(j, i);
			AT(j, i) = j > i ? 0 : TAU[i];
		}
	}

	// Reallocate workspace, if necessary
	doublereal TMP = SIZE;	// Remember old workspace size
	LWORK = -1;		// Request a new size
	dorgqr_(&M, &N, &K, &AT[0], &LDA, TAU, &SIZE, &LWORK, &INFO);
	LWORK = (integer) SIZE;
	if(SIZE > TMP) {
		delete [] WORK;
		WORK = new doublereal[LWORK];
	}

	// Form Q
	dorgqr_(&M, &N, &K, &AT[0], &LDA, TAU, WORK, &LWORK, &INFO);

	// Check error condition
	if(INFO < 0)
		std::cerr << "dorgqr_: Illegal value at argument "
			  << MP_abs(INFO) << std::endl;

	// Copy Q to output
	Q = AT.transpose();

	delete [] WORK;
	delete [] TAU;

	return static_cast<int>(INFO);
}
//@}

}	// namespace MP
