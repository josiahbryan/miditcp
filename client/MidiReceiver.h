#ifndef MidiReceiver_H
#define MidiReceiver_H

#include <QDialog>
#include <QTcpSocket>
#include <QTimer>

class QTcpSocket;

class MidiReceiver : public QObject
{
	Q_OBJECT

public:
	MidiReceiver(bool verbose=false, QObject *parent = 0);
	~MidiReceiver();
	
	bool start(const QString& host="", int port=3729);
	void exit();
	
	bool isConnected() { return m_connected; }

signals:
	void midiFrameReady(int chan, int key, int val);
	
	void socketDisconnected();
	void socketError(QAbstractSocket::SocketError);
	void error(QString);	
	void socketConnected();
	void connected();
	void connectionStatusChanged(bool isConnected);

private slots:
	void dataReady();
	void processBlock();
	void lostConnection();
	void lostConnection(QAbstractSocket::SocketError);
	void reconnect();
	void connectionReady();
	void connectTimeout();
	void pingServer();

	void emitError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket *m_socket;
	QByteArray m_dataBlock;
	bool m_connected;
	QString m_host;
	int m_port;
	bool m_verbose;
	bool m_autoReconnect;
	QTimer m_connectTimer;
	QTimer m_pingTimer;
	QTimer m_pingDeadTimer;
};

#endif
