#ifndef UZOOSOCKET_H
#define UZOOSOCKET_H

#include <qsocket.h>
#include <qfile.h>
#include <qdatastream.h>

class UzooSocket : public QSocket
{
	Q_OBJECT
	public:
		UzooSocket(const QString &path ,const QString &id , 
						QObject*parent=0 , const char*name=0);
		~UzooSocket();
		void connectTo(QString &address , int port);
		void setTotalFileSize(long);
		void setListIndex(int);
	public slots:
		void slotSend();
		void slotRecvData();
		void slotInspect();

		void slotConnectionClosed();
		void slotDelayedCloseFinished();
		void slotError(int);
	private:
		QString		path;
		QString		id;
		long		nowSize;
		long		totalFileSize;

		bool		canIdownload;
		QFile		downloadfile;
		QDataStream mp3data;

		int			listIndex; // uzoomainnet의 list인덱스를 저장한다.
	signals:
		void sendMessage(const QString&);
		void sendFileSize(int index , int size);
};
#endif//UZOOSOCKET_H
