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

Shape::Shape(Shape *parent, int id, QPixmap pixmap) :
	m_id(id), m_pixmap(pixmap)
{
	 setParent(parent);
}

void Shape::setParent(Shape *parent)
{
	m_parent = parent;
	if (m_parent)
		m_parent->m_children.append(this);
}

Shape::~Shape()
{
	qDeleteAll(m_children);
}

ShapeList Shape::siblings()
{
	 if (m_parent) {
		  ShapeList nodes = m_parent->children();
		  nodes.removeOne(this);
		  return nodes;
	 }
	 else return ShapeList();
}

void Shape::addBlit(unsigned short left, unsigned short bottom)
{
	 m_blits.append(qMakePair(left, bottom));
}

bool Shape::greaterThan(Shape * n1, Shape *n2)
{
	 if (!n1 || !n2)
		  return false;

	 return n1->pixmap().size().width() > n2->pixmap().size().width();
}
