#ifndef CONDITIONLISTVIEWITEM_H
#define CONDITIONLISTVIEWITEM_H

#include "uzooparser.h" 	// <--- ResultSearch
#include <qlistview.h>

/* ListViewItem은 시그널 슬롯을 사용할수 없다. */
class ConditionListViewItem : public QListViewItem
{
	public:
		ConditionListViewItem(QListView *parent , ResultSearch &data);
		~ConditionListViewItem();
		void setResultSearch( ResultSearch &data)	{ result = &data;}
		ResultSearch getResultSearch()				{ return *result ; }
	
		virtual void repaint();
	private:
		ResultSearch *result;
};
#endif//CONDITIONLISTVIEWITEM_H
