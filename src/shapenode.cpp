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

#include "shapenode.h"

ShapeNode::ShapeNode(ShapeNode *parent, int id, QPixmap pixmap) :
	m_id(id), m_pixmap(pixmap)
{
	 setParent(parent);
}

void ShapeNode::setParent(ShapeNode *parent)
{
	m_parent = parent;
	if (m_parent)
		m_parent->m_children.append(this);
}

ShapeNode::~ShapeNode()
{
	qDeleteAll(m_children);
}

QList<ShapeNode *> ShapeNode::siblings()
{
	 if (m_parent) {
		  QList<ShapeNode*> nodes = QList<ShapeNode *>(m_parent->children());
		  nodes.removeOne(this);
		  return nodes;
	 }
	 else return QList<ShapeNode*>();
}

void ShapeNode::addBlit(unsigned short left, unsigned short bottom)
{
	 m_blits.append(qMakePair(left, bottom));
}

bool ShapeNode::greaterThan(ShapeNode * n1, ShapeNode *n2)
{
	 if (!n1 || !n2)
		  return false;

	 return n1->pixmap().size().width() > n2->pixmap().size().width();
}
