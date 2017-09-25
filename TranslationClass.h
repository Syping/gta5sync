/*****************************************************************************
* gta5sync GRAND THEFT AUTO V SYNC
* Copyright (C) 2017 Syping
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

#ifndef TRANSLATIONCLASS_H
#define TRANSLATIONCLASS_H

#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QObject>

class TranslationClass : public QObject
{
    Q_OBJECT
public:
    explicit TranslationClass(QObject *parent = 0);
    void loadTranslation(QApplication *app);
    void unloadTranslation(QApplication *app);

private:
    QTranslator exAppTranslator;
    QTranslator exQtTranslator;
    QTranslator inAppTranslator;
    QTranslator inQtTranslator;
    QString systemLanguage;

signals:

public slots:
};

#endif // TRANSLATIONCLASS_H
