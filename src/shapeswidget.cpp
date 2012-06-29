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

	connect(this, SIGNAL(clicked(QModelIndex)), this,
			  SLOT(onClicked(QModelIndex)));
	connect(this, SIGNAL(doubleClicked(QModelIndex)), this,
			  SLOT(onDoubleClicked(QModelIndex)));
}

ShapesWidget::~ShapesWidget()
{
	close();
	delete m_rootShape;
}

void ShapesWidget::open(QDjVuDocument *document)
{
	close();

	ShapeExtractor extractor;
	connect(&extractor, SIGNAL(progress(int)), this, SIGNAL(progress(int)));

	extractor.open(document);
	m_shapes = extractor.extract(m_rootShape);
	extractor.close();

	m_shapes.sort(ShapeList::SortByPreorder, m_rootShape);
	setModel(m_model);
}

void ShapesWidget::close()
{
	qDeleteAll(m_shapes);
	m_shapes.clear();
	m_rootShape->clear();
}

void ShapesWidget::onClicked(const QModelIndex &index)
{
	if (ShapeNode* node = m_model->nodeAt(index)) {
		ShapeList nodes;
		nodes.append(node);
		if (m_model->selectedItems() == nodes)
			onDoubleClicked(index);
		else {
			 m_model->selectItems(nodes);
			 emit showOccurences(nodes);
		}
	}
}

void ShapesWidget::onDoubleClicked(const QModelIndex &index)
{
	if (ShapeNode* node = m_model->nodeAt(index)) {
		ShapeList nodes = node->shapes(ShapeNode::ShapeDescendants);
		m_model->selectItems(nodes);
		emit showOccurences(nodes);
	}
}

ShapeList ShapesWidget::selectedOccurences() const
{
	return m_model->selectedItems();
}

void ShapesWidget::resizeEvent(QResizeEvent *event)
{
	m_model->setColumnCount((width() - 20) / 30);
	QTableView::resizeEvent(event);
}
