#ifndef SEARCHLISTBOX_H
#define SEARCHLISTBOX_H

#include "uzooparser.h"
#include <qlistbox.h>
#include <qvaluelist.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qpoint.h>
class SearchListBox : public QListBox
{
	Q_OBJECT
	public:
		SearchListBox(QWidget *parent=0,const char*name=0);
		~SearchListBox();
		void setItems(QValueList<ResultSearch> * src){resultSearchList = src;}
	public slots:
		void slotStateItem(ResultSearch&);
		void slotListMenuActivated(int);
	protected:
		virtual void mouseReleaseEvent(QMouseEvent*);
	private:
		QPixmap	*startDownLoadPix;
		QPixmap *nowDownLoadPix;
		QPixmap *endDownLoadPix;
		QPixmap *userLimitPix;
		QPixmap *errorPix;
		QValueList<ResultSearch> *resultSearchList;
		int findIndex(ResultSearch&);
		QPopupMenu	*listMenu;
	signals:
		void runMP3Player(ResultSearch&);
		void startDownLoad(ResultSearch&);
		void stopDownLoad(ResultSearch&);
};
#endif//SEARCHLISTBOX_H
