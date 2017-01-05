// ======================================================================
// Nail Art Design and Rendering Package
// Copyright (C) 2015 by George Wolberg
//
// change.cpp - Slot functions for MainWindow class
//
// Written by: George Wolberg, 2015
// ======================================================================

#include "MainWindow.h"

void MainWindow::changeThresholdD(double val) { changeThresholdI((int) val); }
void MainWindow::changeBrightnessD(double val) { changeBrightnessI((int)val); }
void MainWindow::changeContrastD(double val) { changeContrastI((int)val); }
void MainWindow::changeFilterSizeD(double val) { changeFilterSizeI((int)val); }
void MainWindow::changeFilterFctrD(double val) { changeFilterFctrI((int)val); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeThresholdI:
//
// Slot to process change in threshold value caused by moving the slider.
//
void
MainWindow::changeThresholdI(int val)
{
	m_slider [0]->blockSignals(true);
	m_slider [0]->setValue    (val);
	m_slider [0]->blockSignals(false);
	m_spinBox[0]->blockSignals(true);
	m_spinBox[0]->setValue    (val);
	m_spinBox[0]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeBrightnessI:
//
// Slot to process change in brightness value caused by moving the slider.
//
void
MainWindow::changeBrightnessI(int val)
{
	m_slider[0]->blockSignals(true);
	m_slider[0]->setValue(val);
	m_slider[0]->blockSignals(false);
	m_spinBox[0]->blockSignals(true);
	m_spinBox[0]->setValue(val);
	m_spinBox[0]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeContrastI:
//
// Slot to process change in contrast value caused by moving the slider.
//
void
MainWindow::changeContrastI(int val)
{
	m_slider[1]->blockSignals(true);
	m_slider[1]->setValue(val);
	m_slider[1]->blockSignals(false);
	m_spinBox[1]->blockSignals(true);
	m_spinBox[1]->setValue(val);
	m_spinBox[1]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeGammaI:
//
// Slot to process change in gamma value caused by moving the slider.
//
void
MainWindow::changeGammaI(int val)
{
	m_slider[2]->blockSignals(true);
	m_slider[2]->setValue(val);
	m_slider[2]->blockSignals(false);
	m_spinBox[2]->blockSignals(true);
	m_spinBox[2]->setValue(val/10.0);
	m_spinBox[2]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeGammaD:
//
// Slot to process change in gamma value caused by changing the spinbox.
//
void 
MainWindow::changeGammaD(double val)
{ 
	m_slider[2]->blockSignals(true);
	m_slider[2]->setValue(val*10);
	m_slider[2]->blockSignals(false);
	m_spinBox[2]->blockSignals(true);
	m_spinBox[2]->setValue(val);
	m_spinBox[2]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeFilterSizeI:
//
// Slot to process change in filter size value caused by moving the slider.
//
void
MainWindow::changeFilterSizeI(int val)
{
	m_slider[3]->blockSignals(true);
	m_slider[3]->setValue(val);
	m_slider[3]->blockSignals(false);
	m_spinBox[3]->blockSignals(true);
	m_spinBox[3]->setValue(val);
	m_spinBox[3]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeFilterFctrI:
//
// Slot to process change in filter factor value caused by moving the slider.
//
void
MainWindow::changeFilterFctrI(int val)
{
	m_slider[4]->blockSignals(true);
	m_slider[4]->setValue(val);
	m_slider[4]->blockSignals(false);
	m_spinBox[4]->blockSignals(true);
	m_spinBox[4]->setValue(val);
	m_spinBox[4]->blockSignals(false);

	// apply new values to stored image
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeGauge():
//
// Slot to change nail gauge size
//
void
MainWindow::changeGauge(int val)
{
	switch (val)
	{
		case 0:
			m_imgLabel[0]->setText(QString(".23622"));
			m_spacing = .23622;
			break;
		case 1:
			m_imgLabel[0]->setText(QString(".15748"));
			m_spacing = .15748;
			break;
		case 2:
			m_imgLabel[0]->setText(QString(".11811"));
			m_spacing = .11811;
			break;
		default:
			IP::IP_printfErr("MainWindow::changeGauge; Bad Index %d", val);
	}
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeArtWidth():
//
// Slot to change art width
//
void
MainWindow::changeArtWidth(double val)
{
	//TODO
	m_valueBox[0]->setValue(val);
	m_artWidth = val;
	m_artHeight = m_artWidth / m_ar;
	m_valueBox[1]->setValue(m_artHeight);
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::changeArtHeight():
//
// Slot to change art height
//
void
MainWindow::changeArtHeight(double val)
{
	//TODO
	m_valueBox[1]->setValue(val);
	m_artHeight = val;
	m_artWidth = m_artHeight * m_ar;
	m_valueBox[0]->setValue(m_artWidth);
	preview();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::reset:
//
// Slot to reset threshold parameter
//
void
MainWindow::reset()
{
	m_slider[0]->setValue(0);
	m_slider[1]->setValue(0);
	m_slider[2]->setValue(10);
	m_slider[3]->setValue(3);
	m_slider[4]->setValue(3);

	// apply new values to stored image
	preview();
}