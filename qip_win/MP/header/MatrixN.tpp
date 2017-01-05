// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MatrixN.tpp - MxN matrix class implementation.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MatrixN.tpp
//! \brief	MxN matrix class implementation.
//! \author	George Wolberg and Gene Yu, 2015

namespace MP {

//! \addtogroup genericmatrix
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Template function to multiply two matrices of any type:  C = AB.
//! \brief	Multiply two matrices.
//! \details	This macro computes C=AB.
//!		Matrices A, B, C can be simple arrays, or objects of
//!		type MatrixN.  A, B, and C have dimensions
//!		L x M, M x N, and L x N, respectively.
//! \param[in]	A, B, C - Matrices.
//! \warning	This template is internal and should not be called directly.
//
template<class T1, class T2, class T3>
inline void
MP_matrixMultiply(const T1 &A, const T2 &B, T3& C)
{
	// get dimensions
	int r1 = A.rows();
	int c1 = A.cols();
	int c2 = B.cols();

	// init pointers
	const double *d1 = &A[0];
	const double *d2;
	      double *d3 = &C[0];

	// perform matrix multiplication: for all rows in A...
	double sum;
	for(int r=0; r<r1; r++) {
		// visit each column in B...
		for(int c=0; c<c2; c++) {
			d2 = &B[c];

			// multiply A row with B column
			sum = 0;
			for(int i=0; i<c1; i++) {
				sum += (d1[i] * *d2);
				d2  += c2;
			}
			*d3++ = sum;
		}

		// advance d1 to point to next A row
		d1 += c1;
	}
}
//@}

} // namespace MP
