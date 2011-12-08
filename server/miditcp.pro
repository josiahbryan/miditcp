TEMPLATE = app
TARGET = miditcp
DEPENDPATH += .
INCLUDEPATH += .

QT += network

# Input
HEADERS += MidiReader.h \
	MidiServer.h \
	MidiServerThread.h
SOURCES += MidiReader.cpp \
	MidiServer.cpp \
	MidiServerThread.cpp \
	main.cpp 

