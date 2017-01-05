// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// Vector2.h - 2D vector class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	Vector2.h
//! \brief	2D vector class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::Vector2
//! \brief	2D vector class.
//! \details	The Vector2 class represents 2D vectors of type \a double.

#ifndef VECTOR2_H
#define VECTOR2_H

#include "MPdefs.h"

namespace MP {

// forward declarations
class Vector3;
class Vector4;
class VectorN;
class MatrixN;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Vector2 class declaration
//
class Vector2 {
public:
	Vector2();				// default constructor
	Vector2(const Vector2 &);		// copy constructor
	Vector2(const double  *);		// array constructor

	// component constructor
	Vector2(const double &, const double &);

	// public methods
	int	 size	() const;		// number of elements
	int      rows	() const;		// number of rows (=size)
	int      cols	() const;		// number of columns (=1)
	double	 norm2	() const;		// squared vector norm
	double	 norm	() const;		// vector norm
	Vector2	&normalize();			// normalize vector
	MatrixN  transpose() const;		// vector transpose
	Vector2	&clear	();			// clear vector

	// array index operator
	const double &operator[](int i) const;
	double       &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i) const;
	double	     &operator()(int i);

	// assignment operators
	Vector2 &operator= (const Vector2 &);	// copy
	Vector2 &operator+=(const Vector2 &);	// addition
	Vector2 &operator-=(const Vector2 &);	// subtraction
	Vector2 &operator*=(const double  &);	// scalar multiplication
	Vector2 &operator/=(const double  &);	// scalar division

	// type cast operators
	operator Vector3() const;		// cast to 3D vector
	operator Vector4() const;		// cast to 4D vector
	operator VectorN() const;		// cast to dynamic vector
	operator MatrixN() const;		// cast to nD column vector

protected:
	int	m_size;				// number of elements
	double	m_vector[2];			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern Vector2	operator+(const Vector2 &u, const Vector2 &v);
extern Vector2	operator-(const Vector2 &v);
extern Vector2	operator-(const Vector2 &u, const Vector2 &v);
extern Vector2	operator*(const Vector2 &v, const  double &k);
extern Vector2	operator*(const  double &k, const Vector2 &v);
extern Vector2	operator/(const Vector2 &v, const  double &k);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//
extern std::ostream & operator<<(std::ostream  &, const Vector2 &);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous vector functions
//
extern void	MP_normalize	(const Vector2 &,	Vector2 &);
extern double	MP_dot		(const Vector2 &, const Vector2 &);

}	// namespace MP

#endif	// VECTOR2_H
