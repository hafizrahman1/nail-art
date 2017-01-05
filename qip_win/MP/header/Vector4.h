// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// Vector4.h - 4D vector class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	Vector4.h
//! \brief	4D vector class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::Vector4
//! \brief	4D vector class.
//! \details	The Vector4 class represents 4D vectors of type \a double.

#ifndef VECTOR4_H
#define VECTOR4_H

#include "MPdefs.h"

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Vector4 class declaration
//
class Vector4 {
public:
	Vector4();				// default constructor
	Vector4(const Vector4 &);		// copy constructor
	Vector4(const double  *);		// array constructor

	// component constructor
	Vector4(const double &, const double &, const double &, const double &);

	// public methods
	int      size	() const;		// number of elements
	int      rows	() const;		// number of rows (=size)
	int      cols	() const;		// number of columns (=1)
	double   norm2	() const;		// squared vector norm
	double   norm	() const;		// vector norm
	Vector4 &normalize();			// normalize vector
	MatrixN  transpose() const;		// vector transpose
	Vector4 &clear	();			// clear vector

	// array index operator
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i) const;
	double	     &operator()(int i);

	// assignment operators
	Vector4 &operator= (const Vector4 &);	// copy
	Vector4 &operator+=(const Vector4 &);	// addition
	Vector4 &operator-=(const Vector4 &);	// subtraction
	Vector4 &operator*=(const double &);	// scalar multiplication
	Vector4 &operator/=(const double &);	// scalar division

	// type cast operators
	operator Vector2() const;		// cast to 2D vector
	operator Vector3() const;		// cast to 3D vector
	operator VectorN() const;		// cast to dynamic vector
	operator MatrixN() const;		// cast to nD column vector

protected:
	int	m_size;				// number of elements
	double	m_vector[4];			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern Vector4  operator+(const Vector4 &u, const Vector4 &v);
extern Vector4  operator-(const Vector4 &v);
extern Vector4  operator-(const Vector4 &u, const Vector4 &v);
extern Vector4  operator*(const Vector4 &v, const  double &k);
extern Vector4  operator*(const  double &k, const Vector4 &v);
extern Vector4  operator/(const Vector4 &v, const  double &k);
extern bool	operator==(const Vector4 &A, const Vector4 &B);
extern bool	operator!=(const Vector4 &A, const Vector4 &B);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//
extern std::ostream &operator<<(std::ostream &out, const Vector4 &u);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous vector functions
//
extern void	MP_normalize	(const Vector4 &,	Vector4 &);
extern double	MP_dot		(const Vector4 &, const Vector4 &);
extern Vector4	MP_cross	(const Vector4 &, const Vector4 &, const Vector4 &);

}	// namespace MP

#endif	// VECTOR4_H
