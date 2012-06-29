/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEPREVIEWLIST_H
#define SHAPEPREVIEWLIST_H

#include "shapepreview.h"
#include "shape.h"
#include <QtGui>

class ShapePreviewList : public QScrollArea
{
	Q_OBJECT
public:
	explicit ShapePreviewList(QWidget *parent = 0);
	void setDocument(QDjVuDocument* document);
	void clear();
	int count() const   {return m_items.count();}
	int currentIndex() const {return m_currentItem;}
public slots:
	void showItems(const ShapeList& nodes);
	void setCurrentIndex(int index);
	void configure();
private slots:
	void updateCurrentItem();
signals:
	void currentIndexChanged(int index);
	void pageRequested(int page);
	void documentRequested(const Blit& blit);
private:
	void addItem(ShapeNode *node, const Blit &blit);

	struct ShapeItem{
		QLabel* label;
		ShapePreview* djvu;
	};

	QDjVuDocument* m_document;
	int m_currentItem;
	QGridLayout* m_layout;
	QVector<ShapeItem> m_items;
};

#endif // SHAPEPREVIEWLIST_H
