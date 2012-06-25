/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEDOCUMENT_H
#define SHAPEDOCUMENT_H

#include "qdjvuwidget.h"

class ShapeNode;

class ShapeDocument : public QDjVuWidget
{
	Q_OBJECT
public:
	explicit ShapeDocument(QWidget* parent = 0);
public slots:
	void showOccurences(ShapeNode* node);

};

#endif // SHAPEDOCUMENT_H
