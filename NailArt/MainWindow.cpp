// ===============================================================
// Nail Art Design and Rendering Package
// Copyright (C) 2015 by George Wolberg
//
// MainWindow.cpp - MainWindow class
//
// Written by: George Wolberg, 2015
// ===============================================================

#include "MainWindow.h"
#include "GLWidget.h"

QString GroupBoxStyle = "QGroupBox {				\
			border: 2px solid gray;			\
			border-radius: 9px;			\
			margin-top: 0.5em;}";

MainWindow *MainWindowP = 0;
int	DefaultDisplay  = 1;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::MainWindow:
//
// MainWindow constructor.
//
MainWindow::MainWindow(QWidget *parent)
	:  QWidget(parent)
{
	setWindowTitle("Nail Art");

	// init global var
	MainWindowP = this;	// main window pointer

	// add control panel groupboxes to vertical box layout 
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(createGroupInput  ());
	vbox->addWidget(createGroupFilter ());
	vbox->addWidget(createGroupDimensions());
	vbox->addWidget(createGroupDisplay());
	vbox->addStretch(1);
	vbox->addLayout(createExitButtons());

	// add all widgets to grid layout
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(createGroupView());
	hbox->setStretch(0, 1);
	hbox->addLayout(vbox);
	setLayout(hbox);
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::createGroupView:
//
// Create preview window groupbox.
//
QGroupBox*
MainWindow::createGroupView()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox();
	groupBox->setStyleSheet(GroupBoxStyle);

	m_glWidget = new GLWidget();

	// create a stacked widget to handle multiple displays
	m_stackWidget = new QStackedWidget;

	// create display widgets and add to stacked widget
	for(int i=0; i<2; i++)
		m_stackWidget->addWidget(new QLabel);

	// set centering alignment on both labels
	QLabel *label;
	label = (QLabel *) m_stackWidget->widget(0); label->setAlignment(Qt::AlignCenter); // Input
	label = (QLabel *) m_stackWidget->widget(1); label->setAlignment(Qt::AlignCenter); // Output
	m_stackWidget->addWidget(m_glWidget); // GLWidget (Ortho and Perp view)

	// set stacked widget to default view (output image)
	m_stackWidget->setCurrentIndex(DefaultDisplay);

	// assemble stacked widget in vertical layout
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(m_stackWidget);
	groupBox->setLayout(vbox);

	return groupBox;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::createGroupDimensions:
//
// Create preview window groupbox.
// 
QGroupBox*
MainWindow::createGroupDimensions()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Physical Dimensions");

	// TODO: Update this function for Physical Dimensions

	// init slider label
	QLabel *label[8];
	label[0] = new QLabel("Art Width");
	label[1] = new QLabel("Art Height");
	label[2] = new QLabel("Gauge");
	label[3] = new QLabel("Spacing:");
	label[4] = new QLabel("Nails:");
	label[5] = new QLabel("Image:");
	label[6] = new QLabel("in");
	label[7] = new QLabel("in");

	// layout for assembling filter widget
	QGridLayout *layout = new QGridLayout;

	for (int i = 0; i < 6; i++) {

		// init widget ranges and values
		switch (i) {
		case 0: // art width
			m_valueBox[i] = new QDoubleSpinBox;
			m_valueBox[i]->setMinimum(1);
			m_valueBox[i]->setMaximum(99);
			m_valueBox[i]->setValue(16.00);
			m_valueBox[i]->setDecimals(2);
			m_valueBox[i]->setSingleStep(0.1);
			break;
		case 1: // art height
			m_valueBox[i] = new QDoubleSpinBox;
			m_valueBox[i]->setMinimum(1);
			m_valueBox[i]->setMaximum(99);
			m_valueBox[i]->setValue(16.00);
			m_valueBox[i]->setDecimals(2);
			m_valueBox[i]->setSingleStep(0.1);
			break;
		case 2: // gauge
			m_comboBox = new QComboBox;
			m_comboBox->addItem("16 (thick)");
			m_comboBox->addItem("18 (medium)");
			m_comboBox->addItem("23 (thin)");
			m_comboBox->setCurrentIndex(1);
			break;
		case 3: // spacing
			//TODO
			m_imgLabel[i - 3] = new QLabel;
			m_imgLabel[i - 3]->setText(".15748");
			break;
		case 4: // nails
			//TODO
			m_imgLabel[i - 3] = new QLabel;
			break;
		case 5: // image
			//TODO
			m_imgLabel[i - 3] = new QLabel;
			break;
		}
		layout->addWidget(label[i], i, 0);
	}

	// set member variables
	m_artWidth = m_valueBox[0]->value();
	m_artHeight = m_valueBox[1]->value();
	m_spacing = .15748;

	// assemble widgets into layout
	layout->addWidget(m_valueBox[0], 0, 1);
	layout->addWidget(label[6], 0, 2);
	layout->addWidget(m_valueBox[1], 1, 1);
	layout->addWidget(label[7], 1, 2);
	layout->addWidget(m_comboBox, 2, 1);
	layout->addWidget(m_imgLabel[0], 3, 1);
	layout->addWidget(m_imgLabel[1], 4, 1);
	layout->addWidget(m_imgLabel[2], 5, 1);

	// create dimensions widget and set its layout
	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	// assemble into vertical layout
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(widget);
	groupBox->setLayout(vbox);

	// init signal/slot connections
	connect(m_valueBox[0], SIGNAL(valueChanged(double)), this, SLOT(changeArtWidth(double)));
	connect(m_valueBox[1], SIGNAL(valueChanged(double)), this, SLOT(changeArtHeight(double)));
	connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeGauge(int)));

	return groupBox;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::createGroupInput:
