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

#include "JsonEditorDialog.h"
#include "ui_JsonEditorDialog.h"
#include "SnapmaticEditor.h"
#include "AppEnv.h"
#include <QStringBuilder>
#include <QJsonDocument>
#include <QMessageBox>

JsonEditorDialog::JsonEditorDialog(SnapmaticPicture *picture, QWidget *parent) :
    QDialog(parent), smpic(picture),
    ui(new Ui::JsonEditorDialog)
{
    // Set Window Flags
    setWindowFlags(windowFlags()^Qt::WindowContextHelpButtonHint);

    ui->setupUi(this);
    if (QIcon::hasThemeIcon("dialog-close"))
    {
        ui->cmdClose->setIcon(QIcon::fromTheme("dialog-close"));
    }
    jsonCode = picture->getJsonStr();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonCode.toUtf8());
    ui->txtJSON->setPlainText(QString::fromUtf8(jsonDocument.toJson(QJsonDocument::Indented)));

    // DPI calculation
    qreal screenRatio = AppEnv::screenRatio();
    resize(400 * screenRatio, 350 * screenRatio);
}

JsonEditorDialog::~JsonEditorDialog()
{
    delete ui;
}

void JsonEditorDialog::on_cmdClose_clicked()
{
    QJsonDocument jsonNew = QJsonDocument::fromJson(ui->txtJSON->toPlainText().toUtf8());
    if (!jsonNew.isEmpty())
    {
        QJsonDocument jsonOriginal = QJsonDocument::fromJson(jsonCode.toUtf8());
        QString originalCode = QString::fromUtf8(jsonOriginal.toJson(QJsonDocument::Compact));
        QString newCode = QString::fromUtf8(jsonNew.toJson(QJsonDocument::Compact));
        if (newCode != originalCode)
        {
            // ask for save
        }
    }
    this->close();
}

void JsonEditorDialog::on_cmdSave_clicked()
{
    QJsonDocument jsonNew = QJsonDocument::fromJson(ui->txtJSON->toPlainText().toUtf8());
    if (!jsonNew.isEmpty())
    {
        QJsonDocument jsonOriginal = QJsonDocument::fromJson(jsonCode.toUtf8());
        QString originalCode = QString::fromUtf8(jsonOriginal.toJson(QJsonDocument::Compact));
        QString newCode = QString::fromUtf8(jsonNew.toJson(QJsonDocument::Compact));
        if (newCode != originalCode)
        {
            QString currentFilePath = smpic->getPictureFilePath();
            QString originalFilePath = smpic->getOriginalPictureFilePath();
            QString backupFileName = originalFilePath % ".bak";
            if (!QFile::exists(backupFileName))
            {
                QFile::copy(currentFilePath, backupFileName);
            }
            smpic->setJsonStr(newCode, true);
            if (!smpic->isJsonOk())
            {
                QMessageBox::warning(this, tr("Snapmatic JSON Editor"), tr("Patching of Snapmatic Properties failed because of JSON Error"));
                smpic->setJsonStr(originalCode, true);
                return;
            }
            if (!smpic->exportPicture(currentFilePath))
            {
                QMessageBox::warning(this, tr("Snapmatic JSON Editor"), SnapmaticEditor::tr("Patching of Snapmatic Properties failed because of I/O Error"));
                smpic->setJsonStr(originalCode, true);
                return;
            }
            smpic->emitUpdate();
        }
        this->close();
    }
    else
    {
        // throw an error
    }
}
