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
		/* �α信 �ش�ȴ�. */
		void slotStartConnect();
		void slotGetGateWay(const QByteArray&);
		void slotGetServerInfo(const QByteArray&);
		/* ���� ������� */

		/* �˻������� �����Ѵ�!!!! */
		void slotSearch();
		void slotSearchStop();
		void slotAppendToSearchListView(ResultSearch &);
		/**/
	protected:	
		void runMP3Player(ResultSearch&);	//MP3Player����
		void runMP3Player(int);

	protected slots:
		void slotRunMP3Player();				//�����Ŀ� ����

	public slots:
		void slotAtOnceMP3Player(ResultSearch&);
		void slotAtOnceMP3Player(int);

		void slotStartDownLoad(int);			//�ٿ�ε� ���� ODER!
		void slotStartDownLoad(ResultSearch&);	//�ٿ�ε� ���� ODER!
		// �ٿ�ε� �������� ������ �˸�
		void slotSucceedStartDownLoad(ResultSearch&);		
		//�ٿ�ε� ���� �˸�
		void slotSucceedEndDownLoad(ResultSearch&);			
		void slotStopDownLoad(ResultSearch&);
		void slotStopDownLoad(int);
	/*	void slotStateDownLoad(ResultSearch&);	//�ٿ�ε� ����
		void slotStateDownLoad(int);			//�ٿ�ε� ����*/

	protected slots:
		void slotSearchListBoxHighlighted(int); //���� ������ ���¸� ǥ��
		void slotUpdateClientInfo();	// Timer�� �޾Ƽ� 0.1�������� ������Ʈ
		void slotRecvSendUDPClients(int,int);

		void slotRunConfig();
		void slotRunHelp();
		void slotRunAppearanceConfig();
	private:
		/* ���� ���Ϸ� ������ �ҷ��� ���� �ش�. */
		QString _ASRUrl;	//
		QString _Myip;		//
		UzooEnviroment	info;		// ȯ�����嵥��Ÿ
		/* ������� */
		UzooParser		*parser;	// ���� �߿��� �ļ�
		UzooConfigImpl	*genconfig;	// ���� ȭ��
		UzooHelpImpl	*help;
		QValueList<ResultSearch> *resultSearchList; /*�˻���� ����� */
		QString 	mp3player;
		QStatusBar	*messageStatus;
		int findIndex(ResultSearch&);
};
#endif//UZOOMAINNET_H
