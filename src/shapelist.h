/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPELIST_H
#define SHAPELIST_H

#include <QtCore>

class Shape;

class ShapeList : public QList<Shape*>
{
public:
	ShapeList();
};

#endif // SHAPELIST_H
