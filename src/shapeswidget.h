/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPESWIDGET_H
#define SHAPESWIDGET_H

#include <QtGui>
#include "shapeextractor.h"

class ShapesWidget : public QTableWidget
{
	 Q_OBJECT
public:
	 explicit ShapesWidget(QWidget* parent = 0);
	void open(QDjVuDocument* document);
	void close();
private:
	ShapeExtractor* m_extractor;
};


#endif // SHAPESWIDGET_H
