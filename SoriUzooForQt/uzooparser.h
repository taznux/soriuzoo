#ifndef UZOOPARSER_H
#define UZOOPARSER_H

#include <qobject.h>
#include <qarray.h>
#include <qvaluelist.h>
#include <qnetworkprotocol.h>
#include <qhostaddress.h>
#include <qsocketdevice.h>
#include <qtimer.h>

/* ASR주소에서 받아진 데이타를 정리해서 담는 자료현 */
typedef struct asrarray
{
	int port;
	uchar ip1;
	uchar ip2;
	uchar ip3;
	uchar ip4;
}AsrArray;
/* UDP로 클라이언트들에게 보낼 스트링을 담는 자료형 */
typedef struct sendmessage
{
	uchar *send_data;
	int send_len;
}SendMessage;
/* 클라이언트에게 메세지를 받으면 번역해서 저장한다. */
typedef struct recvmessage
{
	int port;
	QString address;
	QString	message;
}RecvMessage;

class UzooParser : public QObject
{	// 검색이 이루어 질때마다 생성된다.
	// 처음에 클라이언트 정보를 생성자에서 수집하고, 역시 보내야 할 메시지를
	// 만들어 둔다. 이후 전송함수를 실행하면 차근차근 메세지들이 전해져서
	// 이후 슬롯 함수에서 정보를 받아와서 저장고에 저장을 한다.
	// 물론 lookUptable을 만든다.
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
		void initMyIP(const QString &myip); /* 카운터와 search를 제외한 부분*/
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
			/* AsrProtocalMessage를 차곡차곡 저장한다. 물론 디코딩도한다.*/
		void slotFinished(); /* AsrParsing이 끝남을 알림*/
		void slotSendMessageToClients();	
			/* 알아서 하나씩 메세지를 날려준다
			타이머 이벤트에 연결되어 실행한다.물론 실행할때마다. clientsInfo의 
			위치를 인식해서 다음을 실행한다. */
		void slotRecvMessageFromClients();	/* clientsMessage에 차곡차곡 쌓는다.*/

	private:
		QArray<AsrArray> 	*clientsInfo;	
			/* 클라이언트 정보를 변환저장, 7500개의 배열 */
		int					clientsInfoIndex ;
		//QValueList<RecvMessage> *clientsMessage;  /* 클라이언트가 보내준 정보*/
		QTimer				*timer;				  /* send대기시간. */
		QSocketDevice		*socketDevice;
		int					sockfd;
		uchar 				lookUpTable[255];	  /* 인코딩을 위한 테이블	*/
		SendMessage			message;			  /* 각각의 클라이언트들에게
												   * 보낼 데이타	        */
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
