#ifndef CONDITIONLISTVIEW_H
#define CONDITIONLISTVIEW_H

#include "uzooparser.h"	// <-- ResultSearch
#include <qlistview.h>

class ConditionListView : public QListView
{
	Q_OBJECT
	public:
		ConditionListView(QWidget *parent , const char*name);
		~ConditionListView();
		void initKorean();
		void addResultSearch(ResultSearch&);
		void removeResultSearch(ResultSearch&);
	private:
};
#endif//CONDITIONLISTVIEW_H
