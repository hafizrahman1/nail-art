// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// Matrix4.h - 4x4 matrix class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	Matrix4.h
//! \brief	4x4 matrix class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::Matrix4
//! \brief	4x4 matrix class.
//! \details	The Matrix4 class represents 4x4 matrices of type \a double.
//!
//! <b>Example:</b>
//! \verbinclude example_matrix4.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_matrix4.out

#ifndef MATRIX4_H
#define MATRIX4_H

#include "MPdefs.h"

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Matrix4 class declaration
//
class Matrix4 {
public:
	Matrix4();				// default constructor
	Matrix4(const Matrix4 &);		// copy    constructor
	Matrix4(const double  *);		// array   constructor

	// component constructor
	Matrix4(const double &, const double &, const double &, const double &,
		const double &, const double &, const double &, const double &,
		const double &, const double &, const double &, const double &,
		const double &, const double &, const double &, const double &);

	// public methods
	int      size	  () const;		// number of elements
	int	 rows	  () const;		// number of rows
	int	 cols	  () const;		// number of columns
	double	 norm2	  () const;		// squared Frobenius norm
	double	 norm	  () const;		// Frobenius norm
	Matrix4	 transpose() const;		// matrix transpose
	Matrix4	&clear	  ();			// clear matrix
	void	 identity ();			// identity matrix

	// array index operators (for 1D arrays)
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i, int j) const;
	double	     &operator()(int i, int j);

	// assignment operators
	Matrix4 &operator= (const Matrix4 &);	// copy
	Matrix4 &operator+=(const Matrix4 &);	// addition
	Matrix4 &operator-=(const Matrix4 &);	// subtraction
	Matrix4 &operator*=(const double  &);	// scalar multiplication
	Matrix4 &operator*=(const Matrix4 &);	// pre-multiplication
	Matrix4 &operator/=(const double  &);	// scalar division

	// type cast operators
	operator Matrix3() const;		// cast to 3x3 matrix
	operator MatrixN() const;		// cast to dynamic matrix

private:
	int	m_rows;				// number of rows
	int	m_cols;				// number of columns
	double	m_matrix[16];			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern Matrix4	operator+ (const Matrix4 &A, const Matrix4 &B);
extern Matrix4	operator- (const Matrix4 &A);
extern Matrix4	operator- (const Matrix4 &A, const Matrix4 &B);
extern Matrix4	operator* (const Matrix4 &A, const  double &k);
extern Matrix4	operator* (const  double &k, const Matrix4 &A);
extern Matrix4	operator/ (const Matrix4 &A, const  double &k);
extern Vector3	operator* (const Matrix4 &A, const Vector3 &u);
extern Vector3	operator* (const Vector3 &u, const Matrix4 &A);
extern Vector4	operator* (const Matrix4 &A, const Vector4 &u);
extern Vector4	operator* (const Vector4 &u, const Matrix4 &A);
extern Matrix4	operator* (const Matrix4 &A, const Matrix4 &B);
extern bool	operator==(const Matrix4 &A, const Matrix4 &B);
extern bool	operator!=(const Matrix4 &A, const Matrix4 &B);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//
extern  std::ostream &operator<<(std::ostream &out, const Matrix4 &A);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous matrix functions
//
extern double	MP_det		(const Matrix4 &A, int r1, int r2, int r3,
						   int c1, int c2, int c3);
extern double	MP_det		(const Matrix4 &A);
extern Matrix4	MP_inverse	(const Matrix4 &A);
extern Matrix4	MP_outerProduct	(const Vector4 &u, const Vector4 &v);
extern void	MP_eulerAngles	(const Matrix4 &A, double &,double &,double &);

}	// namespace MP

#endif	// MATRIX4_H
