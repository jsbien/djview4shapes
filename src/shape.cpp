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
	if (m_pixmap.width() > maxSize.width() || m_pixmap.height() > maxSize.width())
		return m_pixmap.scaled(maxSize, Qt::KeepAspectRatio);
	else return m_pixmap;
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
	return tr("Depth: %1\nChildren: %2\nSiblings: %3\nOccurences: %4").arg(depth())
			.arg(m_children.count()).arg(siblings().count()).arg(m_blits.count());
}

void ShapeNode::addBlit(const Blit &blit)
{
	 m_blits.append(blit);
}

bool ShapeNode::widerThan(ShapeNode * n1, ShapeNode *n2)
{
	 if (!n1 || !n2)
		  return false;

	 return n1->pixmap().size().width() > n2->pixmap().size().width();
}
