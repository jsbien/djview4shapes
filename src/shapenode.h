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

#ifndef SHAPENODE_H
#define SHAPENODE_H

#include <QtGui>

class ShapeTableWidgetItem;

class ShapeNode
{
public:
	 ShapeNode(ShapeNode *m_parent, int id, QPixmap pixmap);
	 ShapeNode(int id, QPixmap pixmap) : m_id(id), m_parent(0), m_pixmap(pixmap) {}
	 ShapeNode(int id) : m_id(id), m_parent(0) {}
	 ~ShapeNode();

	 int getId() { return m_id; }
	 QPixmap& getPixmap() { return m_pixmap; }

	 QList<ShapeNode *> children() {return m_children;}
	 QList<ShapeNode *> siblings();
	 ShapeNode * getParent() { return m_parent; }

	 QList<QPair<unsigned short, unsigned short> > getBlits() { return m_blits; }
	 void addBlit(unsigned short left, unsigned short bottom);

	 void setParent(ShapeNode *m_parent);

	 void calculateTreeHeights() { calculateTreeHeights(0); }
	 int getToRootHeight() { return m_distanceToRoot; }
	 int getToLeafHeight() { return m_distanceToLeaf; }

	 static bool greaterThan(ShapeNode * n1, ShapeNode *n2);
private:
	 int m_id;
	 ShapeNode *m_parent;
	 QPixmap m_pixmap;
	 QList<ShapeNode*> m_children;
	 QList<QPair<unsigned short, unsigned short> > m_blits;
	 int m_distanceToRoot;
	 int m_distanceToLeaf;

	 int calculateTreeHeights(int from_root);
};

#endif // SHAPENODE_H
