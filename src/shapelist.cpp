/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapelist.h"
#include "shape.h"

ShapeList::ShapeList()
{
}

void ShapeList::sort(ShapeList::SortMethod method, ShapeNode* root)
{
	switch (method) {
	case SortByWidth:
		qSort(begin(), end(), ShapeNode::widerThan);
		break;
	case SortByPreorder:
	case SortByPostorder:
		doSort(method, root);
	}
}

QSize ShapeList::maximumSize() const
{
	QSize size;
	for (int i = 0; i < count(); i++)
		size = size.expandedTo(at(i)->pixmap().size());
	return size;
}

ShapeList ShapeList::find(int page, const QPoint &point) const
{
	ShapeList matches;
	for (int i = 0; i < count(); i++)
		foreach (Blit blit, at(i)->blits())
			if (blit.page() == page && blit.rect().contains(point)) {
				matches.append(at(i));
				break;
			}
	return matches;
}

void ShapeList::doSort(ShapeList::SortMethod method, ShapeNode *root)
{
	ShapeList newOrder;
	foreach (ShapeNode* node, root->children()) {
		if (method == SortByPreorder)
			preorderSort(&newOrder, node);
		else postorderSort(&newOrder, node);
	}
	if (newOrder.count() != count())
		qWarning("Sorting failed: %d %d", newOrder.count(), count());
	else *this = newOrder;
}

void ShapeList::preorderSort(ShapeList *newOrder, ShapeNode *root)
{
	newOrder->append(root);
	foreach (ShapeNode* node, root->children())
		preorderSort(newOrder, node);
}

void ShapeList::postorderSort(ShapeList *newOrder, ShapeNode *root)
{
	foreach (ShapeNode* node, root->children())
		preorderSort(newOrder, node);
	newOrder->append(root);
}
