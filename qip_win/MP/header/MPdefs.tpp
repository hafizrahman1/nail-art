// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPdefs.tpp - Implementation file for MP symbolic constants
//		(#defines) and globals.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file       MPdefs.tpp
//! \brief      Implementation file for MP symbolic constants
//!		(#defines) and globals.
//! \author     George Wolberg and Gene Yu, 2015

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Math functions:
// MP_abs:	Return absolute value.
// MP_cbrt:	Return cube root.
// MP_isZero:	Return TRUE if input is less than MP_EPSILON.
// MP_sgn:	Return sign of input (+1, -1, or 0).
// MP_round:	Round  input to nearest integer.
// MP_floor:	Round  input to nearest integer towards -infinity.
// MP_ceil:	Round  input to nearest integer towards +infinity.
// MP_clip:	Clip   input to lie between l and h.
// MP_max:	Return maximum value of the two inputs.
// MP_min:	Return minimum value of the two inputs.
// MP_swap:	Swap the values of the two inputs.
//! \defgroup math MP: Math Functions
//@{

//! \brief Return absolute value.
template<class T>
inline T
MP_abs(const T &a)
{
	return (a>=0 ? a : -a);
}

//! \brief Return cube root.
template<class T>
inline T
MP_cbrt(const T &a)
{
	return (a>=0) ? exp(log(a)/3.0) : -exp(log(-a)/3.0);
}

//! \brief Return TRUE if input is less than MP_EPSILON.
template<class T>
inline T
MP_isZero(const T &a)
{
	return (MP_abs(a) < MP_EPSILON);
}

//! \brief Return sign of input (+1, -1, or 0).
template<class T>
inline int
MP_sgn(const T &a)
{
	return (a>0 ? 1 : (a<0 ? -1 : 0));
}

//! \brief Round input to nearest integer.
template<class T>
inline T
MP_round(const T &a)
{
	return ((T) (a>=0 ? (int)(a+.5) : -(int)(.5-a)));
}

//! \brief Round input to nearest integer towards -infinity.
template<class T>
inline T
MP_floor(const T &a)
{
	return ((T) (a==(int)a ? (int)a : a>0 ? (int)a : (int)a-1));
}

//! \brief Round input to nearest integer towards +infinity.
template<class T>
inline T
MP_ceiling(const T &a)
{
	return ((T) (a==(int)a ? (int)a : a>0 ? (int)a+1:(int)a));
}

//! \brief Clip input to lie between l and h.
template<class T>
inline T
MP_clip(const T &a, const T &l, const T &h)
{
	return (a<=l ? l : a<=h ? a : h);
}

//! \brief Return maximum value of the two inputs.
template<class T>
inline T
MP_max(const T &a, const T &b)
{
	return (a>b ? a : b);
}

//! \brief Return minimum value of the two inputs.
template<class T>
inline T
MP_min(const T &a, const T &b)
{
	return (a<b ? a : b);
}

//! \brief Swap the values of two variables of any type.
template<class T>
inline void
MP_swap(T &a, T &b)
{
	T t=a;
	a = b;
	b = t;
}

