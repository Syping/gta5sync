/*****************************************************************************
* gta5sync GRAND THEFT AUTO V SYNC
* Copyright (C) 2016 Syping Gaming Team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "ProfileInterface.h"
#include "ui_ProfileInterface.h"
#include "SnapmaticWidget.h"
#include "SavegameWidget.h"
#include <QFileInfo>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QDir>

ProfileInterface::ProfileInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileInterface)
{
    ui->setupUi(this);
    contentStr = ui->labProfileContent->text();
    profileFolder = "";
}

ProfileInterface::~ProfileInterface()
{
    delete ui;
}

void ProfileInterface::setProfileFolder(QString folder, QString profile)
{
    profileFolder = folder;
    profileName = profile;
}

void ProfileInterface::setupProfileInterface()
{
    QDir profileDir;
    profileDir.setPath(profileFolder);
    ui->labProfileContent->setText(contentStr.arg(profileName));

    profileDir.setNameFilters(QStringList("PGTA*"));
    QStringList SnapmaticPics = profileDir.entryList(QDir::Files | QDir::NoDot, QDir::NoSort);
    foreach(const QString &SnapmaticPic, SnapmaticPics)
    {
        QString picturePath = profileFolder + "/" + SnapmaticPic;
        SnapmaticPicture *picture = new SnapmaticPicture(picturePath);
        if (picture->readingPicture())
        {
            SnapmaticWidget *picWidget = new SnapmaticWidget(ui->saSnapmaticContent);
            picWidget->setSnapmaticPicture(picture, picturePath);
            ui->saSnapmaticContent->layout()->addWidget(picWidget);
        }
    }

    profileDir.setNameFilters(QStringList("SGTA*"));
    QStringList SavegameFiles = profileDir.entryList(QDir::Files | QDir::NoDot, QDir::NoSort);
    qDebug() << SavegameFiles;
}