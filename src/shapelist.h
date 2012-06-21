/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPELIST_H
#define SHAPELIST_H

#include <QtCore>

class ShapeNode;

class ShapeList : public QList<ShapeNode*>
{
public:
	enum SortMethod {SortByWidth, SortByPreorder, SortByPostorder};
	ShapeList();
	void sort(SortMethod method, ShapeNode* root);
	QSize maximumSize() const;
private:
	void doSort(SortMethod method, ShapeNode* root);
	void preorderSort(ShapeList* newOrder, ShapeNode* root);
	void postorderSort(ShapeList* newOrder, ShapeNode* root);
};

#endif // SHAPELIST_H
