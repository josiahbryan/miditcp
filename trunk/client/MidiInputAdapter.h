#ifndef MidiInputAdapter_H
#define MidiInputAdapter_H

#include <QtGui>
#include <QDebug>

class MidiReceiver;

class MidiInputAction : public QObject
{
	//Q_OBJECT
public:
	MidiInputAction() : m_valueIndex(-1) {}
	virtual ~MidiInputAction() {}
	
	// Just return a UUID - makes life easier. Used for mapping persistance across application executions
	virtual QString id() { return "0000-0000-0000-0000"; }
	
	// Displayed to user in config dialog
	virtual QString name() { return "Hello, World"; }
	
	// Fader or Button
	virtual bool isFader() { return false; }

	// Reimplement this to do the real work
	virtual void trigger(int value) { qDebug() << "Hello, World! Value is:"<<value; }
	
	// Called by MidiInputAdapter if smoothing enabled on the adapter
	virtual int smoothValue(int value, int smoothingValue=10);
	
protected:
	// Used to smooth inputs
	QList<int> m_smoothingValues;
	int m_valueTotal;
	int m_valueIndex;
	int m_receivedCount;
};

class MidiInputAdapter : public QObject
{
	Q_OBJECT
public:	
	MidiInputAdapter();
	~MidiInputAdapter();

	QList<MidiInputAction*> availableActions() { return m_actionList; }
	
	bool triggerMappingForKey(int key, int value);
	bool isConfigMode() { return m_configMode; }
	
	QString host() { return m_host; }
	int port() { return m_port; }

	QHash<int, MidiInputAction*> mappings() { return m_mappings; }
	
	int keyForAction(MidiInputAction*);
	MidiInputAction *actionForKey(int key);
	
	bool isConnected();
	
	int faderMax() { return m_faderMax; }
	int faderSmoothing() { return m_smoothingValue; }

public slots:
	void setMappings(QHash<int,MidiInputAction*>);
	void setHost(QString host, int port=3729);
	
	// if true, disables mapping executor
	void setConfigMode(bool);
	
	// Sets the limit value for fader errors due to analog glitches in the MIDI console
	void setFaderMax(int max) { m_faderMax = max; }
	
	// Enable (disable with value=0) smoothing for fader inputs
	void setFaderSmoothing(int value=10) { m_smoothingValue = value; }
	
signals:
	// used mainly to configure and update mappings
	void midiKeyReceived(int key, int val);
	void connectionStatusChanged(bool);

protected slots:
	void midiFrameReady(int chan, int key, int val);


protected:
	virtual void setupActionList();
	
	void storeSettings();
	void loadSettings();

protected:
	QHash<int,MidiInputAction*> m_mappings;
	QList<MidiInputAction*> m_actionList;
	MidiReceiver *m_receiver;
	bool m_configMode;
	
	QString m_host;
	int m_port;
	
	int m_faderMax;
	int m_smoothingValue;

};

#endif
