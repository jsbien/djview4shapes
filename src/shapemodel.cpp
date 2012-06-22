/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapemodel.h"
#include "shape.h"

ShapeModel::ShapeModel(ShapeList* shapes, QObject *parent) :
	QAbstractTableModel(parent), m_shapes(shapes)
{
	m_columns = 20;
}

int ShapeModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	else return (m_shapes->count() + m_columns - 1) / m_columns;
}

int ShapeModel::columnCount(const QModelIndex &parent) const
{
	return parent.isValid() ? 0 : m_columns;
}

QVariant ShapeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	int i = index.row() * m_columns + index.column();
	if (i >= m_shapes->count())
		return QVariant();
	switch (role) {
	case Qt::DecorationRole:
		return m_shapes->at(i)->scaledPixmap(QSize(30, 30));
	case Qt::ToolTipRole:
		return m_shapes->at(i)->tooltip();
	default:
		return QVariant();
	}
	return QVariant();
}

void ShapeModel::setColumnCount(int columns)
{
	m_columns = columns;
	reset();
}
