// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// Quaternion.h - Quaternion class.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file	Quaternion.h
//! \brief	4D quaternion class.
//! \author	George Wolberg and Gene Yu, 2015
//!
//! \class	MP::Quaternion
//! \brief	4D quaternion class.
//! \details	Quaternions are denoted by lower-case letters starting with
//!		\a q, such as \a q,r,s. A quaternion \a q=ix+jy+kz+w has three
//!		imaginary components \a (x,y,z)=v, representing the axis of
//!		rotation; and one real component \a w, representing the angle of
//!		rotation. Do not use the components directly, however.
//!		Use the axis and angle methods, which convert the quaternion
//!		to quantities in 3D space.
//!
//!		Properties of quaternions:
//!		\f[q = ix + jy + kz + w \f]<br>
//!		\f[i^2 =  j^2 = k^2 = -1 \f] <br>
//!		\f[ij = -ji = k\f] <br>
//!		\f[jk = -kj = i\f] <br>
//!		\f[ki = -ik = j\f]
//!
//! <b>Example:</b>
//! \verbinclude example_quat.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_quat.out

#ifndef QUATERNION_H
#define QUATERNION_H

#include "MPdefs.h"

namespace MP {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Quaternion class declaration
//
class Quaternion {
public:
	Quaternion();				// default constructor
	Quaternion(const Quaternion &);		// copy constructor
	Quaternion(const double *);		// array constructor
	Quaternion(Vector3, double);		// axis/angle constructor
	Quaternion(const Matrix3 &);		// 3x3 matrix constructor
	Quaternion(const Matrix4 &);		// 4x4 matrix constructor

	// component constructor
	Quaternion(const double &, const double &, const double &, const double &);

	// vector constructor
	Quaternion(Vector3, Vector3);

	// public methods
	double		 norm2	 () const;	// squared norm
	double		 norm	 () const;	// norm
	Quaternion    &normalize ();		// normalize
	Quaternion     conjugate () const;	// conjugate
	Vector3		 axis	 () const;	// get rotation axis
	double		 angle	 () const;	// get rotation angle
	Quaternion	&clear	 ();		// clear quaternion elements
	void		 identity();		// identity quaternion

	// array index operator
	const double &operator[](int i) const;
	double	     &operator[](int i);

	// assignment operators
	Quaternion &operator= (const Quaternion &); // copy
	Quaternion &operator+=(const Quaternion &); // addition
	Quaternion &operator-=(const Quaternion &); // subtraction
	Quaternion &operator*=(const Quaternion &); // multiplication
	Quaternion &operator*=(const double &);	    // scalar multiplication
	Quaternion &operator/=(const double &);	    // scalar division

