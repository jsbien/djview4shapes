/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapeswidget.h"
#include "shapeextractor.h"
#include "messagedialog.h"

ShapesWidget::ShapesWidget(QWidget *parent) :
	QTableWidget(parent)
{
	m_extractor = new ShapeExtractor(this);
}

void ShapesWidget::open(QDjVuDocument *document)
{
	m_extractor->open(document);
}

void ShapesWidget::close()
{
	m_extractor->close();
}
