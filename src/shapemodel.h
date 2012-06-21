/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEMODEL_H
#define SHAPEMODEL_H

#include <QtCore>

class ShapeList;

class ShapeModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit ShapeModel(ShapeList* shapes, QObject *parent = 0);
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	void setColumnCount(int columns);
private:
	int m_columns;
	ShapeList* m_shapes;
};

#endif // SHAPEMODEL_H
