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
	m_id(id), m_pixmap(pixmap), m_item(0)
{
	 setParent(parent);
}

void ShapeNode::setParent(ShapeNode *parent)
{
	 this->m_parent = parent;

	 if (parent)
		  parent->m_children.append(this);
}

ShapeNode::~ShapeNode()
{
	qDeleteAll(m_children);
}

QList<ShapeNode *> ShapeNode::getSiblings()
{
	 if (m_parent == NULL)
		  return QList<ShapeNode *>();
	 else {
		  QList<ShapeNode *> ret = QList<ShapeNode *>(m_parent->getChildren());
		  ret.removeOne(this);
		  return ret;
	 }
}

int ShapeNode::calculateTreeHeights(int from_root)
{
	 m_distanceToRoot = from_root;
	 m_distanceToLeaf = 0;
	 for (QList<ShapeNode *>::iterator i = m_children.begin(); i != m_children.end(); ++i) {
		  int to_leaf = (*i)->calculateTreeHeights(from_root + 1);
		  m_distanceToLeaf = to_leaf > m_distanceToLeaf ? to_leaf : m_distanceToLeaf;
	 }

	 return m_distanceToLeaf + 1;
}

void ShapeNode::addBlit(unsigned short left, unsigned short bottom)
{
	 m_blits.append(qMakePair(left, bottom));
}

bool ShapeNode::greaterThan(ShapeNode * n1, ShapeNode *n2)
{
	 if (!n1 || !n2)
		  return false;

	 return n1->getPixmap().size().width() > n2->getPixmap().size().width();
}
