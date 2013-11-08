/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_standort.cpp
 * Description: Database-Operation with Standort-Object
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

#include "dbop_standort.h"
#include "statements.h"


DBOp_Standort::DBOp_Standort( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Standort )
{
    ui->setupUi( this );

    sId = Id;
    getFirmenkunden( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( sId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertStandort()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertStandort()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getStandort( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateStandort()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateStandort()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    connect( ui->pushNeuFK, SIGNAL(clicked()), this, SLOT(neuFirmenkunde()) );
}

DBOp_Standort::~DBOp_Standort( )
{
    delete ui;
}

void DBOp_Standort::changeEvent( QEvent *aEvent )
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

void DBOp_Standort::getAutoID()
{
    query = new QSqlQuery( getStandorte );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineStandortID->setText( QString::number(nextId) );
}

void DBOp_Standort::getFirmenkunden( )
{
    query = new QSqlQuery( getSO_Firmenkunden );
    for( int i = ui->comboFirmenkundenID->count(); i>=0; i-- )
    {
        ui->comboFirmenkundenID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboFirmenkundenID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                          query->value(2).toString() + " " + query->value(3).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Firmenkunden nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Standort::getStandort( )
{
    query = new QSqlQuery( chooseStandort + sId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineStandortID->setText( query->value(0).toString() );
        ui->comboFirmenkundenID->setCurrentIndex( ui->comboFirmenkundenID->findText(query->value(1).toString(),Qt::MatchStartsWith) );
        ui->comboStandorttyp->setCurrentIndex( ui->comboStandorttyp->findText(query->value(2).toString()) );
        ui->linePostleitzahl->setText( query->value(3).toString() );
        ui->lineStadt->setText( query->value(4).toString() );
        ui->lineStrasse->setText( query->value(5).toString() );
        ui->linePostfach->setText( query->value(6).toString() );
        ui->lineLand->setText( query->value(7).toString() );
        ui->lineKontonummer->setText( query->value(8).toString() );
        ui->lineBankleitzahl->setText( query->value(9).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Standort nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Standort::neuFirmenkunde( )
{
    DBOp_Firmenkunde *newFirmenkunde = new DBOp_Firmenkunde( "0" );
    newFirmenkunde->exec( );
    getFirmenkunden( );
}

void DBOp_Standort::insertStandort( )
{
    QStringList list = ui->comboFirmenkundenID->currentText().split(" ");
    query = new QSqlQuery( createStandort + ui->lineStandortID->text() + ","
                                          + list[0] + ","
                                          + "\"" + ui->comboStandorttyp->currentText() + "\","
                                          + "\"" + ui->linePostleitzahl->text() + "\","
                                          + "\"" + ui->lineStadt->text() + "\","
                                          + "\"" + ui->lineStrasse->text() + "\","
                                          + "\"" + ui->linePostfach->text() + "\","
                                          + "\"" + ui->lineLand->text() + "\","
                                          + "\"" + ui->lineKontonummer->text() + "\","
                                          + "\"" + ui->lineBankleitzahl->text() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Standort nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Standort::updateStandort( )
{
    QStringList list = ui->comboFirmenkundenID->currentText().split(" ");
    query = new QSqlQuery( changeStandort + atrStandort + "=" + ui->lineStandortID->text() + ","
                                          + atrSO_Firmenkunde + "=" + list[0] + ","
                                          + atrStandorttyp + "=" + "\"" + ui->comboStandorttyp->currentText() + "\","
                                          + atrPLZ + "=" + "\"" + ui->linePostleitzahl->text() + "\","
                                          + atrStadt + "=" + "\"" + ui->lineStadt->text() + "\","
                                          + atrStrasse + "=" + "\"" + ui->lineStrasse->text() + "\","
                                          + atrPostfach + "=" + "\"" + ui->linePostfach->text() + "\","
                                          + atrLand + "=" + "\"" + ui->lineLand->text() + "\","
                                          + atrKonto + "=" + "\"" + ui->lineKontonummer->text() + "\","
                                          + atrBank + "=" + "\"" + ui->lineBankleitzahl->text() + "\""
                                          + " WHERE " + atrStandort + "=" + sId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Standort nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
