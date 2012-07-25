/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf
*   This software is subject to, and may be distributed under, the
*   GNU General Public License, either version 2 of the license,
*   or (at your option) any later version. The license should have
*   accompanied the software or you may obtain a copy of the license
*   from the Free Software Foundation at http://www.fsf.org .

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
****************************************************************************/

#include "blit.h"
#include "helpdialog.h"
#include "mainwindow.h"
#include "messagedialog.h"
#include "qdjvu.h"
#include "qdjvuhttp.h"
#include "version.h"
#include "preferencesdialog.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), m_helpDialog(0)
{
	m_context = new QDjVuContext("djvu-shapes", this);
	m_document = 0;

	ui.setupUi(this);
	ui.progressBar->hide();

	setupActions();
	setWindowTitle(m_applicationName);

	connect(ui.shapeWidget, SIGNAL(progress(int)), this, SLOT(progress(int)));
	connect(ui.shapeWidget, SIGNAL(showOccurences(ShapeList)), ui.djvuWidget,
			  SLOT(showOccurences(ShapeList)));
	connect(ui.shapeWidget, SIGNAL(showOccurences(ShapeList)), ui.previewWidget,
			  SLOT(showItems(ShapeList)));

	connect(ui.previewWidget, SIGNAL(blitRequested(Blit)), this,
			  SLOT(showBlit(Blit)));
	connect(ui.previewWidget, SIGNAL(documentRequested(Blit)), this,
			  SLOT(launchDjview(Blit)));

	connect(ui.djvuWidget, SIGNAL(clicked(int,QPoint)), ui.shapeWidget,
			 SLOT(findShapes(int,QPoint)));
	show();
	restoreSettings();
}

void MainWindow::openFile(const QString &filename)
{
	if (m_document) {
		ui.djvuWidget->setDocument(0);
		ui.shapeWidget->close();
	}
	m_document = new QDjVuDocument(this);
	connect(m_document, SIGNAL(docinfo()), this, SLOT(documentLoaded()));
	if (!m_document->setFileName(m_context, filename)) {
		MessageDialog::warning(tr("Cannot read file: %1").arg(filename));
		m_document->deleteLater();
		m_document = 0;
		m_recentFiles.removeFile(filename);
	}
	else m_recentFiles.addFile(m_filename = filename);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (queryClose())
		saveSettings();
	else event->ignore();
}

HelpDialog *MainWindow::helpDialog()
{
	if (!m_helpDialog)
		m_helpDialog = new HelpDialog(this);
	return m_helpDialog;
}

bool MainWindow::queryClose()
{
	return true;
}

void MainWindow::restoreSettings()
{
	QSettings settings;
	settings.beginGroup("MainWindow");
	resize(settings.value("size", size()).toSize());
	ui.splitter->restoreState(settings.value("splitter").toByteArray());
	settings.endGroup();
}

void MainWindow::saveSettings()
{
	QSettings settings;
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("splitter", ui.splitter->saveState());
	settings.endGroup();
}

void MainWindow::showAboutDialog()
{
	QString build = Version::buildNumber() ? tr(" (build %1)")
														  .arg(Version::buildText()) : "";
	QString about = tr("%1\nVersion %2 %3\n(c) Michal Rudolf 2012")
					.arg(m_applicationName).arg(Version::versionText()).arg(build);
	QMessageBox::about(this, tr("About application"), about);
}

void MainWindow::documentLoaded()
{
	ui.djvuWidget->setDocument(m_document);
	ui.shapeWidget->open(m_document);
	ui.previewWidget->setDocument(m_document);
}

void MainWindow::progress(int percentage)
{
	ui.progressBar->setValue(percentage);
	ui.progressBar->setVisible(percentage < 100);
}

void MainWindow::exportPixmaps()
{
	QString saveFile = MessageDialog::saveFile(tr("Images (*.png)"), tr("Base image name"), "export");
	if (saveFile.isEmpty())
		return;

	int extension = saveFile.lastIndexOf('.');
	if (extension != -1)
		saveFile = saveFile.left(extension);
	saveFile.append("-%1.png");

	ShapeList items = ui.shapeWidget->selectedOccurences();
	for (int i = 0; i < items.count(); i++)
		items.at(i)->pixmap().save(saveFile.arg(i+1));
}

void MainWindow::configure()
{
	PreferencesDialog dlg(this);
	if (dlg.exec()) {
		dlg.saveSettings();
		ui.shapeWidget->configure();
	}
}

void MainWindow::showBlit(const Blit &blit)
{
	QPoint centered = QPoint(ui.djvuWidget->width() / 2,
									 ui.djvuWidget->height() / 2);
	ui.djvuWidget->setPosition(blit.djvuPosition(), centered);
}

void MainWindow::launchDjview(const Blit &blit)
{
	QString cmd = QSettings().value("Tools/djviewPath", "djview").toString();
	QStringList args;
	args.append(QString("file://") + m_filename + blit.link());
	if (!QProcess::startDetached(cmd, args)) {
		QString msg = tr("Cannot execute program:") + "<br><i>%1</i>";
		MessageDialog::warning(msg.arg(cmd));
	}

}

void MainWindow::toggleHelp()
{
	helpDialog()->setVisible(ui.actionHelp->isChecked());
}

void MainWindow::setupActions()
{
	m_recentFiles.plug(ui.actionFileRecent);


	// File menu
	connect(ui.actionFileOpen, SIGNAL(triggered()), this,
			  SLOT(selectFileToOpen()));
	connect(&m_recentFiles, SIGNAL(selected(QString)), this,
			  SLOT(openFile(QString)));

	// Settings menu
	connect(ui.actionConfigure, SIGNAL(triggered()), this,
			  SLOT(configure()));

	// Help menu
	connect(ui.actionHelp, SIGNAL(toggled(bool)), this, SLOT(toggleHelp()));
	connect(ui.actionHelpAbout, SIGNAL(triggered()), this,
			  SLOT(showAboutDialog()));

	// Shape widget menu
	QAction* exportAction = new QAction(tr("Export images"), this);
	connect(exportAction, SIGNAL(triggered()), this, SLOT(exportPixmaps()));
	ui.shapeWidget->addAction(exportAction);
}


void MainWindow::selectFileToOpen()
{
	QString filename = MessageDialog::openFile(tr("DjVu files (*.djvu)"),
															 tr("Open file"), "open");
	if (!filename.isEmpty())
		openFile(filename);
}


const QString MainWindow::m_applicationName = QT_TR_NOOP("DjView Shapes");

