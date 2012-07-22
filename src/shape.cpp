/****************************************************************************
*   Copyright (C) 2011 by Grzegorz Chimosz
*   Copyright (C) 2012 by Michal Rudolf
*   This software is subject to, and may be distributed under, the
*   GNU General Public License, either version 2 of the license,
*   or (at your option) any later version. The license should have
*   accompanied the software or you may obtain a copy of the license
*   from the Free Software Foundation at http://www.fsf.org .

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
****************************************************************************/

#include "shape.h"

ShapeNode::ShapeNode(ShapeNode *parent, QPixmap pixmap) :
	m_pixmap(pixmap)
{
	m_parent = parent;
	if (m_parent)
		m_parent->m_children.append(this);
}

QPixmap ShapeNode::scaledPixmap(const QSize& maxSize) const
{
	if (m_pixmap.width() > maxSize.width() || m_pixmap.height() > maxSize.height())
		return m_pixmap.scaled(maxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	else return m_pixmap;
}

int ShapeNode::childrenCount(bool recursive) const
{
	int sum = m_children.count();
	if (recursive)
		for (int i = 0; i < m_children.count(); i++)
			sum += m_children[i]->childrenCount(true);
	return sum;
}

ShapeList ShapeNode::shapes(ShapeNode::ShapeSelection selection)
{
	ShapeList selected;
	ShapeNode* node;

	switch (selection) {
	case SingleShape:
		selected.append(this);
		break;
	case ShapeDescendants:
		selected.append(this);
		foreach (node, m_children)
			selected.append(node->shapes(selection));
		break;
	}
	return selected;
}

ShapeList ShapeNode::siblings() const
{
	 if (m_parent) {
		 ShapeList nodes = m_parent->children();
		 nodes.removeOne(const_cast<ShapeNode*>(this));
		 return nodes;
	 }
	 else return ShapeList();
}

int ShapeNode::depth() const
{
	int toRoot = 0;
	for (ShapeNode* node = const_cast<ShapeNode*>(this); node != 0; node = node->m_parent)
		toRoot++;
	return toRoot -1;
}

QString ShapeNode::toolTip() const
{
	return tr("Depth: %1\nDescendants: %2\nSiblings: %3\nOccurences: %4\nPixmap size: %5x%6")
			.arg(depth()).arg(childrenCount(true)).arg(siblings().count())
			.arg(m_blits.count()).arg(size().width()).arg(size().height());
}

void ShapeNode::clear()
{
	m_children.clear();
	m_blits.clear();
	m_parent = 0;
}

void ShapeNode::sortChildren(bool recursively)
{
	qSort(m_children.begin(), m_children.end(), ShapeNode::smallerThan);
	if (recursively)
		for (int i = 0; i < m_children.count(); i++)
			m_children[i]->sortChildren(true);
}

void ShapeNode::addBlit(const Blit &blit)
{
	 m_blits.append(blit);
}

bool ShapeNode::biggerThan(ShapeNode * n1, ShapeNode *n2)
{
	 if (!n1)
		 return false;
	 else if (!n2)
		 return true;
	 else if (n1->pixmap().width() == n2->pixmap().width())
		 return n1->pixmap().height() > n2->pixmap().height();
	 else return n1->pixmap().width() > n2->pixmap().width();
}

bool ShapeNode::smallerThan(ShapeNode * n1, ShapeNode *n2)
{
	 if (!n1)
		 return false;
	 else if (!n2)
		 return true;
	 else if (n1->pixmap().width() == n2->pixmap().width())
		 return n1->pixmap().height() < n2->pixmap().height();
	 else return n1->pixmap().width() < n2->pixmap().width();
}

