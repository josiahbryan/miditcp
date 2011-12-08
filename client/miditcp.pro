TEMPLATE = app
TARGET = miditcp
DEPENDPATH += .
INCLUDEPATH += .

QT += network

rxtest: {
	SOURCES += MidiReceiver.cpp \
		main_rxtest.cpp
	HEADERS += MidiReceiver.h
	TARGET = rxtest 
}

adaptest: {

	include(miditcp.pri)
	
	SOURCES -= main.cpp
	SOURCES += main_adaptest.cpp
	TARGET = adaptest 
}
