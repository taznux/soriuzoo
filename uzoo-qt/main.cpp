#include <qapplication.h>
#include <qnetwork.h>
#include <qtextcodec.h>
#include "http.h"
#include "uzoomainnet.h"

int main( int argc , char *argv[])
{
	QApplication app(argc , argv);
	app.setDefaultCodec(QTextCodec::codecForLocale());
	qInitNetworkProtocols();
	QNetworkProtocol::registerNetworkProtocol("http" ,
			new QNetworkProtocolFactory<Http> );
	UzooMainNet *uzoo = new UzooMainNet();
	app.setMainWidget(uzoo);
	uzoo->show();
	return app.exec();
}
