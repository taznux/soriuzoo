#ifndef UZOOCONFIGIMPL_H
#define UZOOCONFIGIMPL_H

#include "uzooconfig.h"
typedef struct uzooenviroment
{
	short biggestClient;
	short biggestEvery;
	short userPort;
	short biggestSearch;
	QString uploadPath;
	QString downloadPath;
	QString defaultPlayerPath;
	QString	playerEnable;
	short	playerStartTime;
	QString userid;
	QString passwd;
	QString	autoLogin;
	QString version;
}UzooEnviroment;

class UzooConfigImpl : public UzooConfig
{
	Q_OBJECT
	public:
		UzooConfigImpl(QWidget*parent=0,const char*name=0,
							bool modal=false, int fl=0);
		~UzooConfigImpl();
		void initTextFile();
		void loadFileInfo(); // 설정화일에서 정보를 추출
		void saveFileInfo(); // 설정화일에 정보를 저장
		void updateDialog(); // GUI에 정보를 보여줌
		UzooEnviroment getInfo(){ return info; }
	public slots:
		void slotApply();
		void slotOk();
		void slotCancel();
		void slotVersionEdited(bool);
		void slotDownLoadFolder();
		void slotFindPlayer();
	private:
		UzooEnviroment info;
		QString	infoString[13];
	signals:
		void sendInfo(const UzooEnviroment&);
};

#endif//UZOOCONFIGIMPL_H