//! \brief Swap the values of two integers.
// int version: exploit binary representation of ints
inline void
MP_swap(int &a, int &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}
//@}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Get/set functions for diagonals, rows, and columns.
//
//! \defgroup genericmatrix MP: Generic Matrix Procedures
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a diagonal of matrix A, with offset d from the central diagonal,
// into vector u.
//! \brief	Copy a matrix diagonal into a vector.
//! \details	Copy a diagonal of matrix A, with offset d from the
//!		central diagonal, into vector u.
//! \param[in]	A - Input matrix.
//! \param[in]	d - An offset from the central diagonal.
//! \param[out]	u - The output vector that holds the diagonal.
//
template<class T1, class T2>
inline void
MP_getDiag(const T1& A, int d, T2& u)
{
	int i, max;
	int l = A.rows();		// get # of rows
	int m = A.cols();		// get # of columns
	int n = u.size();		// get vector size
	if(d >= 0) {			// non-negative row index
		assert(d < l);		// diagonal must exist
		max = MP_min(m-d, n);	// # of elements to copy
	} else {			// negative row index
		assert(MP_abs(d) < l);	// diagonal must exist
		max =  MP_min(l+d,n);	// # of elements to copy
		d = -d*m;		// advance to row
	}
	const double *p = &A[d];	// ptr to diagonal
	for(i=0; i<l; i++, p+=(m)+1) {
		if(i >= max) break;
		u[i] = *p;		// copy element
	}
	for(; i<n; i++) u[i] = 0;	// pad with trailing 0's
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a vector u into a diagonal of matrix A, with offset d from the
// central diagonal.
//! \brief	Copy a vector into a matrix diagonal.
//! \details	Copy vector u into a diagonal of matrix A, with offset
//!		d from the central diagonal.
//! \param[in]	u - The input vector that holds the new diagonal elements.
//! \param[in,out] A - Square matrix.
//! \param[in]	d - An offset from the central diagonal.
//
template<class T1, class T2>
inline void
MP_setDiag(const T1& u, T2& A, int d)
{
	int i, max;
	int l = A.rows();		// get # of rows
	int m = A.cols();		// get # of columns
	int n = u.size();		// get vector size
	if(d >= 0) {			// non-negative row index
		assert(d < l);		// diagonal must exist
		max = MP_min(m-d, n);	// # of elements to copy
	} else {			// negative row index
		assert(MP_abs(d) < l);	// diagonal must exist
		max =  MP_min(l+d,n);	// # of elements to copy
		d = -d*m;		// advance to row
	}
	double *p = &A[d];	// ptr to diagonal
	for(i=0; i<l; i++, p+=m+1) {
		if(i >= max) break;
		*p = u[i];		// copy element
	}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a row of matrix A, with offset row from the top, into vector u.
//! \brief	Copy a matrix row into a vector.
//! \details	Copy row of matrix A into vector u.
//! \param[in]	A - Input matrix.
//! \param[in]	row - Row index into matrix A.
//! \param[out]	u - The output vector that holds the row.
//
template<class T1, class T2>
inline void
MP_getRow(const T1& A, int row, T2& u)
{
	int i;
	int m = A.cols();				// get # of columns
	int n = u.size();				// get vector size
	assert(row>=0 && row<A.rows());	// row must exist
	const double *p = &A[row*m];	// get a ptr to row
	for(i=0; i<MP_min(m, n); ++i, p++)
		u[i] = *p;					// copy element
	for(; i<n; ++i) u[i] = 0;		// pad with 0's
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a vector u into a row of matrix A, with offset row from the top.
//! \brief	Copy a vector into a matrix row.
//! \details	Copy vector u into row row of matrix A.
//! \param[in]	u - The input vector that holds the new row elements.
//! \param[in,out] A - Matrix.
//! \param[in]	row - Row index into matrix A.
//
template<class T1, class T2>
inline void
MP_setRow(const T1& u, T2& A, int row)
{

	int m = A.cols();				// get # of columns
	int n = u.size();				// get vector size
	assert(row>=0 && row<A.rows());	// row must exist
	double *p = &A[row*m];			// get a ptr to row
	for(int i=0; i<MP_min(m, n); ++i, p++)
		*p = u[i];					// copy element
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a column of matrix A, with offset col from the left, into vector u.
//! \brief	Copy a matrix column into a vector.
//! \details	Copy column col of matrix A into vector u.
//! \param[in]	A - Input matrix.
//! \param[in]	col - Column index into matrix A.
//! \param[out]	u - The output vector that holds the column.
//
template<class T1, class T2>
inline void
MP_getCol(const T1& A, int col, T2& u)
{
	int i;
	int l = A.rows();		// get # of rows
	int m = A.cols();		// get # of columns
	int n = u.size();		// get vector size
	assert(col>=0 && col<m);	// column must exist
	const double *p = &A[col];	// get a ptr to column
	for(i=0; i<MP_min(l, n); i++, p+=m)
		u[i] = *p;		// copy element
	for(; i<n; i++) u[i] = 0;	// pad with 0's
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copy a vector u into a column of matrix A, with offset col from the left.
//! \brief	Copy a vector into a matrix column.
//! \details	Copy vector u into column col of matrix A
//! \param[in]	u - The input vector that holds the new column elements.
//! \param[in,out] A - Matrix.
//! \param[in]	col - Column index into matrix A.
//
template<class T1, class T2>
inline void
MP_setCol(const T1& u, T2& A, int col)
{
	int l = A.rows();		// get # of rows
	int m = A.cols();		// get # of columns
	int n = u.size();		// get vector size
	assert(col>=0 && col<m);	// column must exist
	double *p = &A[col];		// get a ptr to column
	for(int i=0; i<MP_min(l, n); i++, p+=m)
		*p = u[i];		// copy element
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_swapRows:
//
// Swap rows i and j in matrix A.
//! \brief	Swap rows.
//! \details	Swap rows i and j in m x n matrix.
//! \param[in]	A - m x n matrix.
//! \param[in]	i, j - row indices.
//
template<class T>
inline void
MP_swapRows(T &A, int i, int j)
{
	// trivial case
	if(i == j) return;

	// error checking
	assert(i >= 0 && i < A.rows());
	assert(j >= 0 && j < A.rows());

	// swap row i with row j across all k columns
	for(int k=0; k<A.cols(); k++)
		MP_swap(A(i, k), A(j, k));
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_swapCols:
//
// Swap columns i and j in matrix A.
//! \brief	Swap columns.
//! \details	Swap columns i and j in m x n matrix.
//! \param[in]	A - m x n matrix.
//! \param[in]	i, j - column indices.
//
template<class T>
inline void
MP_swapCols(T &A, int i, int j)
{
	// trivial case
	if(i == j) return;

	// error checking
	assert(i >= 0 && i < A.cols());
	assert(j >= 0 && j < A.cols());

	// swap column i with column j across all k rows
	for(int k=0; k<A.rows(); k++)
		MP_swap(A(k, i), A(k, j));
}
//@}

}	// namespace MP
