/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapeextractor.h"
#include "config.h"
#include <libdjvu/DjVuImage.h>
#include <libdjvu/DjVuDocument.h>
#include <libdjvu/JB2Image.h>
#include <libdjvu/ByteStream.h>
#include <libdjvu/GBitmap.h>
#include <libdjvu/ddjvuapi.h>
#include <libdjvu/miniexp.h>

namespace DJVU
{
struct ddjvu_page_s;
}

GP<DjVuImage> ddjvu_get_DjVuImage(DJVU::ddjvu_page_s *page);


ShapeExtractor::ShapeExtractor(QObject* parent) : QObject(parent)
{
	m_document = 0;
}

void ShapeExtractor::open(QDjVuDocument *document)
{
	qDeleteAll(m_shapes);
	m_shapes.clear();
	m_document = document;
}

bool ShapeExtractor::extract(int pageno)
{
	if (!m_document)
		return false;

	struct DJVU::ddjvu_page_s* page = reinterpret_cast<DJVU::ddjvu_page_s *>(
				ddjvu_page_create_by_pageno(*m_document, pageno));

	if (!page) {
		qWarning("Cound not render djvupage, page %d", pageno);
		return false;
	}

	GP<DjVuImage> img = ddjvu_get_DjVuImage(page);
	if (!img) {
		qWarning("Cound not render djvuimage, page %d", pageno);
		return false;
	}

	if (!img->wait_for_complete_decode())
		return false;

	GP<JB2Image> jimg = img->get_fgjb();
	if (!jimg) {
		qWarning("Cound not get fbjb, page %d", pageno);
		return false;
	}


	QVector<Shape*> shapes;
	int shapesCount = jimg->get_shape_count();
	for (int i = 0; i < shapesCount; i++) {
		JB2Shape shape = jimg->get_shape(i);

		Shape* parent = 0;
		if (shape.parent >= 0 && shape.parent < shapes.count())
			parent = shapes[shape.parent];

		GP<GBitmap> bits = shape.bits;
		if (!bits)
			continue;
		GP<ByteStream> bs = ByteStream::create();
		bits->save_pbm(*bs);
		TArray<char> array = bs->get_data();

		QPixmap pixmap;
		pixmap.loadFromData(reinterpret_cast<const uchar*>((char*)array), array.size());
		pixmap.setMask(pixmap.createMaskFromColor(Qt::white, Qt::MaskInColor)); //add transparency
		//boundingShapeSize = boundingShapeSize.expandedTo(node->getPixmap().size());
		shapes.append(new Shape(parent, i, pixmap));
	}

	// now put blits
	int blitCount = jimg->get_blit_count();
	for (int i = 0; i < blitCount; i++) {
		JB2Blit *blit = jimg->get_blit(i);
		if (blit && int(blit->shapeno) < shapes.count())
			shapes[blit->shapeno]->addBlit(blit->left, blit->bottom);
	}

	m_shapes = shapes;

	qSort(m_shapes.begin(), m_shapes.end(), Shape::greaterThan);
	qDebug("Grabed %d shapes for page %d", shapesCount, pageno);
	return true;
}

Shape *ShapeExtractor::node(int i) const
{
	return m_shapes[i];
}

int ShapeExtractor::nodeCount()
{
	return m_shapes.count();
}



