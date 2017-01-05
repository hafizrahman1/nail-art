// ===============================================================
// Nail Art Design and Rendering Package
// Copyright (C) 2015 by George Wolberg
//
// GLWidget.cpp - GLWidget class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "GLWidget.h"
#include "MainWindow.h"

#define INIT_DEPTH 3

using namespace IP;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::GLWidget:
//
// GLWidget constructor.
//
GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(parent),
	m_mousePosition(0, 0)
{
	// init variables
	for (int i = 0; i<3; i++) {
		m_rotation[i] = 0;
		m_cameraPos[i] = 0;
	}
	m_cameraPos[2] = INIT_DEPTH;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::~GLWidget:
//
// GLWidget destructor.
//
GLWidget::~GLWidget()
{
	glDeleteLists(m_boardList, 1);
	glDeleteLists(m_nailList, 1);
	glDeleteLists(m_nailsList, 1);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::initializeGL:
//
// Initialization routine before display loop.
//! \brief	Initialization routine before display loop.
//! \details	Initialization routine before display loop.
//
void
GLWidget::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(.9, .9, .9, 1.0);
	initDisplayLists(1);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::paintGL:
//
// Update GL scene.
//! \brief	Update GL scene.
//! \details	Update GL scene.
//
void
GLWidget::paintGL()
{
	// clear color and depth buffer to background values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// reset transformation matrix to identity matrix
	glLoadIdentity();

	// move camera to (x,y,z);
	// clip z so that it is always > 1 to be in front of nailart;
	// look straight ahead: (x,y,z) looks at (x,y,0)
	// use gluLookAt()
	float x = m_cameraPos[0];
	float y = m_cameraPos[1];
	float z = qMax(m_cameraPos[2], 1.0f); // clip
	gluLookAt(x, y, z, x, y, 0, 0, 1, 0);

	// bring origin back to camera position to invert translation below
	glTranslatef(x, y, 0);

	// update transformation for rotation about x-, y-, and z-axes
	glRotatef(m_rotation[0], 1., 0., 0.);	//  cw rotation about x-axis 
	glRotatef(m_rotation[1], 0., 1., 0.);	// ccw rotation about y-axis 
	glRotatef(m_rotation[2], 0., 0., 1.);	// ccw rotation about z-axis, this line can go away

	// bring orthographic projection of camera position to the origin 
	glTranslatef(-x, -y, 0);

	// draw nails
	initDisplayLists(1);
	glCallList(m_nailsList);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::resizeGL:
//
// Resize event handler.
//! \brief	Resize event handler.
//! \details	Resize event handler.
//! \param[in]	w - width
//! \param[in]	h - height
//
void
GLWidget::resizeGL(int w, int h)
{
	// init viewport
	glViewport(0, 0, w, h);

	// save w, h
	m_windowW = w;
	m_windowH = h;

	// aspect ratio
	double ar = (double)w / h;

	// set m_xmax, m_ymax such that aspect ratio of rendering is preserved
	if (w > h) {
		m_xmax = ar;
		m_ymax = 1.;
	}
	else {
		m_xmax = 1.;
		m_ymax = 1. / ar;
	}
	// initialize viewing values
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (m_orthoView) {
		glOrtho(-m_xmax, m_xmax, -m_ymax, m_ymax, -10., 10.);
	}
	else {
		gluPerspective(45, (float)w / h, .01, 1000.);
	}
	glMatrixMode(GL_MODELVIEW);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::mousePressEvent:
//
// Event handler for mouse press events.
//! \brief	Event handler for mouse press events.
//! \details	Event handler for mouse press events.
//! \param[in]	event - mouse event
//
void
GLWidget::mousePressEvent(QMouseEvent *event)
{
	m_mousePosition = event->pos();
	QGLWidget::mousePressEvent(event);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::mouseReleaseEvent:
//
// Event handler for mouse release events.
//! \brief	Event handler for mouse release events.
//! \details	Event handler for mouse release events.
//! \param[in]	event - mouse event
//
void
GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QGLWidget::mouseReleaseEvent(event);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::mouseMoveEvent:
//
// Event handler for mouse move events.
//! \brief	Event handler for mouse move events.
//! \details	Event handler for mouse move events.
//! \param[in]	event - mouse event
//
void
GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	Qt::KeyboardModifiers km = qApp->keyboardModifiers();

	if (event->buttons()&Qt::LeftButton || event->buttons()&Qt::MidButton) {
		QPoint pos = event->pos();
		int dx = pos.x() - m_mousePosition.x();
		int dy = pos.y() - m_mousePosition.y();

		if (event->buttons() & Qt::LeftButton) {
			m_rotation[0] += dy *.5;
			m_rotation[1] += dx *.5;
		}
		else if (km & Qt::ControlModifier) {
			m_cameraPos[0] -= dx * .001;
			m_cameraPos[1] += dy * .001;
		}
		else	m_cameraPos[2] += dy * .1;
		m_mousePosition = pos;
		updateGL();
	}

	QGLWidget::mouseMoveEvent(event);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::initDisplayLists:
//
// Init display lists.
//! \brief	Init display lists.
//! \details	Init display lists.
//
void
GLWidget::initDisplayLists(int flag)
{
	// create display list for board and single nail; only call it first time (flag=1)
	if (flag) {
		// draw board
		m_boardList = glGenLists(1);
		glNewList(m_boardList, GL_COMPILE);

		ImagePtr I;
		double spacing, artWidth, artHeight, ar;

		//get nail spacing , and art dimension values
		MainWindowP->getParams(I, spacing, artWidth, artHeight);

		// compute aspect ratio
		ar = artWidth / artHeight;

		if(artWidth > artHeight)
			drawBoard(2, 2/ar, .05);
		else	
			drawBoard(2*ar, 2, .05);

		glEndList();
		
		// draw single nail
		m_nailList = glGenLists(1);
		glNewList(m_nailList, GL_COMPILE);
		drawCylinder((.04016 / 2), .75);
		glEndList();
	}

	// create display list for the nails
	m_nailsList = glGenLists(1);
	glNewList(m_nailsList, GL_COMPILE);
	glCallList(m_boardList);
	drawNails();
	glEndList();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::drawBoard:
//
// Draw 3D board.
//! \brief	Draw 3D board.
//! \details	Draw 3D board.
//! \param[in]	w - board width
//! \param[in]	h - board height
//! \param[in]	d - board depth
//
void
GLWidget::drawBoard(float w, float h, float d)
{
	// board is drawn from -w to w, -h to h, and -d to d
	w /= 2;
	h /= 2;

	// set the color to white
	glColor3f(1.0, 1.0, 1.0);

	// draw six quadrilaterals for six sides of the board
	glBegin(GL_QUADS);

	// front
	glVertex3f(-w, h, 0);
	glVertex3f(-w, -h, 0);
	glVertex3f(w, -h, 0);
	glVertex3f(w, h, 0);

	// back
	glVertex3f(-w, h, -d);
	glVertex3f(-w, -h, -d);
	glVertex3f(w, -h, -d);
	glVertex3f(w, h, -d);

	// set the color to gray
	glColor3f(0.5, 0.5, 0.5);

	// right side
	glVertex3f(w, h, 0);
	glVertex3f(w, -h, 0);
	glVertex3f(w, -h, -d);
	glVertex3f(w, h, -d);

	// left side
	glVertex3f(-w, h, -d);
	glVertex3f(-w, -h, -d);
	glVertex3f(-w, -h, 0);
	glVertex3f(-w, h, 0);

	// top
	glVertex3f(w, h, -d);
	glVertex3f(-w, h, -d);
	glVertex3f(-w, h, 0);
	glVertex3f(w, h, 0);

	// bottom
	glVertex3f(w, -h, 0);
	glVertex3f(-w, -h, 0);
	glVertex3f(-w, -h, -d);
	glVertex3f(w, -h, -d);
	glEnd();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::drawCylinder:
//
// Draw 3D cylinder.
//! \brief	Draw 3D cylinder.
//! \details	Draw 3D cylinder.
//! \param[in]	r - cylinder radius
//! \param[in]	h - cylinder height
//
void
GLWidget::drawCylinder(float r, float h)
{
	float degToRad = M_PI / 180.;

	// set the color to black
	glColor3f(0.0, 0.0, 0.0);

	// cylinder top at z = h (front)
	glBegin(GL_POLYGON);		// start drawing the cylinder top
	for (int i = 0; i <= 360; i += 5) {
		float a = i * degToRad;	// convert to radians
		glVertex3f(r*cos(a), r*sin(a), h);
	}
	glEnd();

	// cylinder bottom at z = 0 (rear)
	glBegin(GL_POLYGON);		// start drawing the cylinder bottom
	for (int i = 0; i <= 360; i += 5) {
		float a = i * degToRad;	// convert to radians
		glVertex3f(r*cos(a), r*sin(a), 0);
	}
	glEnd();

	// cylinder sides
	glBegin(GL_QUAD_STRIP);		// start drawing the cylinder sides
	for (int i = 0; i <= 360; i += 5) {
		float a = i * degToRad;	// convert to radians
		glVertex3f(r*cos(a), r*sin(a), h);
		glVertex3f(r*cos(a), r*sin(a), 0);
	}
	glEnd();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::drawNails:
//
// Draw 3D nails.
//! \brief	Draw 3D board.
//! \details	Draw 3D board.
//
void
GLWidget::drawNails()
{

	ImagePtr I;
	double spacing, artWidth, artHeight;

	// get nail spacing, and art dimension values
	MainWindowP->getParams(I, spacing, artWidth, artHeight);
	double dx = spacing;
	double dy = dx;
	double s1;
	double s2;
	double ar = artWidth / artHeight;
	
	glPushMatrix();

	// compute board side lengths based on aspect ratio and translate gl matrix appropriately (credit: Muhammad)
	if (artWidth > artHeight)
	{
		s1 = 2 / artWidth;
		s2 = (2/ar) / artHeight;
		glTranslatef(-1 + (.04016 / 4), (1 / ar) - (.04016 / 4), 0);
	}
	else
	{
		s1 = (2*ar) / artWidth;
		s2 = 2/ artHeight;
		glTranslatef(-ar + (.04016 / 4), 1 - (.04016 / 4), 0);
	}

	// compute scale factor that relates art dimensions and board coordinates
	double s = MIN(s1, s2);
	glScalef(s, s, s);

	// draw array of scaled cylinders
	int type;
	IP::ChannelPtr<uchar> p1;
	IP::IP_getChannel(I, 0, p1, type);
	int w = I->width();
	int h = I->height();
	for (int y = 0; y<h; y++) {
		glPushMatrix();

		// draw cylinders only where black pixels are found in row
		for (int x = 0; x<w; x++, p1++) {
			if (!*p1) glCallList(m_nailList);
			glTranslatef(dx, 0., 0.);
		}
		glPopMatrix();
		glTranslatef(0., -dy, 0.);
	}
	glPopMatrix();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::reset:
//
// Reset parameters.
//! \brief	Reset viewing parameters.
//! \details	Reset viewing parameters.
void
GLWidget::reset()
{
	// reset variables
	for (int i = 0; i<3; i++) {
		m_rotation[i] = 0;
		m_cameraPos[i] = 0;
	}
	m_cameraPos[2] = INIT_DEPTH;
	updateGL();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLWidget::setOrthoView:
//
// Set flag for orthographic viewing.
//! \brief	Set flag for orthographic viewing.
//! \details	Set flag for orthographic viewing.
void
GLWidget::setOrthoView(int flag)
{
	m_orthoView = flag;
	resizeGL(m_windowW, m_windowH);
	updateGL();
}
