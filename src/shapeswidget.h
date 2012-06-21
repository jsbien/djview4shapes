/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPESWIDGET_H
#define SHAPESWIDGET_H

#include "shape.h"
#include <QtGui>

class QDjVuDocument;

class ShapesWidget : public QTableWidget
{
	 Q_OBJECT
public:
	explicit ShapesWidget(QWidget* parent = 0);
	~ShapesWidget();
	void open(QDjVuDocument* document);
	void close();
private:
	ShapeList m_shapes;
	ShapeNode* m_rootShape;
};


#endif // SHAPESWIDGET_H
