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
#include "blit.h"
#include "shapelist.h"

class ShapeNode
{
public:
	 ShapeNode(ShapeNode *m_parent, QPixmap pixmap);
	 ShapeNode() : m_parent(0) {}
	 /** @return current pixmap. */
	 const QPixmap& pixmap() { return m_pixmap; }
	 /** @return the pixmap of shape scaled to at most @p maxsize. */
	 QPixmap scaledPixmap(const QSize& maxSize) const;
	 /** @return the list of children. */
	 ShapeList children() const {return m_children;}
	 /** @return the list of all other children of the same parent. */
	 ShapeList siblings() const;
	 /** @return distance to root. */
	 int depth() const;
	 /** @return basic information about the node. */
	 QString toolTip() const;

	 // Blits
	 const QList<Blit>& blits() { return m_blits; }
	 void addBlit(const Blit& blit);
	 static bool widerThan(ShapeNode * n1, ShapeNode *n2);
private:
	 ShapeNode *m_parent;
	 ShapeList m_children;
	 QPixmap m_pixmap;
	 QList<Blit> m_blits;

	 Q_DECLARE_TR_FUNCTIONS(ShapeNode)
};

#endif // SHAPENODE_H
