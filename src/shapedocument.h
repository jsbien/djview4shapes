/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEDOCUMENT_H
#define SHAPEDOCUMENT_H

#include "qdjvuwidget.h"

class Blit;
class ShapeNode;
class ShapeList;

class ShapeDocument : public QDjVuWidget
{
	Q_OBJECT
public:
	explicit ShapeDocument(QWidget* parent = 0);
	void clearAllHighlights();
public slots:
	void showOccurences(const ShapeList& nodes);
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void clicked(int page, const QPoint& position);
private:
	void showBlit(const Blit& blit);
};

#endif // SHAPEDOCUMENT_H
