/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_rechnung.h
 * Description: Database-Operation with Rechnung-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/22 13:30 sven Exp $
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

#include "dbop_rechnung.h"
#include "statements.h"


DBOp_Rechnung::DBOp_Rechnung( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Rechnung )
{
    ui->setupUi( this );

    rId = Id;
    getBestellungen( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( rId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertRechnung()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertRechnung()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getRechnung( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateRechnung()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateRechnung()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    connect( ui->pushNeuB, SIGNAL(clicked()), this, SLOT(neuBestellung()) );
}

DBOp_Rechnung::~DBOp_Rechnung( )
{
    delete ui;
}

void DBOp_Rechnung::changeEvent( QEvent *aEvent )
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

void DBOp_Rechnung::getAutoID()
{
    query = new QSqlQuery( getRechnungen );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineRechnungsID->setText( QString::number(nextId) );
}

void DBOp_Rechnung::getBestellungen( )
{
    query = new QSqlQuery( getR_Bestellungen );
    for( int i = ui->comboBestellungsID->count(); i>=0; i-- )
    {
        ui->comboBestellungsID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboBestellungsID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                         query->value(2).toString() + " " + query->value(3).toString() + " " +
                                         query->value(4).toString() + " " + query->value(5).toString() + " " +
                                         query->value(6).toString() + " " + query->value(7).toString() + " " +
                                         query->value(8).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Bestellungen nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Rechnung::getRechnung( )
{
    query = new QSqlQuery( chooseRechnung + rId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineRechnungsID->setText( query->value(0).toString() );
        ui->lineRechnungsdatum->setText( query->value(1).toString() );
        ui->lineFaelligkeit->setText( query->value(2).toString() );
        ui->doubleMwSt->setValue( query->value(3).toDouble() );
        ui->comboBestellungsID->setCurrentIndex( ui->comboBestellungsID->findText(query->value(4).toString(), Qt::MatchStartsWith) );
        ui->comboZahlungsart->setCurrentIndex( ui->comboZahlungsart->findText(query->value(5).toString()) );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Rechnung nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Rechnung::neuBestellung( )
{
    DBOp_Bestellung *newBestellung = new DBOp_Bestellung( "0" );
    newBestellung->exec( );
    getBestellungen( );
}

void DBOp_Rechnung::insertRechnung( )
{
    QStringList list = ui->comboBestellungsID->currentText().split(" ");
    query = new QSqlQuery( createRechnung + ui->lineRechnungsID->text() + ","
                                          + "\"" + ui->lineRechnungsdatum->text() + "\","
                                          + "\"" + ui->lineFaelligkeit->text() + "\","
                                          + "\"" + ui->doubleMwSt->text() + "\","
                                          + list[0] + ","
                                          + "\"" + ui->comboZahlungsart->currentText() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Rechnung nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Rechnung::updateRechnung( )
{
    QStringList list = ui->comboBestellungsID->currentText().split(" ");
    query = new QSqlQuery( changeRechnung + atrRechnung + "=" + ui->lineRechnungsID->text() + ","
                                          + atrRechnungsdatum + "=" + "\"" + ui->lineRechnungsdatum->text() + "\","
                                          + atrFaelligkeit + "=" + "\"" + ui->lineFaelligkeit->text() + "\","
                                          + atrMwSt + "=" + "\"" + ui->doubleMwSt->text() + "\","
                                          + atrR_Bestellung + "=" + list[0] + ","
                                          + atrZahlungsArt + "=" + "\"" + ui->comboZahlungsart->currentText() + "\""
                                          + " WHERE " + atrRechnung + "=" + rId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Rechnung nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
