/*****************************************************************************
* gta5sync GRAND THEFT AUTO V SYNC
* Copyright (C) 2016-2018 Syping
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

#ifndef APPENV_H
#define APPENV_H

#include <QString>
#include <QUrl>

class AppEnv
{
public:
    AppEnv();

    // Build Stuff
    static QString getBuildDateTime();

    // Folder Stuff
    static QString getGameFolder(bool *ok = 0);
    static bool setGameFolder(QString gameFolder);
    static QString getExLangFolder();
    static QString getInLangFolder();
    static QString getPluginsFolder();

    // Web Stuff
    static QByteArray getUserAgent();
    static QUrl getCrewFetchingUrl(QString crewID);
    static QUrl getPlayerFetchingUrl(QString crewID, QString pageNumber);
    static QUrl getPlayerFetchingUrl(QString crewID, int pageNumber);

    // Screen Stuff
    static qreal screenRatio();
};

#endif // APPENV_H
