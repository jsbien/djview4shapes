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

	int sh_count = jimg->get_shape_count();
	int blit_count = jimg->get_blit_count();

//	progress->setMaximum(sh_count + blit_count);
//	progress->show();

	QVector<ShapeNode *> shapes_nodes(sh_count);
	QMultiHash<int, int> shapes_children;
	//QSize boundingShapeSize(0, 0);
	for (int i = 0; i < sh_count; i++) {
		JB2Shape shape = jimg->get_shape(i);
		/*if (!shape)
					continue;*/

		int idx = shape.parent >= 0 ? shape.parent : -1;
		shapes_children.insert(idx, i);

		GP<GBitmap> bits = shape.bits;
		if (!bits)
			continue;
		GP<ByteStream> bs = ByteStream::create();
		bits->save_pbm(*bs);
		TArray<char> array = bs->get_data();

		ShapeNode * node = new ShapeNode(i);
		node->getPixmap().loadFromData(reinterpret_cast<const uchar*>((char*)array), array.size());
		node->getPixmap().setMask(node->getPixmap().createMaskFromColor(Qt::white, Qt::MaskInColor)); //add transparency
		//boundingShapeSize = boundingShapeSize.expandedTo(node->getPixmap().size());

		shapes_nodes[i] = node;
//		progress->setValue(i);
	}

	// now put blits
	for (int i = 0; i < blit_count; i++) {
		JB2Blit *blit = jimg->get_blit(i);
		if (blit && shapes_nodes[blit->shapeno]) {
			shapes_nodes[blit->shapeno]->addBlit(blit->left, blit->bottom);
			//qDebug("blit %d %u %u %u", i, blit->left, blit->bottom, blit->shapeno);
		}
//		progress->setValue(i + sh_count);
	}

	QMultiHash<int, int>::iterator itr;

	//set parentness
	for (int parent_id = 0; parent_id < sh_count; parent_id++) {
		itr = shapes_children.find(parent_id);
		while (itr != shapes_children.end() && itr.key() == parent_id) {
			if (shapes_nodes[itr.value()])
				shapes_nodes[itr.value()]->setParent(shapes_nodes[parent_id]);
			++itr;
		}
	}

	//find root shapes
	itr = shapes_children.find(-1);
	while (itr != shapes_children.end() && itr.key() == -1) {
		if (shapes_nodes[itr.value()]) {
			m_shapes.append(shapes_nodes[itr.value()]);
			shapes_nodes[itr.value()]->calculateTreeHeights();

			//DEBUG
			//if (shapes_nodes[itr.value()]->getToRootHeight() || shapes_nodes[itr.value()]->getToLeafHeight()) {
			//    *itr;
			//}
		}
		++itr;
	};
//	roots.first = sh_count;

	qSort(m_shapes.begin(), m_shapes.end(), ShapeNode::greaterThan);
//	progress->hide();

	qDebug("Grabed %d shapes for page %d", sh_count, pageno);
	return true;
}

ShapeNode *ShapeExtractor::node(int i) const
{
	return m_shapes[i];
}

int ShapeExtractor::nodeCount()
{
	return m_shapes.count();
}



