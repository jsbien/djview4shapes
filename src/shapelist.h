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
	enum SortMethod {SortByWidth};
	ShapeList();
	void sort(SortMethod method);
};

#endif // SHAPELIST_H
