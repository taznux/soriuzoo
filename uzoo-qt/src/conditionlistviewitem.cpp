#include "conditionlistviewitem.h"
#include <iostream.h>

#define kor(x) QString::fromLocal8Bit(x)
ConditionListViewItem::ConditionListViewItem(QListView *parent , ResultSearch &data)	: QListViewItem(parent)
{
	setResultSearch(data);

	setText(1 , kor(data.filename));
	setText(2 , kor(data.title));
	setText(3 , kor(data.singer));
	setText(4 , kor(QString::number(data.filesize)));
	setText(5 , kor(data.bitrate));
	setText(6 , kor(data.filetime));
	setText(7 , kor(data.userid));
}
ConditionListViewItem::~ConditionListViewItem()
{
}
void
ConditionListViewItem::repaint()
{
	cout << "paint\n";
}
