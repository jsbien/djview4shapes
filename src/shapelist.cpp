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
