// ======================================================================
// Nail Art Design and Rendering Package
// Copyright (C) 2015 by George Wolberg
//
// GLWidget.h - Header file for GLWidget class
//
// Written by: George Wolberg, 2015
// ======================================================================

#ifndef GLWIDGET_H
#define GLWIDGET_H

// ----------------------------------------------------------------------
// standard include files
//
//#include <QOpenGLWidget>
#include <QGLWidget>
#include <GL/glu.h>
#include <QtOpenGL>
#include <QOpenGLFunctions>
#include "IP.h"


//////////////////////////////////////////////////////////////////////////
///
/// \class GLWidget
/// \brief Dialog widget for GLWidget
///
//////////////////////////////////////////////////////////////////////////

class GLWidget : public QGLWidget {
	Q_OBJECT

public:
	// constructor
	GLWidget(QWidget *parent = 0);	// constructor

	// destructor
	~GLWidget();

	void		setOrthoView(int);
	void		initDisplayLists(int);

	public slots:
	void		reset();

protected:
	void		initializeGL();		// initialize GL state
	void		paintGL();		// render GL scene
	void		resizeGL(int, int);	// resize the widget
	void		mousePressEvent(QMouseEvent *);
	void		mouseMoveEvent(QMouseEvent *);
	void		mouseReleaseEvent(QMouseEvent *);
	void		drawBoard(float, float, float);
	void		drawCylinder(float, float);
	void		drawNails();

private:
	int			m_windowW;
	int			m_windowH;
	float		m_xmax;
	float		m_ymax;
	GLuint		m_boardList;
	GLuint		m_nailList;
	GLuint		m_nailsList;
	QPoint		m_mousePosition;
	bool		m_orthoView;
	float		m_rotation[3];
	float		m_cameraPos[3];
};

#endif // GLWIDGET_H
