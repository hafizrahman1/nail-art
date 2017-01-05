// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// Matrix3.h - 3x3 matrix class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	Matrix3.h
//! \brief	3x3 matrix class.
//! \author	George Wolberg and Gene Yu, 2015

//! \class	MP::Matrix3
//! \brief	3x3 matrix class.
//! \details	The Matrix3 class represents 3x3 matrices of type double.
//!
//! <b>Example:</b>
//! \verbinclude example_matrix3.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_matrix3.out

#ifndef MATRIX3_H
#define MATRIX3_H

#include "MPdefs.h"

namespace MP {

// forward declarations
class Matrix4;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Matrix3 class declaration
//
class Matrix3 {
public:
	Matrix3();				// default constructor
	Matrix3(const Matrix3 &);		// copy    constructor
	Matrix3(const double  *);		// array   constructor

	// component constructor
	Matrix3(const double &, const double &, const double &,
		const double &, const double &, const double &,
		const double &, const double &, const double &);

	// public methods
	int      size	  () const;		// number of elements
	int	 rows	  () const;		// number of rows
	int	 cols	  () const;		// number of columns
	double	 norm2	  () const;		// squared Frobenius norm
	double	 norm	  () const;		// Frobenius norm
	Matrix3	 transpose() const;		// matrix transpose
	Matrix3 &clear	  ();			// clear matrix
	void	 identity ();			// identity matrix

	// array index operators (for 1D arrays)
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i, int j) const;
	double	     &operator()(int i, int j);

	// assignment operators
	Matrix3 &operator= (const Matrix3 &);	// copy
	Matrix3 &operator+=(const Matrix3 &);	// addition
	Matrix3 &operator-=(const Matrix3 &);	// subtraction
	Matrix3 &operator*=(const double  &);	// scalar multiplication
	Matrix3 &operator*=(const Matrix3 &);	// pre-multiplication
	Matrix3 &operator/=(const double  &);	// scalar division

	// type cast operators
	operator Matrix4() const;		// cast to 4x4 matrix
	operator MatrixN() const;		// cast to dynamic matrix

private:
	int	m_rows;				// number of rows
	int	m_cols;				// number of columns
	double	m_matrix[9];			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern Matrix3	operator+ (const Matrix3 &A, const Matrix3 &B);
extern Matrix3	operator- (const Matrix3 &A);
extern Matrix3	operator- (const Matrix3 &A, const Matrix3 &B);
extern Matrix3	operator* (const Matrix3 &A, const  double &k);
extern Matrix3	operator* (const  double &k, const Matrix3 &A);
extern Matrix3	operator/ (const Matrix3 &A, const  double &k);
extern Vector2	operator* (const Matrix3 &A, const Vector2 &u);
extern Vector2	operator* (const Vector2 &u, const Matrix3 &A);
extern Vector3	operator* (const Matrix3 &A, const Vector3 &u);
extern Vector3	operator* (const Vector3 &u, const Matrix3 &A);
extern Matrix3	operator* (const Matrix3 &A, const Matrix3 &B);
extern bool	operator==(const Matrix3 &A, const Matrix3 &B);
extern bool	operator!=(const Matrix3 &A, const Matrix3 &B);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//

extern std::ostream &operator<<(std::ostream &out, const Matrix3 &A);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous matrix functions
//

extern double	MP_det		(const Matrix3 &A, int r1, int r2, int r3,
						   int c1, int c2, int c3);
extern double	MP_det		(const Matrix3 &A);
extern Matrix3	MP_inverse	(const Matrix3 &A);
extern Matrix3	MP_outerProduct	(const Vector3 &u, const Vector3 &v);

}	// namespace MP

#endif	// MATRIX3_H
