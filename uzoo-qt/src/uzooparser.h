#ifndef UZOOPARSER_H
#define UZOOPARSER_H

#include "uzooconfigimpl.h"

#include <qobject.h>
#include <qarray.h>
#include <qvaluelist.h>
#include <qnetworkprotocol.h>
#include <qhostaddress.h>
#include <qsocketdevice.h>
#include <qtimer.h>
/* ASR�ּҿ��� �޾��� ����Ÿ�� �����ؼ� ��� �ڷ��� */
typedef struct asrarray
{
	int port;
	uchar ip1;
	uchar ip2;
	uchar ip3;
	uchar ip4;
}AsrArray;
/* UDP�� Ŭ���̾�Ʈ�鿡�� ���� ��Ʈ���� ��� �ڷ��� */
typedef struct sendmessage
{
	uchar *send_data;
	int send_len;
}SendMessage;
/* Ŭ���̾�Ʈ���� �޼����� ������ �����ؼ� �����Ѵ�. */
typedef struct recvmessage
{
	int port;
	QString address;
	QString	message;
}RecvMessage;

enum DownLoadState { NODOWN=0 , START=1 , DOWNLOADING=2 , FINISHED=3,
	WAITING , ERROR , USER_LIMIT , FILE_NOT_FOUND , INVALID_COMMAND ,
	FILE_EXIST , CONNECTION_CLOSED , DELAYED_CLOSE_FINISHED };
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

	QString filename;
	QString downpath;
	long	downsize;
	DownLoadState state;// nodown=0,start=1,downloading=2,finished=3,wating=4
						// error =5,user limit=6, fine not found=7
						// invalid commad=8 ,file exist = 9
						// connection closed = 10, delayed close finished =11
}ResultSearch;

class UzooParser : public QObject
{	
	// �˻��� �̷�� �������� �����ȴ�.
	// ó���� Ŭ���̾�Ʈ ������ �����ڿ��� �����ϰ�, ���� ������ �� �޽�����
	// ����� �д�. ���� �����Լ��� �����ϸ� �������� �޼������� ��������
	// ���� ���� �Լ����� ������ �޾ƿͼ� ����� ������ �Ѵ�.
	// ���� lookUptable�� �����.
	Q_OBJECT
	public:
		UzooParser( QObject *parent=0 , const char *name=0);
		~UzooParser();
		int getClientsInfoSize()	{ return clientsInfo->size(); }
		void searchStop() 			{ timer->stop(); }
		void startParser(const QString &asrurl,const QString &myip, 
									const QString &searchstring);
		void setMyPort(short port)	{ myPort = port ;}
		void setRecvMaxNum(int num)	{ recvMaxNum = num;}
	protected:
		void initAsrUrl(const QString &asrurl);
		void initMyIP(const QString &myip); /* ī���Ϳ� search�� ������ �κ�*/
		void initSearchString(const QString &searchstring);
		void initLookUpTable();
		void send();
		uchar decoding(int num ,uchar data);
		uchar encoding(uchar data) { return lookUpTable[data]; }
		void transrate_decoding(uchar b1 , uchar b2 , uchar ip1 , uchar ip2 , 
								uchar ip3 , uchar ip4 , int &port , uchar &ip1,
								uchar &ip2 , uchar &ip3, uchar &ip4 );
		void transrate_encoding(int port , QString address , uchar &b1 , 
								uchar &b2 , uchar &ip1, uchar &ip2, 
								uchar &ip3, uchar &ip4);
	protected slots:
		/* AsrProtocalMessage�� �������� �����Ѵ�. ���� ���ڵ����Ѵ�.*/
		void slotRecvAsrProtocolMessage(const QByteArray&);
		void slotFinished(); /* AsrParsing�� ������ �˸�*/
		/* �˾Ƽ� �ϳ��� �޼����� �����ش� Ÿ�̸� �̺�Ʈ�� ����Ǿ� �����Ѵ�.
		 * ���� �����Ҷ�����. clientsInfo�� ��ġ�� �ν��ؼ� ������ �����Ѵ�. */
		void slotSendMessageToClients();	
		void slotRecvMessageFromClients();/*clientsMessage�� �������� �״´�.*/
	private:
		QArray<AsrArray> *clientsInfo; /* Ŭ���̾�Ʈ ������ ��ȯ����, */
		int				clientsInfoIndex ;
		QTimer			*timer;				  /* send���ð�. */
		QSocketDevice	*socketDevice;
		int				sockfd;
		uchar 			lookUpTable[256];	  /* ���ڵ��� ���� ���̺�	*/
		SendMessage		message;			  /* ������ Ŭ���̾�Ʈ�鿡��
											   * ���� ����Ÿ	        */
		int	sendCounter;
		int	recvCounter;
		int	recvMaxNum;	 /* ���� Ŭ���̾�Ʈ ���� */
		short myPort;
	signals:
		void startAsrParser();
		void endAsrParser();
		void startSendUDPClients();
		void endSendUDPClients();
		void nowRecvSendUDPClients(int,int);
		void sendClientMessage(ResultSearch&);
		void sendMessage(const QString&);
		void sendMessage(const QString&,int);
};
#endif//UZOOPARSER_H
