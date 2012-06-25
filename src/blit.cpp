/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "blit.h"

Blit::Blit()
{
	m_page = 0;
}

Blit::Blit(int page, int left, int top)
{
	m_page = page;
	m_position = QPoint(left, top);
}
