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

	connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onClicked(QModelIndex)));
}

ShapesWidget::~ShapesWidget()
{
	close();
	delete m_rootShape;
}

void ShapesWidget::open(QDjVuDocument *document)
{
	ShapeExtractor extractor;
	connect(&extractor, SIGNAL(progress(int)), this, SIGNAL(progress(int)));

	extractor.open(document);
	m_shapes = extractor.extract(m_rootShape, 0, 1);
	extractor.close();

	m_shapes.sort(ShapeList::SortByPreorder, m_rootShape);
	setModel(m_model);
}

void ShapesWidget::close()
{
	qDeleteAll(m_shapes);
	m_shapes.clear();
}

void ShapesWidget::onClicked(const QModelIndex &index)
{
	if (ShapeNode* node = m_model->nodeAt(index)) {
		m_model->selectItems(node->shapes(ShapeNode::ShapeDescendants));
		emit showOccurences(node);
	}
}
