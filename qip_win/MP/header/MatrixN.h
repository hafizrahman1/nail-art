// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MatrixN.h - M x N matrix class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	MatrixN.h
//! \brief	M x N matrix class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::MatrixN
//! \brief	M x N matrix class.
//! \details	The MatrixN class represents M x N matrices of
//!		type double that may be resized dynamically.
//!
//! <b>Example:</b>
//! \verbinclude example_matrixN.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_matrixN.out

#ifndef MATRIXN_H
#define MATRIXN_H

#include "MPdefs.h"

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MatrixN class declaration
// This matrix class may be resized dynamically.
//
class MatrixN {
public:
	MatrixN();				// default constructor
	MatrixN(const MatrixN &);		// copy constructor
	MatrixN(int, int);			// zero constructor
	MatrixN(const double *, int, int);	// array constructor

	// component constructor: set elements to form a 3x3 matrix
	MatrixN(const double &, const double &, const double &,
		const double &, const double &, const double &,
		const double &, const double &, const double &);

	// component constructor: set elements to form a 4x4 matrix
	MatrixN(const double &, const double &, const double &, const double &,
		const double &, const double &, const double &, const double &,
		const double &, const double &, const double &, const double &,
		const double &, const double &, const double &, const double &);

	// destructor
	~MatrixN();

	// public methods
	int      size	  () const;		// number of elements
	int      rows	  () const;		// number of rows
	int      cols	  () const;		// number of columns
	double	 norm2	  () const;		// squared Frobenius norm
	double	 norm	  () const;		// Frobenius norm
	MatrixN  transpose() const;		// matrix transpose
	MatrixN &clear	  ();			// clear matrix
	void	 reserve  (int, int);		// allocate matrix memory 
	void     resize	  (int, int);		// resize matrix
	void	 identity ();			// identity matrix
	void	 normalizeRow();		// row-by-row normalization

	// array index operators (for 1D arrays)
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i, int j) const;
	double	     &operator()(int i, int j);

	// assignment operators
	MatrixN &operator= (const MatrixN &);	// copy
	MatrixN &operator+=(const MatrixN &);	// addition
	MatrixN &operator-=(const MatrixN &);	// subtraction
	MatrixN &operator*=(const double  &);	// scalar multiplication
	MatrixN &operator*=(const MatrixN &);	// pre-multiplication
	MatrixN &operator/=(const double  &);	// scalar division

	// type cast operators
	operator Vector2() const;		// cast to 2D vector
	operator Vector3() const;		// cast to 3D vector
	operator Vector4() const;		// cast to 4D vector
	operator VectorN() const;		// cast to nD vector
	operator Matrix3() const;		// cast to 3x3 matrix
	operator Matrix4() const;		// cast to 4x4 matrix

private:
	int	 m_rows;			// number of rows
	int	 m_cols;			// number of columns
	double	*m_matrix;			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern MatrixN	operator+ (const MatrixN &A, const MatrixN &B);
extern MatrixN	operator- (const MatrixN &A);
extern MatrixN	operator- (const MatrixN &A, const MatrixN &B);
extern MatrixN	operator* (const MatrixN &A, const  double &k);
extern MatrixN	operator* (const  double &k, const MatrixN &A);
extern MatrixN	operator/ (const MatrixN &A, const  double &k);

extern VectorN	operator* (const MatrixN &A, const VectorN &u);
extern VectorN	operator* (const MatrixN &A, const Vector4 &u);
extern VectorN	operator* (const MatrixN &A, const Vector3 &u);
extern VectorN	operator* (const MatrixN &A, const Vector2 &u);
extern VectorN	operator* (const VectorN &u, const MatrixN &A);
extern VectorN	operator* (const Vector4 &u, const MatrixN &A);
extern VectorN	operator* (const Vector3 &u, const MatrixN &A);
extern VectorN	operator* (const Vector2 &u, const MatrixN &A);
extern MatrixN	operator* (const MatrixN &A, const MatrixN &B);
extern MatrixN	operator* (const MatrixN &A, const Matrix3 &B);
extern MatrixN	operator* (const Matrix3 &A, const MatrixN &B);
extern MatrixN	operator* (const MatrixN &A, const Matrix4 &B);
extern MatrixN	operator* (const Matrix4 &A, const MatrixN &B);

extern bool	operator==(const MatrixN &A, const MatrixN &B);
extern bool	operator!=(const MatrixN &A, const MatrixN &B);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//
extern std::ostream &operator<<(std::ostream &out, const MatrixN &A);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous matrix functions
//
extern double   MP_det		(const MatrixN &A, int r1, int r2, int r3,
						   int c1, int c2, int c3);
extern double   MP_det		(const MatrixN &A);
extern double   MP_det3		(const MatrixN &A);
extern double   MP_det4		(const MatrixN &A);
extern MatrixN  MP_inverse	(const MatrixN &A);
extern MatrixN  MP_outerProduct	(const VectorN &u, const VectorN &v);
extern void     MP_copyMatrix	(const MatrixN &A, int x1, int y1, int w, int h,
				       MatrixN &B, int x2, int y2);

template<class T1, class T2, class T3>
void MP_matrixMultiply(const T1 &A, const T2 &B, T3& C);

}	// namespace MP

#include "MatrixN.tpp"

#endif	// MATRIXN_H
