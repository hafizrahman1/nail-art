// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPband.tpp - Solver for tridiagonal systems of equations.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPband.tpp
//! \brief	Solver for tridiagonal and band-diagonal systems of equations.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_band.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_band.out

namespace MP {

//! \addtogroup solvers
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_tridiagonal:
//
// Solve tridiagonal system of equations.
// Given Ax=b, where A is a square tridiagonal matrix and b is the
// RHS vector, find the vector x in linear time and copy it back into b.
//! \brief	Solve tridiagonal system of equations.
//! \details	Given Ax=B, where A is a tridiagonal matrix and
//!		B is the RHS vector, solve for the vector x.
//!		Solution will be stored in B.
//! \param[in]	A - N x 3 matrix containing the 3 tridiagonal bands:
//!		sub-diagonal, diagonal, and super-diagonal.
//! \param[in,out] B - RHS vector that will be overwritten with solution.
//
template<class T1, class T2>
inline void
MP_tridiagonal(T1 &A, T2 &B)
{
	double	*b, *c, *r, pivot;
	int	 i;

	int n = A.rows();

	// C stores the scaled super-diag for backsubstitution
	double *C = new double[n];

	// space for the three bands to be stored in row-order
	double *a = new double[n*3];
	b = &a[n];
	c = &b[n];

	// init arrays a, b, and c with the three bands
	r = &A[0];
	for(i=0; i<n; i++) {
		a[i] = *r++;		// sub-diagonal
		b[i] = *r++;		//     diagonal
		c[i] = *r++;		// super-diag
	}
	r = &B[0];			// RHS

	if(b[0] == 0) {
	 	// should rewrite equations as a set of order N-1,
		// with r[1] trivially eliminated
		std::cerr << "MP_tridiagonal: triv. soln for RHS[1]\n";
		return;
	}

	// forward substitution
	r[0] = r[0] / (pivot = b[0]);
	for(i=1; i<n; i++) {
		C[i]  = c[i-1] / pivot;
		pivot = b[i] - a[i]*C[i];
		if(pivot == 0) {
			std::cerr << "MP_tridiagonal: zero pivot\n";
			return;
		}
		r[i] = (r[i] - a[i]*r[i-1]) / pivot;
	}

	// backsubstitution
	for (i=n-2; i>=0; i--) r[i] -= (C[i+1] * r[i+1]);

	delete [] C;
	delete [] a;
}
//@}

}	// namespace MP
