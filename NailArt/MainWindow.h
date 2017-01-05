// ======================================================================
// Nail Art Design and Rendering Package
// Copyright (C) 2015 by George Wolberg
//
// MainWindow.h - Header file for MainWindow class
//
// Written by: George Wolberg, 2015
// ======================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// ----------------------------------------------------------------------
// standard include files
//
#include <QtWidgets>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>

#include "GLWidget.h"
#include "IP.h"
#include "IPtoUI.h"

using namespace IP;

#define NUMSLIDERS	5


class MainWindow : public QWidget {
	Q_OBJECT

public:
	// constructor
	MainWindow	(QWidget *parent = 0);
	void		getParams(ImagePtr&, double&, double&, double&);
	void		getArtWidth(double&);
	void		getArtHeight(double&);

public slots:
	int			load		();
	void		reset		();
	void		changeThresholdI(int);
	void		changeThresholdD(double);
	void		changeBrightnessI(int);
	void		changeBrightnessD(double);
	void		changeContrastI(int);
	void		changeContrastD(double);
	void		changeGammaI(int);
	void		changeGammaD(double);
	void		changeFilterSizeI(int);
	void		changeFilterSizeD(double);
	void		changeFilterFctrI(int);
	void		changeFilterFctrD(double);
	void		changeGauge(int);
	void		changeArtWidth(double);
	void		changeArtHeight(double);

	void		displayIn	();
	void		displayOut	();
	void		displayOrtho();
	void		displayPersp();

protected:
	QGroupBox*	createGroupView	  ();
	QGroupBox*	createGroupDimensions();
	QGroupBox*	createGroupInput  ();
	QGroupBox*	createGroupFilter ();
	QGroupBox*	createGroupDisplay();
	QHBoxLayout*	createExitButtons ();

protected slots:
	void		save();
	void		quit();

private:
	// image pointers
	ImagePtr	 m_imageSrc;
	ImagePtr	 m_imageDst;

	// image info
	double m_spacing;
	double m_artWidth;
	double m_artHeight;
	double m_ar; // aspect ratio


	// widgets for input groupbox
	QPushButton	*m_buttonIn[2];

	// widgets for image filter groupbox
	QSlider		*m_slider [NUMSLIDERS];
	QDoubleSpinBox	*m_spinBox[NUMSLIDERS];

	// widgets for physical dimensions groupbox
	QDoubleSpinBox *m_valueBox[2];
	QComboBox* m_comboBox;
	QLabel* m_imgLabel[3];

	// widgets for image display groupbox
	QRadioButton	*m_radioDisplay[4];
	QStackedWidget	*m_stackWidget;
	GLWidget		*m_glWidget;

	// variables
	QString		 m_file;
	QString		 m_currentDir;

	// functions
	void	display	 (int);
	void	displayGL(int);
	void	preview  ();
	void	messageBadSave(QString);
	bool	applyFilter(ImagePtr, ImagePtr);
};

extern MainWindow *MainWindowP;

#endif // MAINWINDOW_H
