/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapelist.h"
#include "shape.h"

ShapeList::ShapeList()
{
}

void ShapeList::sort(ShapeList::SortMethod method)
{
	switch (method) {
	case SortByWidth:
		qSort(begin(), end(), ShapeNode::widerThan);
		break;
	}
}
