#include "searchlistbox.h"
#include <qcolor.h>
#include <qcursor.h>
#include <qevent.h>
#include <qnamespace.h>

#include <iostream.h>
#define kor(x) QString::fromLocal8Bit(x)
SearchListBox::SearchListBox(QWidget *parent , const char*name )
	: QListBox(parent,name)
{
	startDownLoadPix = new QPixmap(15,15);
	nowDownLoadPix = new QPixmap(15,15);
	endDownLoadPix = new QPixmap(15,15);
	userLimitPix = new QPixmap(15,15);
	errorPix = new QPixmap(15,15);
	
	startDownLoadPix->fill(QColor(107,142,255));
	nowDownLoadPix->fill(QColor(107,61,255));
	endDownLoadPix->fill(QColor(0,0,0));
	userLimitPix->fill(QColor(255,0,0));
	errorPix->fill(QColor(255,164,27));

	listMenu = new QPopupMenu(this , "listMenu");
	listMenu->insertItem(QString("Start Download"), 0);
	listMenu->insertItem(QString("Stop  Download") ,1);
	listMenu->insertItem(QString("play MP3Player") ,2 );
	connect(listMenu , SIGNAL(activated(int)),
			this , SLOT(slotListMenuActivated(int)));
}
SearchListBox::~SearchListBox()
{
}
void
SearchListBox::slotListMenuActivated(int id)
{
	// 현재 선택되어진 리스트의 index로 ResultSearch를 찾아 넘긴다.
	int listIndex = this->currentItem();
	if(id == 0)
	{
		emit startDownLoad((*resultSearchList)[listIndex]);
	}
	else if(id == 1)
	{
		emit stopDownLoad((*resultSearchList)[listIndex]);
	}
	else if(id == 2)
	{
		emit runMP3Player((*resultSearchList)[listIndex]);
	}
}
void
SearchListBox::slotStateItem(ResultSearch& data)
{
	/*
	enum DownLoadState 
	{ NODOWN=0 , START=1 , DOWNLOADING=2 , FINISHED=3,
    WAITING , ERROR , USER_LIMIT , FILE_NOT_FOUND , INVALID_COMMAND ,
    FILE_EXIST , CONNECTION_CLOSED , DELAYED_CLOSE_FINISHED };*/

	int findListBoxIndex = findIndex(data);
	if (findListBoxIndex < 0 ) return;
	if ( data.state == START)
	{
		changeItem( *startDownLoadPix , kor(data.filename) , findListBoxIndex);
	}
	else if (data.state == DOWNLOADING )
	{
		changeItem( *nowDownLoadPix , kor(data.filename) , findListBoxIndex);
	}
	else if (data.state == FINISHED)
	{
		changeItem( *endDownLoadPix , kor(data.filename) , findListBoxIndex);
	}
	else if (data.state == USER_LIMIT)
	{
		changeItem( *userLimitPix , kor(data.filename) , findListBoxIndex);
	}
	else if (data.state == ERROR)
	{
		changeItem( *errorPix , kor(data.filename) , findListBoxIndex);
	}
}
int
SearchListBox::findIndex(ResultSearch& data)
{
    for(int i=0 ; i <(int)resultSearchList->count() ;i++)
    {
        ResultSearch *src = &(*resultSearchList)[i];
        if (src == &data ) // address compare
            return i;
    }
    return -1;
}

void
SearchListBox::mouseReleaseEvent(QMouseEvent *event)
{
	QListBox::mouseReleaseEvent(event);
	if (event->button() == Qt::RightButton)
	{
		// 현재 Item의 상태에 따라 PopupMenu의 상태를 설정
		int listIndex = this->currentItem();
		ResultSearch *src = &(*resultSearchList)[listIndex];
		listMenu->setItemEnabled(0,false);
		listMenu->setItemEnabled(1,false);
		listMenu->setItemEnabled(2,false);
		if (src->state == NODOWN)
		{
			// Start Download true
			listMenu->setItemEnabled(0,true);
		}
		else if (src->state == DOWNLOADING)
		{
			// MP3 Player Stop Download
			listMenu->setItemEnabled(2, true);
			listMenu->setItemEnabled(1, true);
		}
		else if (src->state == FINISHED )
		{
			// MP3 Plater
			listMenu->setItemEnabled(2 , true);
		}
		listMenu->exec(QCursor::pos());
	}
}

