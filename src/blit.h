/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef BLIT_H
#define BLIT_H

class Blit
{
public:
	Blit();
	Blit(int page, int left, int top);
	int page() const {return m_page;}
	int left() const {return m_left;}
	int top() const {return m_top;}
private:
	int m_page;
	int m_left;
	int m_top;
};

#endif // BLIT_H
