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
	addColumn(kor("�������"));
	addColumn(kor("�����̸�"));
	addColumn(kor("����"));
	addColumn(kor("����"));
	addColumn(kor("ũ��"));
	addColumn(kor("����"));
	addColumn(kor("�ð�"));
	addColumn(kor("�����"));
	addColumn(kor("�ӵ�"));
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
