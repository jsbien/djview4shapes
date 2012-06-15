/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEEXTRACTOR_H
#define SHAPEEXTRACTOR_H

#include "shapenode.h"
#include "qdjvu.h"

class ShapeExtractor : public QObject
{
	Q_OBJECT
public:
	ShapeExtractor(QObject* parent = 0);
	bool open(QDjVuDocument* document);
	void close() {m_document = 0;}
	void extract(int page);
private:
	QDjVuDocument* m_document;
	QList<ShapeNode*> m_shapes;
};

#endif // SHAPEEXTRACTOR_H
