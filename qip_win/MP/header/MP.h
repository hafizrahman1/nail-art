// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MP.h - Header file for MP*.cpp files
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================
//

//! \mainpage	Math Package
//! \author	George Wolberg
//! \author	Gene Yu
//! \date	2015
//! \par	References:
//! 		This code is part of the
//!		IMPROC Image Processing Software Package\n
//!		Copyright &copy; 2015 by George Wolberg

//! \file  MP.h
//! \brief Math Package main header file.
//! \author George Wolberg and Gene Yu, 2015

#ifndef MP_H
#define MP_H

#include "MPdefs.h"

// 2D objects
#include "Vector2.h"

// 3D objects
#include "Vector3.h"
#include "Matrix3.h"

// 4D objects
#include "Vector4.h"
#include "Matrix4.h"

// Quaternion
#include "Quaternion.h"

// variable-sized objects
#include "VectorN.h"
#include "MatrixN.h"

// Point types
namespace MP {
typedef Vector2 Point2;
typedef Vector3 Point3;
typedef Vector4 Point4;
typedef VectorN PointN;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Linear System Solvers
//! \defgroup solvers MP: Linear System Solvers
//! \brief Solve linear equations of the form AX=B.

// MPband.tpp
template<class T1, class T2> void MP_tridiagonal(T1 &A, T2 &B);

// MPgauss.tpp
template<class T1, class T2, class T3>
	void MP_GaussJordan(T1 &A, T2 &B, T3 &X);
template<class T1, class T2, class T3>
	void MP_GaussElimination(T1 &A, T2 &B, T3 &X);

// MPlls.tpp
template<class T1, class T2, class T3> void MP_lls(T1 &D, T2 &B, T3 &X);

// MPpolySolver.cpp
extern void MP_solveQuadratic(const VectorN& v, VectorN& roots);
extern void MP_solveCubic    (const VectorN& v, VectorN& roots);

} // namespace MP

#include "MPband.tpp"
#include "MPgauss.tpp"
#include "MPlls.tpp"

// LAPACK Linear Algebra library
extern "C" {
#include <f2c.h>
#include <clapack.h>
}
#include <cstring>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LAPACK Routines
//! \defgroup lapack MP: LAPACK Routines
//! \brief Algorithms using LAPACK.

// MPchol.tpp
template<class T1, class T2> int MP_choleskyDecomp(const T1 &A, T2 &CD);
template<class T1, class T2> int MP_choleskySolve (const T1 &A, T2 &B);

// MPeigen.tpp
template<class T1, class T2, class T3>
	int MP_eigenvalues(const T1 &A, T2 &W, T3 &V);

// MPlu.tpp
template<class T1>
	void MP_LUdcmp(T1 &A, integer *index, double &d);
template<class T1, class T2>
	void MP_LUbksb(T1 &A, integer *index, T2 &B);

// MPqr.tpp
template<class T1, class T2, class T3>
	int MP_QRdcmp(const T1 &A, T2 &Q, T3 &R);

// MPrq.tpp
template<class T1, class T2, class T3>
	int MP_RQdcmp(const T1 &A, T2 &R, T3 &Q);

// MPsvd.tpp
template<class T1, class T2, class T3, class T4>
	int MP_svd(const T1 &A, T2 &U, T3 &S, T4 &V, bool econ);

#include "MPchol.tpp"
#include "MPeigen.tpp"
#include "MPlu.tpp"
#include "MPqr.tpp"
#include "MPrq.tpp"
#include "MPsvd.tpp"

#endif // MP_H
