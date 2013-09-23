TEMPLATE = app
TARGET   = mathmlview

CONFIG += qt 
CONFIG += no_keywords
CONFIG += warn_on

QT += xml
QT += widgets

MOC_DIR      = moc
OBJECTS_DIR  = obj

# DEFINES += MML_TEST

HEADERS = \
	qwt_mml_document.h \
	qwt_mml_entity_table.h \
	formulaview.h \
	mainwindow.h

SOURCES = \
	qwt_mml_document.cpp \
	qwt_mml_entity_table.cpp \
	formulaview.cpp \
	mainwindow.cpp \
	main.cpp
