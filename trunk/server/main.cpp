#include <QCoreApplication>
#include <QDir>
#include <QStringList>

#include "MidiReader.h"
#include "MidiServer.h"

#define MIDI_DIR "/dev/snd"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc,argv);

	QDir dir(MIDI_DIR);
	if(!dir.exists())
	{
		qDebug() << "Error: Unable to find '" MIDI_DIR "' - exiting.";
		exit(-1);
	}

	QStringList midiList = dir.entryList(QStringList() << "midi*", QDir::System);
	qDebug() << "Debug: Midi devices found: "<<midiList;
	
	if(midiList.isEmpty())
	{
		qDebug() << "Error: No devices found matching 'midi*' in '" MIDI_DIR "' - exiting.";
		exit(-1);
	}

	QString midiDevice = QString("%1/%2").arg(MIDI_DIR).arg(midiList.first());
	qDebug() << "Debug: Using device: "<<midiDevice;
	
	//MidiReader reader("/dev/snd/midi3");
	//MidiReader reader("/dev/snd/midiC0D0");
	//MidiReader reader("/dev/snd/midiC3D0");
	MidiReader reader(midiDevice);
	reader.start();
	
	qDebug() << "Started MIDI Reader Thread.";
	
	MidiServer server;
	QObject::connect(&reader, SIGNAL(midiFrameReady(int,int,int)), &server, SLOT(sendMidiFrame(int,int,int)));
	
	server.start();
	
	return app.exec();
}
