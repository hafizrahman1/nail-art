// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPgauss.tpp - Gauss-Jordan and Gaussian elimination.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MPgauss.tpp
//! \brief	Gauss-Jordan and Gaussian elimination.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_gauss.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_gauss.out

namespace MP {

//! \addtogroup solvers
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_GaussJordan:
//
// Linear equation solution by Gauss-Jordan elimination with full pivoting.
// The function will overwrite A with its inverse and solve AX=B for X,
// storing its corresponding set of solution vectors in X.
// The dimension of the square matrix A is n.
// The number of solutions in X is m.
//! \brief	Linear equation solution by Gauss-Jordan elimination
//!		with full pivoting.
//! \details	Linear equation solution by Gauss-Jordan elimination
//!		with full pivoting.  The function will overwrite A with
//!		its inverse and solve AX=B for X, storing its
//!		corresponding set of solution vectors in X.
//!
//!		The dimension of the square matrix A is n.
//!
//!		The number of solutions in X is m.<br>
//! \param[in,out] A	- On input, the matrix A;
//!			  on output, the inverse of A.
//! \param[in]	   B	- right hand sides
//! \param[out]	   X	- solution vectors
//
template<class T1, class T2, class T3>
inline void
MP_GaussJordan(T1 &A, T2 &B, T3 &X)
{
	// error checking
	assert(A.rows() == A.cols() && A.rows() == B.rows());
	int n = A.cols();
	int m = B.cols();

	X = B;

	double *p1 = &A[0];
	double *p2 = &X[0];

	// handle special case: A is a 1x1 matrix
	if(n == 1) {
		if(*p1 == 0) {	// couldn't find nonzero pivot
			std::cerr << "MP_GaussJordan: Singular Matrix\n";
			return;
		}
		for(int col=0; col<m; col++) p2[col] /= *p1;
		*p1 = 1.0 / *p1;
		return;
	}

	// allocate arrays necessary for full pivoting bookkeeping
	int *buf = new int[3*n];
	int *col_indx = buf;
	int *row_indx = buf +  n ;
	int *pivotflg = buf + 2*n;

	// clear pivot flag
	for(int i=0; i<n; i++) pivotflg[i] = 0;

	// perform n iterations of pivoting over all A columns
	double  *d1, *d2, r, big, pivinv;
	int irow=0, icol=0;
	for(int i=0; i<n; i++) {
	     big = 0;
	     // find the biggest pivot element in A
	     for(int row=0; row<n; row++) {
		  if(!pivotflg[row]) { // only unused pivots
		  for(int col=0; col<n; col++) {
			if(!pivotflg[col]) {
				d1 = &p1[row*n + col];
				if(MP_abs(*d1) > big) {
					big  = MP_abs(*d1);
					irow = row;
					icol = col;
				 }
			}
		  }
		}
	     }

	     if(big == 0) {	// couldn't find nonzero pivot
		std::cerr << "MP_GaussJordan: Singular Matrix\n";
		return;
	     }

	     pivotflg[icol]++; // else, mark pivot as being used

	     // swap rows to put this pivot on diagonal
	     if(irow != icol) {
		// process coefficient matrix
		d1 = &p1[irow*n];
		d2 = &p1[icol*n];
		for(int col=0; col<n; col++) MP_swap(d1[col], d2[col]);

		// process solution vectors
		d1 = &p2[irow*m];
		d2 = &p2[icol*m];
		for(int col=0; col<m; col++) MP_swap(d1[col], d2[col]);
	     }

	     row_indx[i] = irow;
	     col_indx[i] = icol;

	     // divide the row by the pivot
	     d1 = &p1[icol*n];
	     d2 = &p2[icol*m];
	     pivinv  = 1.0 / d1[icol];
	     d1[icol]=1.0;	// pivot=1 to avoid roundoff error
	     for(int col=0; col<n; col++) d1[col] *= pivinv;
	     for(int col=0; col<m; col++) d2[col] *= pivinv;

	     // fix the other rows by subtracting
	     for(int row=0; row<n; row++) {
		  if(row != icol) {
		  	// process coefficient matrix
			d1 = &p1[ row*n];
			d2 = &p1[icol*n];
			r  =  d1[icol];
			d1[icol]=0.0;
			for(int col=0; col<n; col++)
				d1[col] -= d2[col]*r;

			// process solution vectors
			d1 = &p2[ row*m];
			d2 = &p2[icol*m];
			for(int col=0; col<m; col++)
				d1[col] -= d2[col]*r;
		  }
	     }
	}

	// done with reduction over columns; unscramble
	// solution due to column interchanges. This is done
	// by interchanging pairs of columns in the reverse
	// order that the permutation was built.
	for(int i=n-1; i>=0; i--) {
	     if(row_indx[i] != col_indx[i]) {
		  d1 = &p1[row_indx[i]];
		  d2 = &p1[col_indx[i]];
		  for(int row=0; row<n; row++) {
			 MP_swap(*d1, *d2);
			 d1 += n;
			 d2 += n;
		  }
	     }
	}
	delete [] buf;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_GaussElimination:
//
// Linear equation solution by Gaussian elimination with partial pivoting.
// The function will overwrite A (after forward substitution) and solve
// AX=B for X, storing its corresponding set of solution vectors in X.
// The dimension of the square matrix A is n.
// The number of solutions in X is m.
//! \brief	Linear equation solution by Gaussian elimination
//!		with partial pivoting.
//! \details	Linear equation solution by Gaussian elimination
//!		with partial pivoting.  The function will overwrite A
//!		(after forward substitution) and solve AX=B for X,
//!		storing its corresponding set of solution vectors in X.
//!
//!		The dimension of the square matrix A is n.
//!
//!		The number of solutions in X is m.
//! \param[in,out] A	- On input, the matrix A;
//!			  on output, A is destroyed.
//! \param[in]	   B	- right hand sides
//! \param[out]	   X	- solution vectors
//
template<class T1, class T2, class T3>
inline void
MP_GaussElimination(T1 &A, T2 &B, T3 &X)
{
	// error checking
	assert(A.rows() == A.cols() && A.rows() == B.rows());
	int n = A.cols();
	int m = B.cols();

	int col;

	// copy B to X; will overwrite X with solution
	X = B;

	double *p1 = &A[0];
	double *p2 = &X[0];

	// handle special case: A is a 1x1 matrix
	if(n == 1) {
		if(*p1 == 0) {	// couldn't find nonzero pivot
			std::cerr << "MP_GaussElimination: "
				  << "Singular Matrix\n";
			return;
		 }
		 for(col=0; col<m; col++) p2[col] /= *p1;
		*p1 = 1.0 / *p1;
		 return;
	}

	// visit each column in A
	double *d1, *d2, r, sum;
	for(col=0; col<n-1; col++) {
		int pivot = col; // default: pivot is diag. element

		d1 = &p1[(pivot)*n + col];
		d2 = &p1[(col+1)*n + col];

		// visit all column elements below diag to find pivot
		for(int row=col+1; row<n; row++) {
			if(MP_abs(*d1) < MP_abs(*d2)) {
				pivot = row;
				d1 = &p1[(pivot)*n + col];
			}
			d2 += n;
		}

		// check if pivot is nonzero
		if(*d1 == 0) {
			std::cerr << "MP_GaussElimination: "
				  << "Singular Matrix\n";
			return;
		}

		// swap rows, if necessary, to put pivot on diagonal
		if(pivot != col) {
			// process coefficient matrix
			d1 = &p1[pivot*n];
			d2 = &p1[  col*n];
			for(int i=0; i<n; i++) MP_swap(d1[i], d2[i]);

			// process solution vectors
			d1 = &p2[pivot*m];
			d2 = &p2[  col*m];
			for(int i=0; i<m; i++) MP_swap(d1[i], d2[i]);
		}

		// forward elimination
		for(int row=col+1; row<n; row++) { // below-diag rows
			d1 = &p1[row*n];  // row to be reduced
			d2 = &p1[col*n];  // row containing pivot
			if(d1[col]) {	  // eliminate row
				// process coefficient matrix
				r = d1[col] / d2[col];
				d1[col] = 0;
				for(int i=col+1; i<n; i++)
				d1[i] -= (d2[i] * r);

				// process solution vectors
				d1 = &p2[row*m];
				d2 = &p2[col*m];
				for(int i=0; i<m; i++)
				     d1[i] -= (d2[i] * r);
			}
		}
	}

	// backward substitution
	for(int row=n-1; row>=0; row--) {
		d1 = &p1[row*n];

		// process all solution vectors
		for(int i=0; i<m; i++) {
			d2  = &p2[(n-1)*m + i];
			sum =  p2[ row *m + i];
			for(col=n-1; col>row; col--) {
				sum -= d1[col]* *d2;
				d2  -= m;
			}
			*d2 = sum / d1[col];
		}
	}
}

//@}

}	// namespace MP
