/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef BLIT_H
#define BLIT_H

#include <QtCore>


class Blit
{
public:
	Blit();
	Blit(int page, int left, int top);
	bool isValid() const {return m_page >= 0;}
	int page() const {return m_page;}
	QPoint position() const {return m_position;}
	int left() const {return m_position.x();}
	int top() const {return m_position.y();}
private:
	int m_page;
	QPoint m_position;
};

#endif // BLIT_H
