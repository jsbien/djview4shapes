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

void ShapesWidget::open(const QString &filename)
{
	if (!m_extractor->open(filename))
		MessageDialog::warning(tr("Cannot open file:\n%1").arg(filename));
}
