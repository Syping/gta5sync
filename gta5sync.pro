#/*****************************************************************************
#* gta5sync GRAND THEFT AUTO V SYNC
#* Copyright (C) 2015-2017 Syping
#*
#* This program is free software: you can redistribute it and/or modify
#* it under the terms of the GNU General Public License as published by
#* the Free Software Foundation, either version 3 of the License, or
#* (at your option) any later version.
#*
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#*
#* You should have received a copy of the GNU General Public License
#* along with this program.  If not, see <http://www.gnu.org/licenses/>.
#*****************************************************************************/

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): greaterThan(QT_MINOR_VERSION, 1): win32: QT += winextras

DEPLOYMENT.display_name = gta5sync
TARGET = gta5sync
TEMPLATE = app

SOURCES += main.cpp \
    AboutDialog.cpp \
    AppEnv.cpp \
    CrewDatabase.cpp \
    DatabaseThread.cpp \
    ExportDialog.cpp \
    ExportThread.cpp \
    GlobalString.cpp \
    IconLoader.cpp \
    ImportDialog.cpp \
    MapPreviewDialog.cpp \
    OptionsDialog.cpp \
    PictureDialog.cpp \
    PictureExport.cpp \
    PictureWidget.cpp \
    ProfileDatabase.cpp \
    ProfileInterface.cpp \
    ProfileLoader.cpp \
    ProfileWidget.cpp \
    SavegameCopy.cpp \
    SavegameData.cpp \
    SavegameDialog.cpp \
    SavegameWidget.cpp \
    SidebarGenerator.cpp \
    SnapmaticEditor.cpp \
    SnapmaticPicture.cpp \
    SnapmaticWidget.cpp \
    StandardPaths.cpp \
    StringParser.cpp \
    TranslationClass.cpp \
    UserInterface.cpp \
    uimod/UiModLabel.cpp \
    uimod/UiModWidget.cpp

HEADERS  += \
    AboutDialog.h \
    AppEnv.h \
    CrewDatabase.h \
    DatabaseThread.h \
    ExportDialog.h \
    ExportThread.h \
    GlobalString.h \
    IconLoader.h \
    ImportDialog.h \
    MapPreviewDialog.h \
    OptionsDialog.h \
    PictureDialog.h \
    PictureExport.h \
    PictureWidget.h \
    ProfileDatabase.h \
    ProfileInterface.h \
    ProfileLoader.h \
    ProfileWidget.h \
    SavegameCopy.h \
    SavegameData.h \
    SavegameDialog.h \
    SavegameWidget.h \
    SidebarGenerator.h \
    SnapmaticEditor.h \
    SnapmaticPicture.h \
    SnapmaticWidget.h \
    StandardPaths.h \
    StringParser.h \
    TranslationClass.h \
    UserInterface.h \
    uimod/UiModLabel.h \
    uimod/UiModWidget.h

PRECOMPILED_HEADER += config.h

FORMS    += \
    AboutDialog.ui \
    ExportDialog.ui \
    ImportDialog.ui \
    MapPreviewDialog.ui \
    OptionsDialog.ui \
    PictureDialog.ui \
    ProfileInterface.ui \
    SavegameDialog.ui \
    SavegameWidget.ui \
    SnapmaticEditor.ui \
    SnapmaticWidget.ui \
    UserInterface.ui

TRANSLATIONS += \
    res/gta5sync_de.ts \
    res/gta5sync_fr.ts \
    res/gta5sync_ru.ts \
    lang/gta5sync_no.ts

RESOURCES += \
    res/tr_g5p.qrc \
    res/app.qrc

DISTFILES += res/app.rc \
    res/gta5sync.desktop \
    res/gta5sync_de.ts \
    res/gta5sync_fr.ts \
    res/gta5sync_ru.ts \
    res/gta5sync.exe.manifest \
    res/gta5sync.png \
    lang/gta5sync_no.ts \
    lang/README.txt

INCLUDEPATH += ./uimod

# WINDOWS ONLY

win32: DEFINES += GTA5SYNC_WIN
win32: RC_FILE += res/app.rc
win32: LIBS += -luser32
win32: CONFIG -= embed_manifest_exe

# MAC OS X ONLY
macx: ICON = res/5sync.icns

# QT4 ONLY STUFF

isEqual(QT_MAJOR_VERSION, 4): INCLUDEPATH += ./qjson4
isEqual(QT_MAJOR_VERSION, 4): HEADERS += qjson4/QJsonArray.h \
    qjson4/QJsonDocument.h \
    qjson4/QJsonObject.h \
    qjson4/QJsonParseError.h \
    qjson4/QJsonValue.h \
    qjson4/QJsonValueRef.h \
    qjson4/QJsonParser.h \
    qjson4/QJsonRoot.h

isEqual(QT_MAJOR_VERSION, 4): SOURCES += qjson4/QJsonArray.cpp \
    qjson4/QJsonDocument.cpp \
    qjson4/QJsonObject.cpp \
    qjson4/QJsonParseError.cpp \
    qjson4/QJsonValue.cpp \
    qjson4/QJsonValueRef.cpp \
    qjson4/QJsonParser.cpp

isEqual(QT_MAJOR_VERSION, 4): RESOURCES += res/tr_qt4.qrc

# QT5 ONLY STUFF

isEqual(QT_MAJOR_VERSION, 5): RESOURCES += res/tr_qt5.qrc

# UNIX SYSTEM STUFF

unix: !macx: appfiles.path = $$(INSTALL_PATH)/share/applications
unix: !macx: appfiles.files = $$PWD/res/gta5sync.desktop
unix: !macx: pixmaps.path = $$(INSTALL_PATH)/share/pixmaps
unix: !macx: pixmaps.files = $$PWD/res/gta5sync.png
unix: !macx: target.path = $$(INSTALL_PATH)/bin
unix: !macx: INSTALLS += target pixmaps appfiles

# QCONF BASED BUILD STUFF

contains(DEFINES, GTA5SYNC_QCONF){
    RESOURCES -= res/tr_g5p.qrc
    isEqual(QT_MAJOR_VERSION, 4): RESOURCES -= res/tr_qt4.qrc
    isEqual(QT_MAJOR_VERSION, 5): RESOURCES -= res/tr_qt5.qrc
    unix: !macx: langfiles.path = $$(INSTALL_PATH)/share/gta5sync/translations
    unix: !macx: langfiles.files = $$PWD/res/gta5sync_de.qm $$PWD/res/gta5sync_fr.qm $$PWD/res/gta5sync_ru.qm
    unix: !macx: INSTALLS += langfiles
}
