#ifndef UZOOMAINNET_H
#define UZOOMAINNET_H
#include "uzoomain.h"
#include "uzooparser.h"
#include "uzooconfigimpl.h"
#include "uzoosocket.h"

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
		void slotAppendToSearchListView(RecvMessage &);
		/**/
		
		void slotStartDownLoad(UzooSocket*);
		void slotRunMP3Player();
		void slotEndDownLoad(UzooSocket*);

		void slotPrintLabel(int , int);
		void slotSearchListBoxSelected(int);
		void slotSearchListBoxHighlighted(int);
		void slotSetDownLoadSize(int , int);
		void slotSetSocketState(int,char);
		void slotUpdateClientInfo();	// Timer로 받아서 0.1간격으로 업데이트

		void slotRunConfig();
		void slotRunAppearanceConfig();
	private:
			/* 저장 파일로 설정을 불러와 값을 준다. */
		QString _ASRUrl;	//
		QString _Myip;		//
		UzooEnviroment	info;		// 환경저장데이타
			/* 여기까지 */
		UzooParser		*parser;	// 가장 중요한 파서
		UzooConfigImpl	*genconfig;	// 설정 화면

		QValueList<ResultSearch> *resultSearchList; /*검색결과 저장고 */

		QPixmap		*downloadPixmap; // 화일들의 상태그림
		QPixmap		*userlimitPixmap;
		QPixmap		*filenotPixmap;
		QPixmap		*invalidPixmap;

		QString mp3player;

		QStatusBar	*messageStatus;
};

#endif//UZOOMAINNET_H
