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

#if QT_VERSION >= 0x050000
#define QtBaseTranslationFormat "qtbase_"
#else
#define QtBaseTranslationFormat "qt_"
#endif

TranslationClass TranslationClass::translationClassInstance;

void TranslationClass::initUserLanguage()
{
    QSettings settings(GTA5SYNC_APPVENDOR, GTA5SYNC_APPSTR);
    settings.beginGroup("Interface");
    userLanguage = settings.value("Language", "System").toString();
    settings.endGroup();
}

void TranslationClass::loadTranslation(QApplication *app)
{
    if (isLangLoaded) unloadTranslation(app);
#ifndef GTA5SYNC_QCONF // Classic modable loading method
    // Start external translate loading
    QString exLangPath = AppEnv::getExLangFolder();
    if (isUserLanguageSystem_p())
    {
        loadSystemTranslation_p(exLangPath, &exAppTranslator);
    }
    else
    {
        loadUserTranslation_p(exLangPath, &exAppTranslator);
    }
    if (currentLanguage.isEmpty() && !isUserLanguageSystem_p())
    {
        loadSystemTranslation_p(exLangPath, &exAppTranslator);
    }
    if (!currentLanguage.isEmpty())
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "installTranslation" << currentLanguage;
#endif
        app->installTranslator(&exAppTranslator);
        loadQtTranslation_p(exLangPath, &exQtTranslator);
        app->installTranslator(&exQtTranslator);
        isLangLoaded = true;
    }
    // End external translate loading
    // Start internal translate loading
    if (currentLanguage.isEmpty())
    {
        QString inLangPath = AppEnv::getInLangFolder();
        if (isUserLanguageSystem_p())
        {
            loadSystemTranslation_p(inLangPath, &inAppTranslator);
        }
        else
        {
            loadUserTranslation_p(inLangPath, &inAppTranslator);
        }
        if (currentLanguage.isEmpty() && !isUserLanguageSystem_p())
        {
            loadSystemTranslation_p(inLangPath, &inAppTranslator);
        }
        if (!currentLanguage.isEmpty())
        {
#ifdef GTA5SYNC_DEBUG
            qDebug() << "installTranslation" << currentLanguage;
#endif
            app->installTranslator(&inAppTranslator);
            loadQtTranslation_p(inLangPath, &inQtTranslator);
            app->installTranslator(&inQtTranslator);
            isLangLoaded = true;
        }
    }
    // End internal translate loading
#else // New qconf loading method
    QString inLangPath = AppEnv::getInLangFolder();
    QString exLangPath = AppEnv::getExLangFolder();
    if (isUserLanguageSystem_p())
    {
        loadSystemTranslation_p(inLangPath, &inAppTranslator);
    }
    else
    {
        loadUserTranslation_p(inLangPath, &inAppTranslator);
    }
    if (currentLanguage.isEmpty() && !isUserLanguageSystem_p())
    {
        loadSystemTranslation_p(inLangPath, &inAppTranslator);
    }
    if (!currentLanguage.isEmpty())
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "installTranslation" << currentLanguage;
#endif
        app->installTranslator(&inAppTranslator);
        loadQtTranslation_p(exLangPath, &exQtTranslator);
        app->installTranslator(&exQtTranslator);
        isLangLoaded = true;
    }
#endif
}

QStringList TranslationClass::listTranslations(const QString &langPath)
{
    QDir langDir;
    langDir.setNameFilters(QStringList("gta5sync_*.qm"));
    langDir.setPath(langPath);
    QStringList availableLanguages;
    foreach(const QString &lang, langDir.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::NoSort))
    {
        availableLanguages << QString(lang).remove("gta5sync_").remove(".qm");
    }
    return availableLanguages;
}

