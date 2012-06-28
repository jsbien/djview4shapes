/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "shapepreviewlist.h"
#include "qdjvuwidget.h"

ShapePreviewList::ShapePreviewList(QWidget *parent) :
	QScrollArea(parent)
{
	QWidget* main = new QWidget;
	main->setLayout(m_layout = new QGridLayout);
	setWidget(main);
	setWidgetResizable(true);

	m_document = 0;
	m_currentItem = -1;
}

void ShapePreviewList::setDocument(QDjVuDocument *document)
{
	m_document = document;
	clear();
}

void ShapePreviewList::setItems(ShapeNode *node)
{
	clear();
	ShapeList list = node->shapes(ShapeNode::ShapeDescendants);
	foreach (ShapeNode* item, list)
		foreach (Blit blit, item->blits())
			addItem(item, blit);
	m_layout->setRowStretch(m_items.count(), 100);
}

void ShapePreviewList::clear()
{
	m_layout->setRowStretch(m_items.count(), 0);
	for (int i = 0; i < m_items.count(); i++) {
		m_items[i].label->deleteLater();
		m_items[i].djvu->setDocument(0);
		m_items[i].djvu->deleteLater();
	}
	m_items.clear();
	m_currentItem = -1;
}

void ShapePreviewList::setCurrentIndex(int index)
{
	if (m_currentItem == index)
		return;
	if (m_currentItem != -1)
		m_items[m_currentItem].label->setStyleSheet("");
	if (index < 0 || index >= m_items.count()) {
		m_currentItem = -1;
		return;
	}

	QString style = QString("color: %1; background-color: %2; font-weight: bold")
			.arg(QApplication::palette().color(QPalette::HighlightedText).name())
			.arg(QApplication::palette().color(QPalette::Highlight).name());

	m_items[index].label->setStyleSheet(style);
	ensureWidgetVisible(m_items[index].djvu);
	emit currentIndexChanged(m_currentItem = index);
}

void ShapePreviewList::updateCurrentItem()
{
	if (ShapePreview* preview = dynamic_cast<ShapePreview*>(sender()))
		setCurrentIndex(preview->data().toInt());
}

void ShapePreviewList::configure()
{
	for (int i = 0; i < count(); i++)
		m_items[i].djvu->configure();
}

void ShapePreviewList::addItem(ShapeNode* node, const Blit &blit)
{
	int row = m_items.count();

	ShapeItem item;
	item.label = new QLabel(QString(" %1 ")
									.arg(row+1), widget());
	item.label->installEventFilter(this);
	item.djvu = new ShapePreview(widget());
	item.djvu->setDocument(m_document);
	item.djvu->setData(m_items.count());
	connect(item.djvu, SIGNAL(activated()), this, SLOT(updateCurrentItem()));
	connect(item.djvu, SIGNAL(pageRequested(int)), this, SIGNAL(pageRequested(int)));
	item.djvu->setBlit(node, blit);

	m_layout->addWidget(item.label, row, 0);
	m_layout->addWidget(item.djvu, row, 1);
	m_items.append(item);
	adjustSize();
}



