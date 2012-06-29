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
	m_document = document;
}

int ShapeExtractor::pages() const
{
	return ddjvu_document_get_pagenum(*m_document);
}

ShapeList ShapeExtractor::extract(ShapeNode *root)
{
	int maxPages = QSettings().value("Display/pages", 20).toInt();
	return extract(root, 0, qMin(maxPages, pages()));
}

ShapeList ShapeExtractor::extract(ShapeNode *root, int firstPage, int pageCount)
{
	ShapeList shapes;

	if (!m_document)
		return shapes;

	m_pixmaps.clear();
	QTime elapsed;
	elapsed.start();
	emit progress(0);
	for (int page = 0; page < pageCount; page++) {
		shapes.append(extractPage(firstPage + page, root));
		emit progress((page + 1) * 100 / pageCount);
	}
	qDebug("Time elapsed: %f", elapsed.elapsed() / 1000.0);
	return shapes;
}

ShapeList ShapeExtractor::extractPage(int pageno, ShapeNode *root)
{
	ShapeList pageShapes;
	ShapeList newShapes;

	struct DJVU::ddjvu_page_s* page = reinterpret_cast<DJVU::ddjvu_page_s *>(
				ddjvu_page_create_by_pageno(*m_document, pageno));

	if (!page) {
		qWarning("Cound not render djvupage, page %d", pageno);
		return pageShapes;
	}

	GP<DjVuImage> img = ddjvu_get_DjVuImage(page);
	if (!img) {
		qWarning("Cound not render djvuimage, page %d", pageno);
		return pageShapes;
	}

	if (!img->wait_for_complete_decode())
		return pageShapes;

	GP<JB2Image> jimg = img->get_fgjb();
	if (!jimg) {
		qWarning("Cound not get fbjb, page %d", pageno);
		return pageShapes;
	}

	int shared = 0;

	int shapesCount = jimg->get_shape_count();
	for (int i = 0; i < shapesCount; i++) {
		JB2Shape shape = jimg->get_shape(i);

		ShapeNode* parent = root;
		if (shape.parent >= 0 && shape.parent < pageShapes.count())
			parent = pageShapes[shape.parent];

		GP<GBitmap> bits = shape.bits;
		if (!bits)
			continue;
		GP<ByteStream> bs = ByteStream::create();
		bits->save_pbm(*bs);
		TArray<char> array = bs->get_data();

		QPixmap pixmap;
		pixmap.loadFromData(reinterpret_cast<const uchar*>((char*)array), array.size());
		pixmap.setMask(pixmap.createMaskFromColor(Qt::white, Qt::MaskInColor)); //add transparency

		// Look for existing pixmaps
		QByteArray pattern(reinterpret_cast<const char*>((char*)array), array.size());
		if (m_pixmaps.contains(pattern)) {
			shared++;
			pageShapes.append(m_pixmaps[pattern]);
		}
		else {
			ShapeNode* newShape = new ShapeNode(parent, pixmap);
			newShapes.append(newShape);
			pageShapes.append(newShape);
			m_pixmaps.insert(pattern, newShape);
		}
	}

	// now put blits
	int blitCount = jimg->get_blit_count();
	for (int i = 0; i < blitCount; i++) {
		JB2Blit *blit = jimg->get_blit(i);
		if (blit && int(blit->shapeno) < pageShapes.count())
			pageShapes[blit->shapeno]->addBlit(Blit(pageno, blit->left, blit->bottom,
																 pageShapes[blit->shapeno]->size()));
	}

	qDebug("%d images on page %d: %d shared, %d new", shapesCount, pageno+1,
			 shared, newShapes.count());
	return newShapes;
}




