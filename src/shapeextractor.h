/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef SHAPEEXTRACTOR_H
#define SHAPEEXTRACTOR_H

#include "shape.h"
#include "qdjvu.h"

class ShapeExtractor : public QObject
{
	Q_OBJECT
public:
	ShapeExtractor(QObject* parent = 0);
	void open(QDjVuDocument* document);
	int pages() const;
	void close() {m_document = 0;}
	ShapeList extract(ShapeNode* root);
private:
	ShapeList extractPage(int pageno, ShapeNode* root);
	QDjVuDocument* m_document;
};

#endif // SHAPEEXTRACTOR_H
