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
	m_extractor->extract(1);

	const int Columns = 20;
	setColumnCount(Columns);
	setRowCount((m_extractor->nodeCount() + Columns - 1) / Columns);
	for (int i = 0; i < m_extractor->nodeCount(); i++) {
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(m_extractor->node(i)->getPixmap());
		setItem(i / Columns, i % Columns, item);
	}
}

void ShapesWidget::close()
{
	m_extractor->close();
}
