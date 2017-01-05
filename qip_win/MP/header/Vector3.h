// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// Vector3.h - 3D vector class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	Vector3.h
//! \brief	3D vector class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::Vector3
//! \brief	3D vector class.
//! \details	The Vector3 class represents 3D vectors of type \a double.

#ifndef VECTOR3_H
#define VECTOR3_H

#include "MPdefs.h"

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Vector3 class declaration
//
class Vector3 {
public:
	Vector3();				// default (initialized to 0)
	Vector3(const Vector3 &);		// copy constructor
	Vector3(const double  *);		// array construct

	// component constructor
	Vector3(const double &, const double &, const double &);

	// public methods
	int	 size	() const;		// number of elements
	int      rows	() const;		// number of rows (=size)
	int      cols	() const;		// number of columns (=1)
	double	 norm2	() const;		// squared vector norm
	double   norm	() const;		// vector norm
	Vector3 &normalize();			// normalize vector
	MatrixN  transpose() const;		// vector transpose
	Vector3 &clear	();			// clear vector

	// array index operator
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i) const;
	double	     &operator()(int i);

	// assignment operators
	Vector3 &operator= (const Vector3 &);	// copy

	Vector3 &operator+=(const Vector3 &);	// addition
	Vector3 &operator-=(const Vector3 &);	// subtraction
	Vector3 &operator*=(const double &);	// scalar multiplication
	Vector3 &operator/=(const double &);	// scalar division

	// type cast operators
	operator Vector2() const;		// cast to 2D vector
	operator Vector4() const;		// cast to 4D vector
	operator VectorN() const;		// cast to dynamic vector
	operator MatrixN() const;		// cast to nD column vector

protected:
	int	m_size;				// number of elements
	double	m_vector[3];			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern Vector3  operator+(const Vector3 &u, const Vector3 &v);
extern Vector3  operator-(const Vector3 &v);
extern Vector3  operator-(const Vector3 &u, const Vector3 &v);
extern Vector3  operator*(const Vector3 &v, const  double &k);
extern Vector3  operator*(const  double &k, const Vector3 &v);
extern Vector3  operator/(const Vector3 &v, const  double &k);
extern bool	operator==(const Vector3 &A, const Vector3 &B);
extern bool	operator!=(const Vector3 &A, const Vector3 &B);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//
extern std::ostream &operator<<(std::ostream &out, const Vector3 &u);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous vector functions
//
extern void	MP_normalize	(const Vector3 &, 	Vector3 &);
extern double	MP_dot		(const Vector3 &, const Vector3 &);
extern Vector3	MP_cross	(const Vector3 &, const Vector3 &);

}	// namespace MP

#endif	// VECTOR3_H
