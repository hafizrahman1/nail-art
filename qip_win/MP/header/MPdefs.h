// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPdefs.h - Header file for MP symbolic constants (#defines) and globals.
//
// Written by: George Wolberg and Gene Yu, 2015
// ======================================================================

//! \file       MPdefs.h
//! \brief      Header file for MP symbolic constants (#defines) and globals.
//! \author     George Wolberg and Gene Yu, 2015

#ifndef MPDEFS_H
#define MPDEFS_H

// ----------------------------------------------------------------------
// standard include files
//
#include <cstdio>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <vector>

namespace MP {

#define MP_PI			3.1415926535897931160E0
#define MP_PI2			6.2831853071795862320E0
#define MP_PI_2			1.5707963267948965580E0
#define MP_DEGtoRAD		0.0174532927777777777E0
#define MP_RADtoDEG		57.295778666661658617E0
#define MP_EPSILON		1.0e-6
#define MP_EPSILON2		1.0e-12

// floating point display width
#define MP_DISPLAY_WIDTH	12

// floating point precision
#define MP_PRECISION		6

// generate a random number between 0 and 1
#define MP_RAND	    		(rand()%(1000000)/1000000.0)
#define MP_RAND_POINT3 		Point3(MP_RAND, MP_RAND, MP_RAND)

// CLAPACK workspace sizes
#define MP_DEFAULT_WORKSPACE	2048
#define MP_SMALL_WORKSPACE	256

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
//
template<class T> T MP_abs(const T &a);
template<class T> T MP_cbrt(const T &a);
template<class T> T MP_isZero(const T &a);
template<class T> int MP_sgn(const T &a);
template<class T> T MP_round(const T &a);
template<class T> T MP_floor(const T &a);
template<class T> T MP_ceiling(const T &a);
template<class T> T MP_clip(const T &a, const T &l, const T &h);
template<class T> T MP_max(const T &a, const T &b);
template<class T> T MP_min(const T &a, const T &b);
template<class T> void MP_swap(T &a, T &b);
extern void MP_swap(int &a, int &b);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Get/set functions for diagonals, rows, and columns.
//
template<class T1, class T2> void MP_getDiag(const T1& A, int d, T2& u);
template<class T1, class T2> void MP_setDiag(const T1& u, T2& A, int d);
template<class T1, class T2> void MP_getRow(const T1& A, int row, T2& u);
template<class T1, class T2> void MP_setRow(const T1& u, T2& A, int row);
template<class T1, class T2> void MP_getCol(const T1& A, int col, T2& u);
template<class T1, class T2> void MP_setCol(const T1& u, T2& A, int col);
template<class T> void MP_swapRows(T &A, int i, int j);
template<class T> void MP_swapCols(T &A, int i, int j);

}	// namespace MP

#include "MPdefs.tpp"

#endif	// MPDEFS_H
