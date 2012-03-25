#include <QCoreApplication>

#include "MidiReceiver.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc,argv);
	
	MidiReceiver reader;
	reader.start("192.168.0.18");
	
	qDebug() << "Started MIDI Receiver.";
	
	return app.exec();
}
