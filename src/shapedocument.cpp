/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shape.h"
#include "shapedocument.h"

ShapeDocument::ShapeDocument(QWidget *parent) : QDjVuWidget(parent)
{
}

void ShapeDocument::showOccurences(ShapeNode *node)
{
	QColor color(Qt::cyan);
	color.setAlpha(128);

	for (int i = 0; i < 100; i++)
		clearHighlights(i);


	ShapeList list = node->shapes(ShapeNode::ShapeDescendants);
	foreach (ShapeNode* node, list)
		foreach (Blit blit, node->blits()) {
			QDjVuWidget::Position pos;
			pos.pageNo = blit.page();
			pos.inPage = true;
			pos.doPage = true;
			pos.posPage = blit.position();
			addHighlight(pos.pageNo, blit.left(), blit.top(), node->pixmap().width(),
							 node->pixmap().height(), color);
		}
}
