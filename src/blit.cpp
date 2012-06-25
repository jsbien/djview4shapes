/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "blit.h"

Blit::Blit()
{
	m_page = m_left = m_bottom = 0;
}

Blit::Blit(int page, int left, int bottom)
{
	m_page = page;
	m_left = left;
	m_bottom = bottom;
}