//
// Create input image groupbox.
//
QGroupBox*
MainWindow::createGroupInput()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Input Image");

	// create file/reset pushbuttons
	m_buttonIn[0] = new QPushButton("File" );
	m_buttonIn[1] = new QPushButton("Reset");

	// assemble source/reset pushbuttons in horizontal layout
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(m_buttonIn[0]);
	hbox->addWidget(m_buttonIn[1]);
	groupBox->setLayout(hbox);

	// init signal/slot connections
	connect(m_buttonIn[0], SIGNAL(clicked()), this, SLOT(load ()));
	connect(m_buttonIn[1], SIGNAL(clicked()), this, SLOT(reset()));

	return(groupBox);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::createGroupFilter:
//
// Create image filter groupbox.
//
QGroupBox*
MainWindow::createGroupFilter()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Image Filter");

	// init slider label
	QLabel *label[NUMSLIDERS];
	label[0] = new QLabel("Brightness");
	label[1] = new QLabel("Contrast");
	label[2] = new QLabel("Gamma");
	label[3] = new QLabel("FilterSize");
	label[4] = new QLabel("FilterFctr");

	// layout for assembling filter widget
	QGridLayout *layout = new QGridLayout;

	// create sliders and spinboxes
	for(int i=0; i<NUMSLIDERS; i++) {
		// create slider
		m_slider [i] = new QSlider(Qt::Horizontal);
		m_spinBox[i] = new QDoubleSpinBox;

		// init slider ranges and values
		switch(i) {
		case 0: // brightness
			m_slider [i]->setRange(-256, 256);
			m_slider [i]->setValue(0);
			m_spinBox[i]->setMinimum(-256);
			m_spinBox[i]->setMaximum(256);
			m_spinBox[i]->setValue  (0);
			m_spinBox[i]->setDecimals(0);
			break;
		case 1: // contrast
			m_slider[i]->setRange(-100, 100);
			m_slider[i]->setValue(0);
			m_spinBox[i]->setMinimum(-100);
			m_spinBox[i]->setMaximum(100);
			m_spinBox[i]->setValue(0);
			m_spinBox[i]->setDecimals(0);
			break;
		case 2: // gamma
			m_slider[i]->setRange(1, 100);
			m_slider[i]->setValue(10);
			m_spinBox[i]->setMinimum(0.1);
			m_spinBox[i]->setMaximum(10.);
			m_spinBox[i]->setValue(1.00);
			m_spinBox[i]->setDecimals(2);
			m_spinBox[i]->setSingleStep(0.1);
			break;
		case 3: // filterSize
			m_slider[i]->setRange(1, 100);
			m_slider[i]->setValue(3);
			m_spinBox[i]->setMinimum(1);
			m_spinBox[i]->setMaximum(100);
			m_spinBox[i]->setValue(3);
			m_spinBox[i]->setDecimals(0);
			break;
		case 4: // filterFctr
			m_slider[i]->setRange(1, 100);
			m_slider[i]->setValue(3);
			m_spinBox[i]->setMinimum(1);
			m_spinBox[i]->setMaximum(100);
			m_spinBox[i]->setValue(3);
			m_spinBox[i]->setDecimals(0);
			break;
		}

		// assemble widgets into layout
		layout->addWidget(label	   [i], i, 0);
		layout->addWidget(m_slider [i], i, 1);
		layout->addWidget(m_spinBox[i], i, 2);
	}

	// create filter widget and set its layout
	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	// assemble into vertical layout
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addWidget(widget);
	groupBox->setLayout(vbox);

	// init signal/slot connections
	connect(m_slider[0], SIGNAL(valueChanged(int)), this, SLOT(changeBrightnessI(int)));
	connect(m_spinBox[0], SIGNAL(valueChanged(double)), this, SLOT(changeBrightnessD(double)));
	connect(m_slider[1], SIGNAL(valueChanged(int)), this, SLOT(changeContrastI(int)));
	connect(m_spinBox[1], SIGNAL(valueChanged(double)), this, SLOT(changeContrastD(double)));
	connect(m_slider[2], SIGNAL(valueChanged(int)), this, SLOT(changeGammaI(int)));
	connect(m_spinBox[2], SIGNAL(valueChanged(double)), this, SLOT(changeGammaD(double)));
	connect(m_slider[3], SIGNAL(valueChanged(int)), this, SLOT(changeFilterSizeI(int)));
	connect(m_spinBox[3], SIGNAL(valueChanged(double)), this, SLOT(changeFilterSizeD(double)));
	connect(m_slider[4], SIGNAL(valueChanged(int)), this, SLOT(changeFilterFctrI(int)));
	connect(m_spinBox[4], SIGNAL(valueChanged(double)), this, SLOT(changeFilterFctrD(double)));


	return groupBox;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::createGroupDisplay:
