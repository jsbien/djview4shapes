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

#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>
#include "shapelist.h"

class ShapeNode
{
public:
	 ShapeNode(ShapeNode *m_parent, QPixmap pixmap);
	 ShapeNode() : m_parent(0) {}

	 QPixmap& pixmap() { return m_pixmap; }

	 ShapeList children() {return m_children;}
	 ShapeList siblings();
	 ShapeNode * getParent() { return m_parent; }

	 // Blits
	 QList<QPair<unsigned short, unsigned short> > blits() { return m_blits; }
	 void addBlit(unsigned short left, unsigned short bottom);
	 static bool greaterThan(ShapeNode * n1, ShapeNode *n2);
private:
	 ShapeNode *m_parent;
	 ShapeList m_children;
	 QPixmap m_pixmap;
	 QList<QPair<unsigned short, unsigned short> > m_blits;
};

#endif // SHAPENODE_H
