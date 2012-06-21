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
		preorderSort(root);
	}
}

void ShapeList::preorderSort(ShapeNode *root)
{
	ShapeList newOrder;
	foreach (ShapeNode* node, root->children())
		doPreorderSort(&newOrder, node);
	if (newOrder.count() != count())
		qWarning("Sorting failed: %d %d", newOrder.count(), count());
	else *this = newOrder;
}

void ShapeList::doPreorderSort(ShapeList *newOrder, ShapeNode *root)
{
	newOrder->append(root);
	foreach (ShapeNode* node, root->children())
		doPreorderSort(newOrder, node);
}
