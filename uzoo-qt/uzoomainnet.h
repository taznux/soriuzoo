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
		/* �α信 �ش�ȴ�. */
		void slotStartConnect();
		void slotGetGateWay(const QByteArray&);
		void slotGetServerInfo(const QByteArray&);
		/* ���� ������� */

		/* �˻������� �����Ѵ�!!!! */
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
		void slotUpdateClientInfo();	// Timer�� �޾Ƽ� 0.1�������� ������Ʈ

		void slotRunConfig();
		void slotRunAppearanceConfig();
	private:
			/* ���� ���Ϸ� ������ �ҷ��� ���� �ش�. */
		QString _ASRUrl;	//
		QString _Myip;		//
		UzooEnviroment	info;		// ȯ�����嵥��Ÿ
			/* ������� */
		UzooParser		*parser;	// ���� �߿��� �ļ�
		UzooConfigImpl	*genconfig;	// ���� ȭ��

		QValueList<ResultSearch> *resultSearchList; /*�˻���� ����� */

		QPixmap		*downloadPixmap; // ȭ�ϵ��� ���±׸�
		QPixmap		*userlimitPixmap;
		QPixmap		*filenotPixmap;
		QPixmap		*invalidPixmap;

		QString mp3player;

		QStatusBar	*messageStatus;
};

#endif//UZOOMAINNET_H
