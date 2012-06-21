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

class Shape
{
public:
	 Shape(Shape *m_parent, int id, QPixmap pixmap);
	 Shape(int id, QPixmap pixmap) : m_id(id), m_parent(0), m_pixmap(pixmap) {}
	 Shape(int id) : m_id(id), m_parent(0) {}
	 ~Shape();

	 QPixmap& pixmap() { return m_pixmap; }

	 QList<Shape *> children() {return m_children;}
	 QList<Shape *> siblings();
	 Shape * getParent() { return m_parent; }

	 // Blits
	 QList<QPair<unsigned short, unsigned short> > blits() { return m_blits; }
	 void addBlit(unsigned short left, unsigned short bottom);

	 void setParent(Shape *m_parent);

	 static bool greaterThan(Shape * n1, Shape *n2);
private:
	 int m_id;
	 Shape *m_parent;
	 QPixmap m_pixmap;
	 QList<Shape*> m_children;
	 QList<QPair<unsigned short, unsigned short> > m_blits;
};

#endif // SHAPENODE_H
