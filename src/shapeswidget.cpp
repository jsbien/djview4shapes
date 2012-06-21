/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapeswidget.h"
#include "shapeextractor.h"
#include "messagedialog.h"

ShapesWidget::ShapesWidget(QWidget *parent) :
	QTableWidget(parent)
{
	m_rootShape = new ShapeNode();
}

ShapesWidget::~ShapesWidget()
{
	delete m_rootShape;
	qDeleteAll(m_shapes);
}

void ShapesWidget::open(QDjVuDocument *document)
{
	ShapeExtractor extractor;
	extractor.open(document);
	m_shapes.append(extractor.extract(1, m_rootShape));
	extractor.close();

	m_shapes.sort(ShapeList::SortByPostorder, m_rootShape);

	const int Columns = 20;
	setColumnCount(Columns);
	setRowCount((m_shapes.count() + Columns - 1) / Columns);
	for (int i = 0; i < m_shapes.count(); i++) {
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setIcon(m_shapes[i]->pixmap());
		setItem(i / Columns, i % Columns, item);
	}
}

void ShapesWidget::close()
{
}
