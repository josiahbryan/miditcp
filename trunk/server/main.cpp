#include <QCoreApplication>

#include "MidiReader.h"
#include "MidiServer.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc,argv);
	
	MidiReader reader("/dev/snd/midi1");
	//MidiReader reader("/dev/snd/midiC0D0");
	reader.start();
	
	qDebug() << "Started MIDI Reader Thread.";
	
	MidiServer server;
	QObject::connect(&reader, SIGNAL(midiFrameReady(int,int,int)), &server, SLOT(sendMidiFrame(int,int,int)));
	
	server.start();
	
	return app.exec();
}
