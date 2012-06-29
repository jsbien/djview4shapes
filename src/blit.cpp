/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "blit.h"

Blit::Blit()
{
	m_page = -1;
}

Blit::Blit(int page, int left, int top, const QSize& size)
{
	m_page = page;
	m_rect.setLeft(left);
	m_rect.setTop(top);
	m_rect.setSize(size);
}
