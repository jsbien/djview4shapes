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
	Blit(int page, int left, int top, const QSize& size);
	bool isValid() const {return m_page >= 0 && m_rect.width() > 0;}
	int page() const {return m_page;}
	QPoint position() const {return m_rect.topLeft();}
	int left() const {return m_rect.x();}
	int top() const {return m_rect.y();}
	QSize size() const {return m_rect.size();}
	QRect rect() const {return m_rect;}
private:
	int m_page;
	QRect m_rect;
};

#endif // BLIT_H
