/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_personenkunde.cpp
 * Description: Database-Operation with Personenkunden-Object
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

#include "dbop_personenkunde.h"
#include "statements.h"


DBOp_Personenkunde::DBOp_Personenkunde( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Personenkunde )
{
    ui->setupUi( this );

    pkId = Id;
    getStandorte( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( pkId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertPersonenkunde()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertPersonenkunde()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getPersonenkunde( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updatePersonenkunde()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updatePersonenkunde()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    connect( ui->pushNeuS, SIGNAL(clicked()), this, SLOT(neuStandort()) );
}

DBOp_Personenkunde::~DBOp_Personenkunde( )
{
    delete ui;
}

void DBOp_Personenkunde::changeEvent( QEvent *aEvent )
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

void DBOp_Personenkunde::getAutoID()
{
    query = new QSqlQuery( getPersonenkunden );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->linePersonenkundenID->setText( QString::number(nextId) );
}

void DBOp_Personenkunde::getStandorte( )
{
    query = new QSqlQuery( getPK_Standorte );
    for( int i = ui->comboStandortID->count(); i>=0; i-- )
    {
        ui->comboStandortID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboStandortID->addItem( query->value(0).toString() + " " + query->value(11).toString() + " " +
                                      query->value(2).toString() + " " + query->value(3).toString() + " " +
                                      query->value(4).toString() + " " + query->value(5).toString() + " " +
                                      query->value(6).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Standorte nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Personenkunde::getPersonenkunde( )
{
    query = new QSqlQuery( choosePersonenkunde + pkId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->linePersonenkundenID->setText( query->value(0).toString() );
        ui->comboStandortID->setCurrentIndex( ui->comboStandortID->findText(query->value(1).toString(),Qt::MatchStartsWith) );
        ui->comboAnrede->setCurrentIndex( ui->comboAnrede->findText(query->value(2).toString()) );
        ui->lineVorname->setText( query->value(3).toString() );
        ui->lineNachname->setText( query->value(4).toString() );
        ui->linePosition->setText( query->value(5).toString() );
        ui->lineAbteilung->setText( query->value(6).toString() );
        ui->lineGebaeude->setText( query->value(7).toString() );
        ui->lineZimmer->setText( query->value(8).toString() );
        ui->lineTelefon->setText( query->value(9).toString() );
        ui->lineTelefax->setText( query->value(10).toString() );
        ui->lineEmail->setText( query->value(11).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Personenkunden nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Personenkunde::neuStandort( )
{
    DBOp_Standort *newStandort = new DBOp_Standort( "0" );
    newStandort->exec( );
    getStandorte( );
}

void DBOp_Personenkunde::insertPersonenkunde( )
{
    QStringList list = ui->comboStandortID->currentText().split(" ");
    query = new QSqlQuery( createPersonenkunde + ui->linePersonenkundenID->text() + ","
                                               + list[0] + ","
                                               + "\"" + ui->comboAnrede->currentText() + "\","
                                               + "\"" + ui->lineVorname->text() + "\","
                                               + "\"" + ui->lineNachname->text() + "\","
                                               + "\"" + ui->linePosition->text() + "\","
                                               + "\"" + ui->lineAbteilung->text() + "\","
                                               + "\"" + ui->lineGebaeude->text() + "\","
                                               + "\"" + ui->lineZimmer->text() + "\","
                                               + "\"" + ui->lineTelefon->text() + "\","
                                               + "\"" + ui->lineTelefax->text() + "\","
                                               + "\"" + ui->lineEmail->text() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Personenkunden nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Personenkunde::updatePersonenkunde( )
{
    QStringList list = ui->comboStandortID->currentText().split(" ");
    query = new QSqlQuery( changePersonenkunde + atrPersonenkunde + "=" + ui->linePersonenkundenID->text() + ","
                                             + atrPK_Standort + "=" + list[0] + ","
                                             + atrAnrede + "=\"" + ui->comboAnrede->currentText() + "\","
                                             + atrVorname + "=\"" + ui->lineVorname->text() + "\","
                                             + atrNachname + "=\"" + ui->lineNachname->text() + "\","
                                             + atrPosition + "=\"" + ui->linePosition->text() + "\","
                                             + atrAbteilung + "=\"" + ui->lineAbteilung->text() + "\","
                                             + atrGebaeude + "=\"" + ui->lineGebaeude->text() + "\","
                                             + atrZimmer + "=\"" + ui->lineZimmer->text() + "\","
                                             + atrTelefon + "=\"" + ui->lineTelefon->text() + "\","
                                             + atrFax + "=\"" + ui->lineTelefax->text() + "\","
                                             + atrEmail + "=\"" + ui->lineEmail->text() + "\""
                                             + " WHERE " + atrPersonenkunde + "=" + pkId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Personenkunden nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