	// type cast operators
	operator Matrix3() const;		// cast to 3x3 matrix
	operator Matrix4() const;		// cast to 4x4 matrix
	operator MatrixN() const;		// cast to dynamic matrix

private:
	int	m_size;				// number of elements
	double	m_quat[4];			// array pointer
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Arithmetic operators
//

extern Quaternion operator+ (const Quaternion &q, const Quaternion &r);
extern Quaternion operator- (const Quaternion &q);
extern Quaternion operator- (const Quaternion &q, const Quaternion &r);
extern Quaternion operator* (const Quaternion &q, const Quaternion &r);
extern Quaternion operator* (const Quaternion &q, const     double &k);
extern Quaternion operator* (const     double &k, const Quaternion &q);
extern Quaternion operator/ (const Quaternion &q, const     double &k);
extern bool	  operator==(const Quaternion &q, const Quaternion &r);
extern bool	  operator!=(const Quaternion &q, const Quaternion &r);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output stream operator: <<
//
extern std::ostream &operator<<(std::ostream &out, const Quaternion &q);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Miscellaneous quaternion functions
//
extern Quaternion MP_inverse (const Quaternion &q);
extern double	  MP_distance(const Quaternion &q, const Quaternion &r);
extern Quaternion MP_slerp(const Quaternion &q, const Quaternion &r,
			   const double &t);
extern void	MP_rotate(const Vector3 &u, const Quaternion &q, Vector3 &v);
extern Vector3 &MP_rotate(Vector3 &u, const Quaternion &q);
extern void	MP_eulerAngles( const   Quaternion &q, double &phi,
				double &theta, double &psi);



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Construct a quaternion q from a 4x4 matrix A.
// The scalar component of q is w=trace(M)^.5, where trace(M)=4w^2.
// Compute the vector component v=(x, y, z) as follows:
//	x = M_{21}-M_{12} / 4w,
//	y = M_{02}-M_{20} / 4w,
//	z = M_{10}-M_{01} / 4w.
//
template<class T>
inline void
MP_matrixToQuaternion(const T &A, Quaternion &q)
{
	T R = A.transpose();

	double d0 = R(0,0), d1 = R(1,1), d2 = R(2,2);
	double xx = 1.0 + d0 - d1 - d2; // from the diagonal of rotation
	double yy = 1.0 - d0 + d1 - d2; // matrix, find the terms in
	double zz = 1.0 - d0 - d1 + d2; // each Quaternion component
	double rr = 1.0 + d0 + d1 + d2;

	double max = rr; // find the maximum of all
	if (xx > max) max = xx; // diagonal terms.
	if (yy > max) max = yy;
	if (zz > max) max = zz;
 
	if (rr == max) {
		double r4 = sqrt(rr * 4.0);
		q[0] = (R(1,2) - R(2,1)) / r4; // find other components from
		q[1] = (R(2,0) - R(0,2)) / r4; // off diagonal terms of
		q[2] = (R(0,1) - R(1,0)) / r4; // rotation matrix.
		q[3] = r4 / 4.0;
	} else if (xx == max) {
		double x4 = sqrt(xx * 4.0);
		q[0] = x4 / 4;
		q[1] = (R(0,1) + R(1,0)) / x4;
		q[2] = (R(0,2) + R(2,0)) / x4;
		q[3] = (R(1,2) - R(2,1)) / x4;
	} else if (yy == max) {
		double y4 = sqrt(yy * 4.0);
		q[0] = (R(0,1) + R(1,0)) / y4;
		q[1] = y4 / 4.0;
		q[2] = (R(1,2) + R(2,1)) / y4;
		q[3] = (R(2,0) - R(0,2)) / y4;
	} else {
		double z4 = sqrt(zz * 4.0);
		q[0] = (R(0,2) + R(2,0)) / z4;
		q[1] = (R(1,2) + R(2,1)) / z4;
		q[2] = z4 / 4;
		q[3] = (R(0,1) - R(1,0)) / z4;
	}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Convert a quaternion q to a 4x4 rotation matrix R.
// Let q=(x, y, z, w). Compute the following matrix:
//    R=[ 1-2y^2-2z^2 & 2xy-2wz     & 2xz+2wy     & 0
//        2xy+2wz     & 1-2x^2-2z^2 & 2yz-2wx     & 0
//        2xz-2wy     & 2yz+2wx     & 1-2x^2-2y^2 & 0
//        0           & 0           & 0           & 1 ].
//
template<class T>
inline void MP_quaternionToMatrix(const Quaternion &r, T &R)
{
	Quaternion q = r;
	q = q.normalize();

	const double x = q[0];
	const double y = q[1];
	const double z = q[2];
	const double w = q[3];

	R(0, 0) = w*w + x*x - y*y - z*z;
	R(1, 0) = 2*x*y + 2*w*z;
	R(2, 0) = 2*x*z - 2*w*y;

	R(0, 1) = 2*x*y-2*w*z;
	R(1, 1) = w*w - x*x + y*y - z*z;
	R(2, 1) = 2*y*z + 2*w*x;

	R(0, 2) = 2*x*z + 2*w*y;
	R(1, 2) = 2*y*z - 2*w*x;
	R(2, 2) = w*w - x*x - y*y + z*z;

	if (R.rows() > 3 && R.cols() > 3) {
		R(0, 3) = 0.0;
		R(1, 3) = 0.0;
		R(2, 3) = 0.0;
		R(3, 0) = 0.0;
		R(3, 1) = 0.0;
		R(3, 2) = 0.0;
		R(3, 3) = w*w + x*x + y*y + z*z;
	}
}

}	// namespace MP

#endif	// QUATERNION_H