//
// Create preview window groupbox.
//
QGroupBox*
MainWindow::createGroupDisplay()
{
	// init group box
	QGroupBox *groupBox = new QGroupBox("Display");
	groupBox->setMinimumWidth(350);

	// create radio buttons
	m_radioDisplay[0] = new QRadioButton("Input");
	m_radioDisplay[1] = new QRadioButton("Output");
	m_radioDisplay[2] = new QRadioButton("Orthographic View");
	m_radioDisplay[3] = new QRadioButton("Perspective View");

	// create button group and add radio buttons to it
	QButtonGroup *bGroup = new QButtonGroup;
	for(int i=0; i<4; i++)
		bGroup->addButton(m_radioDisplay[i]);
	
	// set output radio button to be default
	m_radioDisplay[DefaultDisplay]->setChecked(true);

	// assemble radio buttons into vertical widget
	QWidget *widget = new QWidget;
	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addStretch();
	vbox->addWidget(m_radioDisplay[0]);
	vbox->addWidget(m_radioDisplay[1]);
	vbox->addWidget(m_radioDisplay[2]);
	vbox->addWidget(m_radioDisplay[3]);
	vbox->addStretch();
	widget->setLayout(vbox);
	groupBox->setLayout(vbox);

	// init signal/slot connections
	connect(m_radioDisplay[0], SIGNAL(clicked()), this, SLOT(displayIn   ()));
	connect(m_radioDisplay[1], SIGNAL(clicked()), this, SLOT(displayOut  ()));
	connect(m_radioDisplay[2], SIGNAL(clicked()), this, SLOT(displayOrtho()));
	connect(m_radioDisplay[3], SIGNAL(clicked()), this, SLOT(displayPersp()));

	return groupBox;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::createExitButtons:
//
// Create save/quit buttons.
//
QHBoxLayout *
MainWindow::createExitButtons()
{
	// create pushbuttons
	QPushButton *buttonSave = new QPushButton("Save");
	QPushButton *buttonQuit = new QPushButton("Quit");

	// init signal/slot connections
	connect(buttonSave, SIGNAL(clicked()), this, SLOT(save()));
	connect(buttonQuit, SIGNAL(clicked()), this, SLOT(quit()));

	// assemble pushbuttons in horizontal layout
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(buttonSave);
	buttonLayout->addWidget(buttonQuit);

	return buttonLayout;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::load:
//
// Load input image.
//
int
MainWindow::load()
{
	QFileDialog dialog(this);

	// open the last known working directory
	if(!m_currentDir.isEmpty())
		dialog.setDirectory(m_currentDir);

	// display existing files and directories
	dialog.setFileMode(QFileDialog::ExistingFile);

	// invoke native file browser to select file
	m_file =  dialog.getOpenFileName(this,
		"Open File", m_currentDir,
		"Images (*.jpg *.png *.ppm *.pgm *.bmp);;All files (*)");

	// verify that file selection was made
	if(m_file.isNull()) return 0;

	// save current directory
	QFileInfo f(m_file);
	m_currentDir = f.absolutePath();

	// read input image and convert to grayscale
	m_imageSrc = IP::IP_readImage(qPrintable(m_file));
	IP_castImage(m_imageSrc, BW_IMAGE, m_imageSrc);

	// compute aspect ratio
	m_ar = (double) m_imageSrc->width() / m_imageSrc->height();

	// Shows nails on the board
	//m_ar = m_imageSrc->width() / m_imageSrc->height();

	m_artWidth = 16.;
	m_artHeight = 16. / m_ar;

	m_valueBox[0]->setValue(m_artWidth);
	m_valueBox[1]->setValue(m_artHeight);

	// update button with filename (without path)
	m_buttonIn[0]->setText(f.fileName());
	m_buttonIn[0]->update();

	// call preview() to display something
	preview();

	return 1;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::preview:
//
// Compute preview image.
//
void
MainWindow::preview()
{
	applyFilter(m_imageSrc, m_imageDst);

	// display requested image
	int i;
	for(i=0; i<4; i++)
		if(m_radioDisplay[i]->isChecked()) break;

	switch(i) {
	case 0:	displayIn   (); break;
	case 1:	displayOut  (); break;
	case 2: displayOrtho(); break;
	case 3: displayPersp(); break;
	}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::applyFilter:
//
// Run filter on the image, transforming I1 to I2.
// Overrides ImageFilterDialog::applyFilter().
// Return 1 for success, 0 for failure.
//
bool
MainWindow::applyFilter(ImagePtr I1, ImagePtr I2)
{
	// error checking
	if(I1.isNull()) {
		IP_printfErr("applyFilter: Missing image");
		return 0;	// failure
	}

	// collect parameters
	double brightness = m_slider[0]->value();
	double contrast = m_slider[1]->value();
	double gamma = m_slider[2]->value() / 10.;
	double filterSize = m_slider[3]->value();
	double filterFctr = m_slider[4]->value();

	int histo[256];
	double hmin, hmax;

	// convert contrast range from [-100, 100] range to [0, 5] range
	if (contrast >= 0)
		contrast = contrast / 25. + 1.;
	else
		contrast = 1 + (contrast / 133.);

	// compute width and height
	int w = m_artWidth / m_spacing;
	int h = m_artHeight / m_spacing;

	// apply filter
	IP_resize(I1, w, h, IP::TRIANGLE, I2);
	IP_contrast(I2, brightness, contrast, 128, I2);
	IP_sharpen(I2, filterSize, filterSize, filterFctr, I2);
	IP_ditherDiffuse(I2, IP::JARVIS_JUDICE_NINKE, gamma, I2);
	IP_copyImage(I2, m_imageDst);

	// set nails
	IP_histogram(I2, 0, histo, 256, hmin, hmax);
	QString nails = QString("%1 nails").arg(histo[0]);
	m_imgLabel[1]->setText(nails);

	// set size
	QString artSize = QString("%1 x %2 pixels").arg(I2->width()).arg(I2->height());
	m_imgLabel[2]->setText(artSize);

	return 1;	// success
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::display:
//
// Slot functions to display input and output images.
//
void MainWindow::displayIn   () { display(0); }
void MainWindow::displayOut  () { display(1); }

void MainWindow::display(int flag)
{
	// error checking
	if(m_imageSrc.isNull()) return;		// no input image
	if(m_imageDst.isNull())			// compute output image
		applyFilter(m_imageSrc, m_imageDst);

	// raise the appropriate widget from the stack
	m_stackWidget->setCurrentIndex(flag);

	// determine image to be displayed
	ImagePtr I;
	int w, h;
	if (flag == 0)
	{
		I = m_imageSrc;
		w = m_stackWidget->width();
		h = m_stackWidget->height();
	}
	else 
	{
		I = m_imageDst;
		w = m_imageDst->width();
		h = m_imageDst->height();
	}

	// convert from ImagePtr to QImage to Pixmap
	QImage q;
	IP_IPtoQImage(I, q);
	QPixmap p = QPixmap::fromImage(q.scaled(QSize(w,h), Qt::KeepAspectRatio));

	// assign pixmap to label widget for display
	QLabel *widget = (QLabel *) m_stackWidget->currentWidget();
	widget->setPixmap(p);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::displayGL:
//
// Slot functions to display GLWidget.
//
void MainWindow::displayOrtho() { displayGL(1); }
void MainWindow::displayPersp() { displayGL(0); }

void MainWindow::displayGL(int flag)
{
	m_stackWidget->setCurrentIndex(2);
	GLWidget *widget = (GLWidget *) m_stackWidget->currentWidget();
	widget->setOrthoView(flag);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::getParams:
//
// Get image parameters.
//
void
MainWindow::getParams(ImagePtr &I, double &spacing, double &artWidth, double &artHeight)
{
	I = m_imageDst;
	spacing = m_spacing;
	artWidth = m_artWidth;
	artHeight = m_artHeight;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::getArtWidth:
//
// Get image width.
//
void
MainWindow::getArtWidth(double &w)
{
	w = m_artWidth;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::getArtHeight:
//
// Get image height.
//
void
MainWindow::getArtHeight(double &h)
{
	h = m_artHeight;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::save:
//
// Save images and parameters.
//
void
MainWindow::save() {}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MainWindow::quit:
//
// Quit application.
//
void
MainWindow::quit()
{
	// close the dialog window
	close();
}

