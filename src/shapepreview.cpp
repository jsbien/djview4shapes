/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include <QtGui>
#include "shape.h"
#include "shapepreview.h"

ShapePreview::ShapePreview(QWidget *parent) :
	QDjVuWidget(parent)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	viewport()->installEventFilter(this);
	setFocusPolicy(Qt::StrongFocus);

	configure();
}

void ShapePreview::setBlit(ShapeNode* node, const Blit &blit)
{
	m_blit = blit;
	QColor color(QSettings().value("Display/highlight", "#ffff00").toString());
	color.setAlpha(128);

	QDjVuWidget::Position pos;
	pos.pageNo = blit.page();
	pos.inPage = true;
	pos.doPage = true;
	pos.posPage = blit.position();
	addHighlight(pos.pageNo, blit.left(), blit.top(), node->pixmap().width(),
					 node->pixmap().height(), color);
	setPosition(pos, QPoint(width() / 2, height() / 2));
}

void ShapePreview::configure()
{
	QSettings settings;
	int height = settings.value("Display/previewHeight", 40).toInt();
	setMaximumHeight(height);
}

void ShapePreview::focusInEvent(QFocusEvent* event)
{
	if (event->reason() == Qt::TabFocusReason || event->reason() == Qt::MouseFocusReason)
		emit activated();
}

void ShapePreview::mouseDoubleClickEvent(QMouseEvent*)
{
	if (m_blit.isValid())
		emit pageRequested(m_blit.page());
}

void ShapePreview::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		event->ignore();
		emit documentRequested(m_blit);
	}
	else QDjVuWidget::mousePressEvent(event);
}


