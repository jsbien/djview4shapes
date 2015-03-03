/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEMODEL_H
#define SHAPEMODEL_H

#include <QtCore>
#include "shape.h"

class ShapeModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit ShapeModel(ShapeList* shapes, QObject *parent = 0);

	// Functions subclassing QAbstractTableModel
	/** @return number of shapes in one row. This is based on number of columns. */
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	/** @return number of shapes in one column. This is set by user. */
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	/** @return data for given cell. */
	QVariant data(const QModelIndex &index, int role) const;
	/** @return index of given shape. */
	QModelIndex indexOf(ShapeNode* node) const;

	/** Set whether root shapes should be displayed. */
	void setHighlightRoot(bool enabled);
	/** Set number of columns. */
	void setVisibleColumnCount(int columns);
	/** @return number of visible columns.*/
	int visibleColumnCount() const {return m_columns;}
	/** @return a shape at given index or 0 if there is no such index. */
	ShapeNode* nodeAt(const QModelIndex& index) const;
	/** Set list of selected items. */
	void selectItems(const ShapeList& list);
	/** @return list of selected items. */
	ShapeList selectedItems() const;

private:
	bool m_highlightRoot;
	int m_columns;
	ShapeList* m_shapes;
	QSet<ShapeNode*> m_selectedItems;
};

#endif // SHAPEMODEL_H
