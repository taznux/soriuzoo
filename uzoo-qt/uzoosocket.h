#ifndef UZOOSOCKET_H
#define UZOOSOCKET_H

#include <qsocket.h>
#include <qfile.h>
#include <qdatastream.h>
typedef struct resultsearch
{
	QString address;
	QString userid;
	int 	port;
	QString path;
	long	filesize;
	QString filetime;
	QString bitrate;
	QString singer;
	QString title;
	QString comment;
	int		downsize; 	// 0이면 다운받지 않은것.0이외의 수이면 다운받은것
	char	state;		// nodown=0,start=1,downloading=2,finished=3,wating=4
						// error =5,user limit=6, fine not found=7
						// invalid commad=8 ,file exist = 9
						// connection closed = 10, delayed close finished =11
						//
}ResultSearch;

class UzooSocket : public QSocket
{
	Q_OBJECT
	public:
		UzooSocket( QObject*parent , const char*name,
			ResultSearch &rs , int listIndex , const QString &myid);
		~UzooSocket();
		void setListIndex(int);
		void setDownLoadPath(const QString&);

		ResultSearch getResultSearch(){ return rs;}
		int			getNowFileSize(){ return nowSize;}
		int 		getListIndex(){ return listIndex;}
		QString 	getDownLoadFileName() {return downloadfile.name(); }
	public slots:
		void slotSend();
		void slotRecvData();
		void slotInspect();

		void slotConnectionClosed();
		void slotDelayedCloseFinished();
		void slotError(int);
	private:
		ResultSearch rs;
		QString		myid;
		long		nowSize;	// 현재 다운로드된 사이즈
		int			listIndex;	// uzoomainnet의 list인덱스를 저장한다.
		bool		canIdownload;
		QFile		downloadfile;
		QDataStream mp3data;
	signals:
		void sendMessage(const QString&);
		void sendFileSize(int index , int size);
		void sendState(int listIndex ,char state);
		void start(UzooSocket*);
		void end(UzooSocket*);
};
#endif//UZOOSOCKET_H
