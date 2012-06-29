/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "preferencesdialog.h"
#include <QtGui>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
	 QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.highlightButton, SIGNAL(clicked()), this, SLOT(selectHighlightColor()));

	restoreSettings();
}

void PreferencesDialog::updateHighlightColor()
{
	QRect rect = ui.highlightButton->rect();
	QPixmap icon(rect.size() - QSize(10, 10));
	QPainter painter(&icon);
	painter.fillRect(0, 0, rect.width() - 8, rect.height() - 8, Qt::black);
	painter.fillRect(1, 1, rect.width() - 10, rect.height() - 10, m_highlight);
	ui.highlightButton->setIcon(QIcon(icon));
	ui.highlightButton->setIconSize(icon.size());
}

void PreferencesDialog::selectHighlightColor()
{
	QColorDialog dlg(this);
	if (dlg.exec()) {
		m_highlight = dlg.currentColor();
		updateHighlightColor();
	}
}

void PreferencesDialog::restoreSettings()
{
	QSettings settings;
	ui.pathEdit->setText(settings.value("Tools/djviewPath", "djview").toString());
	ui.previewHeightSpin->setValue(settings.value("Display/previewHeight", 40).toInt());
	ui.maxPageSpin->setValue(settings.value("Display/pages", 20).toInt());
	m_highlight = QColor(settings.value("Display/highlight", "#ffff00").toString());

	updateHighlightColor();
}

void PreferencesDialog::saveSettings()
{
	QSettings settings;
	settings.setValue("Tools/djviewPath", ui.pathEdit->text());
	settings.setValue("Display/previewHeight", ui.previewHeightSpin->value());
	settings.setValue("Display/pages", ui.maxPageSpin->value());
	settings.setValue("Display/highlight", m_highlight.name());
}
