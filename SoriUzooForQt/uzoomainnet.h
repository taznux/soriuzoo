#ifndef UZOOMAINNET_H
#define UZOOMAINNET_H
#include "uzoomain.h"
#include "uzooparser.h"

#include <qstring.h>
#include <qvaluelist.h>
#include <qpixmap.h>

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
	int		downsize; // 0이면 다운받지 않은것.0이외의 수이면 다운받은것
}ResultSearch;
class UzooMainNet : public UzooMain
{
	Q_OBJECT
	public:
		UzooMainNet(QWidget*parent=0 , const char*name=0 , int fl=0 );
		~UzooMainNet();
		void initHeloBrower();
	private slots:
		/* 로긴에 해당된다. */
		void slotStartConnect();
		void slotGetGateWay(const QByteArray&);
		void slotGetServerInfo(const QByteArray&);
		/* 물론 여기까지 */

		/* 검색엔진을 가동한다!!!! */
		void slotSearch();
		void slotSearchStop();
		void slotAppendToSearchListView(RecvMessage &);

		void slotPrintLabe1(int);
		void slotSearchListBoxSelected(int);
		void slotSearchListBoxHighlighted(int);
		void slotSetDownLoadSize(int , int);
		void slotUpdateClientInfo();	// Timer로 받아서 0.1간격으로 업데이트
	private:
		QString _UserID;
		QString _Passwd;
		QString _Version;
		QString _ASRUrl;
		QString _Myip;
		UzooParser				 *parser;
		QValueList<ResultSearch> *resultSearchList; /*검색결과 저장고 */

		QPixmap		*downloadPixmap; // 화일들의 상태그림
		QPixmap		*userlimitPixmap;
		QPixmap		*filenotPixmap;
		QPixmap		*invalidPixmap;
};

#endif//UZOOMAINNET_H
