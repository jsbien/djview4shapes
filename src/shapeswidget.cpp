/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapeswidget.h"
#include "shapemodel.h"
#include "shapeextractor.h"
#include "messagedialog.h"

ShapesWidget::ShapesWidget(QWidget *parent) :
	QTableView(parent)
{
	m_rootShape = new ShapeNode();
	m_model = new ShapeModel(&m_shapes, this);
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

	int pages = extractor.pages();
	for (int page = 0; page < pages; page++)
		m_shapes.append(extractor.extract(page, m_rootShape));
	extractor.close();

	m_shapes.sort(ShapeList::SortByPostorder, m_rootShape);
	setModel(m_model);
}

void ShapesWidget::close()
{
}
