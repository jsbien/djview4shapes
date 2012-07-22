/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEPREVIEW_H
#define SHAPEPREVIEW_H

#include "blit.h"
#include "qdjvuwidget.h"

/** This is a small class to handle QDjVu previews. */

class ShapeNode;

class ShapePreview : public QDjVuWidget
{
	Q_OBJECT
public:
	explicit ShapePreview(QWidget *parent = 0);
	void setBlit(ShapeNode *node, const Blit &blit);
	void setData(const QVariant& data) {m_data = data;}
	QVariant data() const {return m_data;}
public slots:
	void configure();
protected:
	void focusInEvent(QFocusEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *event);
signals:
	void activated();
	void blitRequested(const Blit& blit);
	void documentRequested(const Blit& blit);
private:
	Blit m_blit;
	QVariant m_data;
};

#endif // SHAPEPREVIEW_H
