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
	enum SortMethod {SortByWidth, SortByPreorder};
	ShapeList();
	void sort(SortMethod method, ShapeNode* root);
private:
	void preorderSort(ShapeNode* root);
	void doPreorderSort(ShapeList* newOrder, ShapeNode* root);
};

#endif // SHAPELIST_H