bool TranslationClass::loadSystemTranslation_p(const QString &langPath, QTranslator *appTranslator)
{
#ifdef GTA5SYNC_DEBUG
    qDebug() << "loadSystemTranslation_p";
#endif
    foreach(const QString &languageName, QLocale::system().uiLanguages())
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguage" << languageName;
#endif
        QStringList langList = QString(languageName).replace("-","_").split("_");
        if (langList.length() == 2)
        {
#ifdef GTA5SYNC_DEBUG
            qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % "_" % langList.at(1) % ".qm");
#endif
            if (appTranslator->load(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % "_" % langList.at(1) % ".qm"))
            {
#ifdef GTA5SYNC_DEBUG
                qDebug() << "loadLanguageFileSuccess" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % "_" % langList.at(1) % ".qm");
#endif
                currentLanguage = languageName;
                return true;
            }
#ifdef GTA5SYNC_DEBUG
            qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
#endif
            if (appTranslator->load(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
#ifdef GTA5SYNC_DEBUG
                qDebug() << "loadLanguageFileSuccess" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
#endif
                currentLanguage = languageName;
                return true;
            }
        }
        else if (langList.length() == 1)
        {
#ifdef GTA5SYNC_DEBUG
            qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
#endif
            if (appTranslator->load(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
            {
#ifdef GTA5SYNC_DEBUG
                qDebug() << "loadLanguageFileSuccess" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
#endif
                currentLanguage = languageName;
                return true;
            }
        }
    }
    return false;
}

bool TranslationClass::loadUserTranslation_p(const QString &langPath, QTranslator *appTranslator)
{
#ifdef GTA5SYNC_DEBUG
    qDebug() << "loadUserTranslation_p";
#endif
    QString languageName = userLanguage;
    QStringList langList = QString(languageName).replace("-","_").split("_");
    if (langList.length() == 2)
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % "_" % langList.at(1) % ".qm");
#endif
        if (appTranslator->load(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % "_" % langList.at(1) % ".qm"))
        {
            currentLanguage = languageName;
            return true;
        }
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
#endif
        if (appTranslator->load(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
        {
            currentLanguage = languageName;
            return true;
        }
    }
    else if (langList.length() == 1)
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm");
#endif
        if (appTranslator->load(langPath % QDir::separator() % "gta5sync_" % langList.at(0) % ".qm"))
        {
            currentLanguage = languageName;
            return true;
        }
    }
    return false;
}

bool TranslationClass::loadQtTranslation_p(const QString &langPath, QTranslator *qtTranslator)
{
#ifdef GTA5SYNC_DEBUG
    qDebug() << "loadQtTranslation_p" << currentLanguage;
#endif
    QString languageName = currentLanguage;
    QStringList langList = QString(languageName).replace("-","_").split("_");
    if (langList.length() == 2)
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % QtBaseTranslationFormat % langList.at(0) % "_" % langList.at(1) % ".qm");
#endif
        if (qtTranslator->load(langPath % QDir::separator() % QtBaseTranslationFormat % langList.at(0) % "_" % langList.at(1) % ".qm"))
        {
            return true;
        }
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % QtBaseTranslationFormat % langList.at(0) % ".qm");
#endif
        if (qtTranslator->load(langPath % QDir::separator() % QtBaseTranslationFormat % langList.at(0) % ".qm"))
        {
            return true;
        }
    }
    else if (langList.length() == 1)
    {
#ifdef GTA5SYNC_DEBUG
        qDebug() << "loadLanguageFile" << QString(langPath % QDir::separator() % QtBaseTranslationFormat % langList.at(0) % ".qm");
#endif
        if (qtTranslator->load(langPath % QDir::separator() % QtBaseTranslationFormat % langList.at(0) % ".qm"))
        {
            return true;
        }
    }
    return false;
}

bool TranslationClass::isUserLanguageSystem_p()
{
    return (userLanguage == "System" || userLanguage.trimmed().isEmpty());
}

void TranslationClass::unloadTranslation(QApplication *app)
{
#ifndef GTA5SYNC_QCONF
    app->removeTranslator(&exAppTranslator);
    app->removeTranslator(&exQtTranslator);
    app->removeTranslator(&inAppTranslator);
    app->removeTranslator(&inQtTranslator);
#else
    app->removeTranslator(&inAppTranslator);
    app->removeTranslator(&exQtTranslator);
#endif
    currentLanguage = "";
    isLangLoaded = false;
#ifdef _MSC_VER // Fix dumb Microsoft compiler warning
    Q_UNUSED(app)
#endif
}
