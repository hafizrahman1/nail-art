TEMPLATE = app
TARGET = NailArt
INCLUDEPATH += .
QT += widgets opengl core gui
OBJECTS_DIR = ./obj
MOC_DIR     = ./moc

win32-msvc2013 {
        INCLUDEPATH +=   ../qip_win/IP/header ../qip_win/MP/header
	LIBS	    += -L../qip_win/IP/lib  -L../qip_win/MP/lib    
	LIBS	    += -lIP -lMP
	LIBS 		+= -lopengl32 -lglu32
	QMAKE_CXXFLAGS += /MP /Zi
}


macx{
        INCLUDEPATH +=   ../qip_mac/IP/header ../qip_mac/MP/header
	LIBS	    += -L../qip_mac/IP/lib  -L../qip_mac/MP/lib    
	LIBS	    += -lIP -lMP
        QMAKE_MAC_SDK	 = macosx10.9
	QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
}

unix:!macx {
	LIBS += -L../libs/qip_linux/IP/lib -L../libs/qip_linux/MP/lib
	LIBS += -lIP -lMP -llapack -lblas
	INCLUDEPATH += ../libs/qip_linux/IP/header ../libs/qip_linux/MP/header
}

# Input
HEADERS += MainWindow.h \
		   GLWidget.h
SOURCES += main.cpp \
           MainWindow.cpp \
	   	   change.cpp \
	   	   GLWidget.cpp
