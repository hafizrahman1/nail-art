// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// VectorN.h - N-dimensional vector class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	VectorN.h
//! \brief	N-dimensional vector class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::VectorN
//! \brief	N-dimensional vector class.
//! \details	The VectorN class represents N-dimensional vectors of type \a double.

#ifndef VECTORN_H
#define VECTORN_H

#include "MPdefs.h"

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// VectorN class declaration
//
class VectorN {
public:
	VectorN();				// default constructor
	VectorN(int);				// zero constructor
	VectorN(const VectorN &);		// copy constructor
	VectorN(const double *, int);		// array construct

	// component constructors
	VectorN(const double &, const double &);
	VectorN(const double &, const double &, const double &);
	VectorN(const double &, const double &, const double &, const double &);

	~VectorN();				// destructor

	// public methods
	int      size	() const;		// number of elements
	int      rows	() const;		// number of rows (=size)
	int      cols	() const;		// number of columns (=1)
	double	norm2	() const;		// squared vector norm
	double	norm	() const;		// vector norm
	VectorN &normalize();			// normalize vector
	MatrixN  transpose() const;		// vector transpose
	VectorN &clear    ();			// clear vector
	void     reserve  (int);		// allocate vector memory
	void     resize   (int);		// resize vector

	// assignment operators
	VectorN &operator= (const VectorN &);
	VectorN &operator+=(const VectorN &);	// addition
	VectorN &operator-=(const VectorN &);	// subtraction
	VectorN &operator*=(const double &);	// scalar multiplication
	VectorN &operator/=(const double &);	// scalar division

	// array index operators
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// array index operators (for 2D arrays)
	const double &operator()(int i) const;
	double	     &operator()(int i);

	// type cast operators
	operator Vector2() const;		// cast to 2D vector
	operator Vector3() const;		// cast to 3D vector
	operator Vector4() const;		// cast to 4D vector
	operator MatrixN() const;		// cast to nD column vector

private:
	int	 m_size;			// number of elements
	double	*m_vector;			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern VectorN	operator+(const VectorN &u, const VectorN &v);
extern VectorN	operator-(const VectorN &v);
extern VectorN	operator-(const VectorN &u, const VectorN &v);
extern VectorN	operator*(const VectorN &u, const  double &k);
extern VectorN	operator*(const  double &k, const VectorN &v);
extern VectorN	operator/(const VectorN &v, const  double &k);
extern bool	operator==(const VectorN &A, const VectorN &B);
extern bool	operator!=(const VectorN &A, const VectorN &B);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operators
//
extern std::ostream & operator<<(std::ostream  &, const VectorN &);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous vector functions
//
extern void	MP_normalize	(const VectorN &, 	VectorN &);
extern double	MP_dot		(const VectorN &, const VectorN &);
extern VectorN	MP_cross	(const VectorN &, const VectorN &);
extern VectorN	MP_cross	(const VectorN &, const VectorN &, const VectorN &);



}	// namespace MP

#endif	// VECTORN_H
