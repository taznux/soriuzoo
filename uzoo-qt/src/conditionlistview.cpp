#include "conditionlistview.h"
#include "conditionlistviewitem.h"
#include <qstring.h>

#define kor(x) QString::fromLocal8Bit(x)

ConditionListView::ConditionListView(QWidget *parent,const char*name)
	:QListView(parent , name)
{
	initKorean();
}
ConditionListView::~ConditionListView()
{
}
void
ConditionListView::initKorean()
{
	addColumn(kor("진행상태"));
	addColumn(kor("파일이름"));
	addColumn(kor("제목"));
	addColumn(kor("가수"));
	addColumn(kor("크기"));
	addColumn(kor("음질"));
	addColumn(kor("시간"));
	addColumn(kor("사용자"));
	addColumn(kor("속도"));
}
void
ConditionListView::addResultSearch(ResultSearch &data)
{
	ConditionListViewItem *item = new ConditionListViewItem(this,data);
}
void
ConditionListView::removeResultSearch(ResultSearch &data)
{
}
