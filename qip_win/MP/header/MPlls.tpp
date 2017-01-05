// ======================================================================
// IMPROC: Image Processing Software Package
// Copyright (C) 2015 by George Wolberg
//
// MPlls.tpp - Linear least squares.
//
// Written by: Siavash Zokai, George Wolberg, and Gene Yu, 2015
// ======================================================================

//! \file	MPlls.tpp
//! \brief	Linear least squares.
//! \author	Siavash Zokai, George Wolberg, and Gene Yu, 2015
//!
//! <b>Example:</b>
//! \verbinclude example_gauss.cpp
//!
//! <b>Output:</b>
//! \verbinclude example_gauss.out

namespace MP {

//! \addtogroup solvers
//@{

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MP_lls:
//
// Linear least squares.
//! \brief	Linear least squares.
//! \details	Solve a linear least squares problem.
//! \param[in]	D - Matrix.
//! \param[in]	B - Right-hand-side matrix.
//! \param[out]	X - Solution matrix.
//
template<class T1, class T2, class T3>
void
MP_lls(T1 &D, T2 &B, T3 &X)
{

       MatrixN A(D.cols(), D.cols()), MB(D.cols(), 1);
       MatrixN DT(D.cols(), D.rows());

       // multiply DT and D matrix
       DT = D.transpose();
       A = DT * D;
       MB = DT * B;
       MP_GaussJordan(A, MB, X);
}
//@}

} // namespace MP
