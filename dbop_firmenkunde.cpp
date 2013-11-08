/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_firmenkunde.cpp
 * Description: Database-Operation with Firmenkunden-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/05 15:00 sven Exp $
 *
 * @see The GNU Public License (GPL)
 **/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "dbop_firmenkunde.h"
#include "statements.h"


DBOp_Firmenkunde::DBOp_Firmenkunde( QString Id, QWidget *parent ) :
        QDialog( parent ), ui( new Ui::DBOp_Firmenkunde )
{
    ui->setupUi( this );

    fkId = Id;
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( fkId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertFirmenkunde()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertFirmenkunde()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getFirmenkunde( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateFirmenkunde()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateFirmenkunde()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
}

DBOp_Firmenkunde::~DBOp_Firmenkunde( )
{
    delete ui;
}

void DBOp_Firmenkunde::changeEvent(QEvent *aEvent)
{
    QDialog::changeEvent( aEvent );
    switch( aEvent->type() )
    {
        case QEvent::LanguageChange:
            ui->retranslateUi( this );
            break;
        default:
            break;
    }
}

void DBOp_Firmenkunde::getFirmenkunde( )
{
    query = new QSqlQuery( chooseFirmenkunde + fkId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineFirmenkundenID->setText( query->value(0).toString() );
        ui->lineFirmenname->setText( query->value(1).toString() );
        ui->lineHomepage->setText( query->value(2).toString() );
        ui->lineBranche->setText( query->value(3).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Firmenkunden nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Firmenkunde::getAutoID()
{
    query = new QSqlQuery( getFirmenkunden );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineFirmenkundenID->setText( QString::number(nextId) );
}


//Slots
void DBOp_Firmenkunde::insertFirmenkunde( )
{
    query = new QSqlQuery( createFirmenkunde + ui->lineFirmenkundenID->text() + ","
                                             + "\"" + ui->lineFirmenname->text() + "\","
                                             + "\"" + ui->lineHomepage->text() + "\","
                                             + "\"" + ui->lineBranche->text() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Firmenkunden nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Firmenkunde::updateFirmenkunde( )
{
    query = new QSqlQuery( changeFirmenkunde + atrFirmenkunde + "=" + ui->lineFirmenkundenID->text() + ","
                                           + atrFirmenname + "=\"" + ui->lineFirmenname->text() + "\","
                                           + atrHomepage + "=\"" + ui->lineHomepage->text() + "\","
                                           + atrBranche + "=\"" + ui->lineBranche->text() + "\""
                                           + " WHERE " + atrFirmenkunde + "=" + fkId + ";" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Firmenkunden nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
