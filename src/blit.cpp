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

QString Blit::link() const
{
	QString args;
	args.append(QString("?djvuopts=&page=%1").arg(page() + 1));
	args.append(QString("&highlight=%1,%2,%3,%4")
					.arg(left()).arg(top()).arg(width()).arg(height()));
	return args;
//		else if (arg.first == "showposition") {
//			m_position.setX(arg.second.section(QRegExp("[.,]"), 1, 1).toInt());
//			m_position.setY(arg.second.section(QRegExp("[.,]"), 3, 3).toInt());
}
