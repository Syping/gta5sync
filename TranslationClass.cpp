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

#include "TranslationClass.h"
#include "AppEnv.h"
#include "config.h"
#include <QStringBuilder>
#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QLocale>
#include <QDebug>
#include <QFile>
#include <QDir>

TranslationClass::TranslationClass(QObject *parent) : QObject(parent)
{
    QSettings settings(GTA5SYNC_APPVENDOR, GTA5SYNC_APPSTR);
    settings.beginGroup("Interface");
    systemLanguage = settings.value("Language","System").toString();
    settings.endGroup();
}

void TranslationClass::loadTranslation(QApplication *app)
{
#ifndef GTA5SYNC_QCONF // Classic modable loading method
    // Start external translate loading
    QString exLangPath = AppEnv::getExLangFolder();
    bool trLoadFail = false;
    bool trLoaded = false;
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                exAppTranslator.load(exLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
                QLocale::setDefault(QLocale::system());
            }
        }
    }
    else
    {
        QString languageName = systemLanguage;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                if (!exAppTranslator.load(exLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
                {
                    if (langList.at(0) != "en")
                    {
                        trLoadFail = true;
                    }
                }
                else
                {
                    QLocale::setDefault(QLocale(langList.at(0)));
                    trLoaded = true;
                }
            }
            else
            {
                if (langList.at(0) != "en")
                {
                    trLoadFail = true;
                }
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                exAppTranslator.load(exLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
                QLocale::setDefault(QLocale(langList.at(0)));
            }
        }
    }
    app->installTranslator(&exAppTranslator);
#if QT_VERSION >= 0x050000
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    else
    {
        QString languageName = systemLanguage;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    app->installTranslator(&exQtTranslator);
#else
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    else
    {
        QString languageName = language;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    app->installTranslator(&exQtTranslator);
#endif
    // End external translate loading
    // Start internal translate loading
    trLoadFail = false;
    QString inLangPath = AppEnv::getInLangFolder();
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                if (!inAppTranslator.load(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
                {
                    if (langList.at(0) != "en")
                    {
                        if (trLoaded) { trLoadFail = true; }
                    }
                }
                else
                {
                    QLocale::setDefault(QLocale(langList.at(0)));
                }
            }
            else
            {
                if (langList.at(0) != "en")
                {
                    if (trLoaded) { trLoadFail = true; }
                }
            }
        }
    }
    else if (systemLanguage == "en" || systemLanguage == "English")
    {
        QLocale::setDefault(QLocale(QLocale::English, QLocale::AnyCountry));
    }
    else
    {
        QString languageName = systemLanguage;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                inAppTranslator.load(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
                QLocale::setDefault(QLocale(langList.at(0)));

            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                inAppTranslator.load(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
                QLocale::setDefault(QLocale(langList.at(0)));
            }
        }
    }
    app->installTranslator(&inAppTranslator);
#if QT_VERSION >= 0x050000
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                inQtTranslator.load(inLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    else
    {
        QString languageName = systemLanguage;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                inQtTranslator.load(inLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                inQtTranslator.load(inLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    app->installTranslator(&inQtTranslator);
#else
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                inQtTranslator.load(inLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    else
    {
        QString languageName = language;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                inQtTranslator.load(inLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                inQtTranslator.load(inLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    app->installTranslator(&inQtTranslator);
#endif
    // End internal translate loading
#else // New qconf loading method
    QString inLangPath = AppEnv::getInLangFolder();
    QString exLangPath = AppEnv::getExLangFolder();
    bool trLoadFail = false;
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                exAppTranslator.load(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
                QLocale::setDefault(QLocale::system());
            }
        }
    }
    else
    {
        QString languageName = systemLanguage;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                if (!exAppTranslator.load(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
                {
                    if (langList.at(0) != "en")
                    {
                        trLoadFail = true;
                    }
                }
                else
                {
                    QLocale::setDefault(QLocale(langList.at(0)));
                }
            }
            else
            {
                if (langList.at(0) != "en")
                {
                    trLoadFail = true;
                }
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
                exAppTranslator.load(inLangPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
                QLocale::setDefault(QLocale(langList.at(0)));
            }
        }
    }
    app->installTranslator(&exAppTranslator);
#if QT_VERSION >= 0x050000
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    else
    {
        QString languageName = language;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qtbase_" % langList.at(0) % ".qm");
            }
        }
    }
    app->installTranslator(&exQtTranslator);
#else
    if (systemLanguage == "System" || systemLanguage.trimmed().isEmpty())
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    else
    {
        QString languageName = systemLanguage;
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    if (trLoadFail)
    {
        QString languageName = QLocale::system().name();
        QStringList langList = languageName.split("_");
        if (langList.length() >= 1)
        {
            if (QFile::exists(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm"))
            {
                exQtTranslator.load(exLangPath % QDir::separator() % "qt_" % langList.at(0) % ".qm");
            }
        }
    }
    app->installTranslator(&exQtTranslator);
#endif
#endif
#ifdef _MSC_VER // Fix dumb Microsoft compiler warning
    Q_UNUSED(app)
#endif
}

void TranslationClass::unloadTranslation(QApplication *app)
{
#ifdef GTA5SYNC_QCONF
    app->removeTranslator(&exAppTranslator);
    app->removeTranslator(&exQtTranslator);
#endif
    app->removeTranslator(&inAppTranslator);
    app->removeTranslator(&inQtTranslator);
#ifdef _MSC_VER // Fix dumb Microsoft compiler warning
    Q_UNUSED(app)
#endif
}
