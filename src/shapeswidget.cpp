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
	int page = 0;
	forever {
		ShapeList shapes = extractor.extract(page++, m_rootShape);
		if (shapes.isEmpty())
			break;
		else m_shapes.append(shapes);
	}
	extractor.close();

	m_shapes.sort(ShapeList::SortByPostorder, m_rootShape);
	setModel(m_model);
}

void ShapesWidget::close()
{
}
