#ifndef UZOOSOCKET_H
#define UZOOSOCKET_H
#include "uzooparser.h"

#include <qsocket.h>
#include <qfile.h>
#include <qdatastream.h>

class UzooSocket : public QSocket
{
	Q_OBJECT
	public:
		UzooSocket( QObject*parent , const char*name,
			ResultSearch &rs , const QString &myid);
		~UzooSocket();
		void setDownLoadPath(const QString&);

		ResultSearch getResultSearch(){ return *rs_p;}
		QString 	getDownLoadFileName() {return downloadfile.name(); }
	public slots:
		void slotSend();
		void slotRecvData();
		void slotInspect();

		void slotConnectionClosed();
		void slotDelayedCloseFinished();
		void slotError(int);
	private:
		ResultSearch *rs_p;
		QString		myid;
		long		nowSize;	// 현재 다운로드된 사이즈
		bool		canIdownload;
		bool		isFirst; // have to send Downloading message only one
		QFile		downloadfile;
		QDataStream mp3data;
	signals:
		void sendMessage(const QString& , int );
		void start(ResultSearch&);
		void state(ResultSearch&);
		void end(ResultSearch&);
};
#endif//UZOOSOCKET_H
