/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shape.h"
#include "shapedocument.h"

ShapeDocument::ShapeDocument(QWidget *parent) : QDjVuWidget(parent)
{
}

void ShapeDocument::clearAllHighlights()
{
	for (int i = 0; i < 1000; i++)
		clearHighlights(i);

}

void ShapeDocument::showOccurences(const ShapeList& nodes)
{
	clearAllHighlights();
	foreach (ShapeNode* node, nodes)
		foreach (Blit blit, node->blits())
			showBlit(blit);
}

void ShapeDocument::showBlit(const Blit &blit)
{
	QColor color(QSettings().value("Display/highlight", "#ffff00").toString());
	color.setAlpha(128);
	QDjVuWidget::Position pos;
	pos.pageNo = blit.page();
	pos.inPage = true;
	pos.doPage = true;
	pos.posPage = blit.position();
	addHighlight(pos.pageNo, blit.left(), blit.top(), blit.size().width(),
					 blit.size().height(), color);
}
