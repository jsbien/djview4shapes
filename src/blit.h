/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef BLIT_H
#define BLIT_H

#include "qdjvuwidget.h"

class Blit
{
public:
	Blit();
	Blit(int page, int left, int top, const QSize& size);
	bool isValid() const {return m_page >= 0 && m_rect.width() > 0;}
	int page() const {return m_page;}
	QPoint position() const {return m_rect.topLeft();}
	QDjVuWidget::Position djvuPosition() const;
	int left() const {return m_rect.x();}
	int top() const {return m_rect.y();}
	int width() const {return m_rect.width();}
	int height() const {return m_rect.height();}
	QSize size() const {return m_rect.size();}
	QRect rect() const {return m_rect;}
	/** @return link for DjView. */
	QString link() const;
private:
	int m_page;
	QRect m_rect;
};

#endif // BLIT_H
