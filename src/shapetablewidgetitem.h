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

#ifndef SHAPETABLEWIDGETITEM_H
#define SHAPETABLEWIDGETITEM_H

#include "shapenode.h"

class ShapeTableWidgetItem : public QTableWidgetItem
{
public:
	 ShapeTableWidgetItem(ShapeNode *node);
	 ShapeNode *node;
};

#endif // SHAPETABLEWIDGETITEM_H
