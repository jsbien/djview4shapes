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
	void open(QDjVuDocument* document);
	void close() {m_document = 0;}
	bool extract(int page);
	ShapeNode* node(int i) const;
	int nodeCount();
private:
	QDjVuDocument* m_document;
	QVector<ShapeNode*> m_shapes;
};

#endif // SHAPEEXTRACTOR_H
