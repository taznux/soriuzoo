#ifndef UZOOPARSER_H
#define UZOOPARSER_H

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

class UzooParser : public QObject
{	// �˻��� �̷�� �������� �����ȴ�.
	// ó���� Ŭ���̾�Ʈ ������ �����ڿ��� �����ϰ�, ���� ������ �� �޽�����
	// ����� �д�. ���� �����Լ��� �����ϸ� �������� �޼������� ��������
	// ���� ���� �Լ����� ������ �޾ƿͼ� ����� ������ �Ѵ�.
	// ���� lookUptable�� �����.
	Q_OBJECT
	public:
		UzooParser(	const QString &asrurl,
					const QString &myip ,
					const QString &searchstring);
		~UzooParser();
		int getClientsInfoSize() { return clientsInfo->size(); }
		void searchStop() { timer->stop(); }
	protected:
		void initAsrUrl(const QString &asrurl);
		void initMyIP(const QString &myip); /* ī���Ϳ� search�� ������ �κ�*/
		void initSearchString(const QString &searchstring);
		void initLookUpTable();
		void send();
		uchar decoding(int num ,uchar data);
		uchar encoding(uchar data) { return lookUpTable[data]; }

		void transrate_decoding(uchar b1 , uchar b2 ,
			uchar ip1 , uchar ip2 , uchar ip3 , uchar ip4 ,
			int &port , uchar &ip1, uchar &ip2 , uchar &ip3, uchar &ip4 );
		void transrate_encoding(int port , QString address ,
				uchar &b1 , uchar &b2 , 
				uchar &ip1, uchar &ip2, uchar &ip3, uchar &ip4);

	protected slots:
		void slotRecvAsrProtocolMessage(const QByteArray&);
			/* AsrProtocalMessage�� �������� �����Ѵ�. ���� ���ڵ����Ѵ�.*/
		void slotFinished(); /* AsrParsing�� ������ �˸�*/
		void slotSendMessageToClients();	
			/* �˾Ƽ� �ϳ��� �޼����� �����ش�
			Ÿ�̸� �̺�Ʈ�� ����Ǿ� �����Ѵ�.���� �����Ҷ�����. clientsInfo�� 
			��ġ�� �ν��ؼ� ������ �����Ѵ�. */
		void slotRecvMessageFromClients();	/* clientsMessage�� �������� �״´�.*/

	private:
		QArray<AsrArray> 	*clientsInfo;	
			/* Ŭ���̾�Ʈ ������ ��ȯ����, 7500���� �迭 */
		int					clientsInfoIndex ;
		//QValueList<RecvMessage> *clientsMessage;  /* Ŭ���̾�Ʈ�� ������ ����*/
		QTimer				*timer;				  /* send���ð�. */
		QSocketDevice		*socketDevice;
		int					sockfd;
		uchar 				lookUpTable[255];	  /* ���ڵ��� ���� ���̺�	*/
		SendMessage			message;			  /* ������ Ŭ���̾�Ʈ�鿡��
												   * ���� ����Ÿ	        */
		int					sendCounter;
		int					recvCounter;
		int					recvMaxNum;
	signals:
		void startAsrParser();
		void endAsrParser();
		void startSendUDPClients();
		void endSendUDPClients();
		void nowSendUDPClients(int);
		void nowRecvUDPClients(int);
		void sendClientMessage(RecvMessage&);
};
#endif//UZOOPARSER_H
