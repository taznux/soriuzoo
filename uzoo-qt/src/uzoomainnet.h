#ifndef UZOOMAINNET_H
#define UZOOMAINNET_H
#include "uzoomain.h"
#include "uzooparser.h"
#include "uzooconfigimpl.h"
#include "uzoohelpimpl.h"
#include "uzoosocket.h"
#include "conditionlistview.h"
#include "searchlistbox.h"

#include <qstring.h>
#include <qvaluelist.h>
#include <qpixmap.h>
#include <qstatusbar.h>

class UzooMainNet : public UzooMain
{
	Q_OBJECT
	public:
		UzooMainNet(QWidget*parent=0 , const char*name=0 , int fl=0 );
		~UzooMainNet();
		void initStatusBar();
		void initKorean();
		
	protected slots:
		void slotEnviroment(const UzooEnviroment&);
		/* 로긴에 해당된다. */
		void slotStartConnect();
		void slotGetGateWay(const QByteArray&);
		void slotGetServerInfo(const QByteArray&);
		/* 물론 여기까지 */

		/* 검색엔진을 가동한다!!!! */
		void slotSearch();
		void slotSearchStop();
		void slotAppendToSearchListView(ResultSearch &);
		/**/
	protected:	
		void runMP3Player(ResultSearch&);	//MP3Player실행
		void runMP3Player(int);

	protected slots:
		void slotRunMP3Player();				//몇초후에 실행

	public slots:
		void slotAtOnceMP3Player(ResultSearch&);
		void slotAtOnceMP3Player(int);

		void slotStartDownLoad(int);			//다운로드 시작 ODER!
		void slotStartDownLoad(ResultSearch&);	//다운로드 시작 ODER!
		// 다운로드 성공적인 시작을 알림
		void slotSucceedStartDownLoad(ResultSearch&);		
		//다운로드 끝을 알림
		void slotSucceedEndDownLoad(ResultSearch&);			
		void slotStopDownLoad(ResultSearch&);
		void slotStopDownLoad(int);
	/*	void slotStateDownLoad(ResultSearch&);	//다운로드 상태
		void slotStateDownLoad(int);			//다운로드 상태*/

	protected slots:
		void slotSearchListBoxHighlighted(int); //현재 아이템 상태를 표시
		void slotUpdateClientInfo();	// Timer로 받아서 0.1간격으로 업데이트
		void slotRecvSendUDPClients(int,int);

		void slotRunConfig();
		void slotRunHelp();
		void slotRunAppearanceConfig();
	private:
		/* 저장 파일로 설정을 불러와 값을 준다. */
		QString _ASRUrl;	//
		QString _Myip;		//
		UzooEnviroment	info;		// 환경저장데이타
		/* 여기까지 */
		UzooParser		*parser;	// 가장 중요한 파서
		UzooConfigImpl	*genconfig;	// 설정 화면
		UzooHelpImpl	*help;
		QValueList<ResultSearch> *resultSearchList; /*검색결과 저장고 */
		QString 	mp3player;
		QStatusBar	*messageStatus;
		int findIndex(ResultSearch&);
};
#endif//UZOOMAINNET_H
