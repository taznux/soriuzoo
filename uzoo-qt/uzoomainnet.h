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
	int		downsize; // 0�̸� �ٿ���� ������.0�̿��� ���̸� �ٿ������
}ResultSearch;
class UzooMainNet : public UzooMain
{
	Q_OBJECT
	public:
		UzooMainNet(QWidget*parent=0 , const char*name=0 , int fl=0 );
		~UzooMainNet();
		void initHeloBrower();
	private slots:
		/* �α信 �ش�ȴ�. */
		void slotStartConnect();
		void slotGetGateWay(const QByteArray&);
		void slotGetServerInfo(const QByteArray&);
		/* ���� ������� */

		/* �˻������� �����Ѵ�!!!! */
		void slotSearch();
		void slotSearchStop();
		void slotAppendToSearchListView(RecvMessage &);

		void slotPrintLabe1(int);
		void slotSearchListBoxSelected(int);
		void slotSearchListBoxHighlighted(int);
		void slotSetDownLoadSize(int , int);
		void slotUpdateClientInfo();	// Timer�� �޾Ƽ� 0.1�������� ������Ʈ
	private:
		QString _UserID;
		QString _Passwd;
		QString _Version;
		QString _ASRUrl;
		QString _Myip;
		UzooParser				 *parser;
		QValueList<ResultSearch> *resultSearchList; /*�˻���� ����� */

		QPixmap		*downloadPixmap; // ȭ�ϵ��� ���±׸�
		QPixmap		*userlimitPixmap;
		QPixmap		*filenotPixmap;
		QPixmap		*invalidPixmap;
};

#endif//UZOOMAINNET_H
