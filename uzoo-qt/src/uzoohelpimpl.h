#ifndef UZOOHELPIMPL_H
#define UZOOHELPIMPL_H

#include "uzoohelp.h"
class UzooHelpImpl : public UzooHelp
{
	Q_OBJECT
	public:
		UzooHelpImpl(QWidget*parent=0,const char*name=0,
							bool modal=false, int fl=0);
		~UzooHelpImpl();
		void initText();
		void initBrowser();
		void setBrowser(QString browser){ this->browser=browser;}
	public slots:
		void slotSwitchHelpBrowser(int);
	private:
		QString browser;
};

#endif//UZOOHELPIMPL_H
