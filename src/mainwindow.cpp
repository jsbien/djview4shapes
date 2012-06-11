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

#include "mainwindow.h"
#include "messagedialog.h"
#include "qdjvu.h"
#include "qdjvuhttp.h"
#include "version.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	ui.setupUi(this);

	setupActions();
	setWindowTitle(m_applicationName);
	show();
	restoreSettings();

}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (queryClose())
		saveSettings();
	else event->ignore();
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
	settings.endGroup();
}

void MainWindow::saveSettings()
{
	QSettings settings;
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
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





void MainWindow::setupActions()
{
	// Help menu
	connect(ui.actionHelpAbout, SIGNAL(triggered()), this,
			  SLOT(showAboutDialog()));
}

const QString MainWindow::m_applicationName = QT_TR_NOOP("DjView Shapes");



