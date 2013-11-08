/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_lieferung.h
 * Description: Database-Operation with Lieferung-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/22 13:00 sven Exp $
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

#include "dbop_lieferung.h"
#include "statements.h"


DBOp_Lieferung::DBOp_Lieferung( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Lieferung )
{
    ui->setupUi( this );

    lId = Id;
    getBestellungen( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( lId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertLieferung()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertLieferung()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getLieferung( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateLieferung()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateLieferung()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    connect( ui->pushNeuB, SIGNAL(clicked()), this, SLOT(neuBestellung()) );
}

DBOp_Lieferung::~DBOp_Lieferung( )
{
    delete ui;
}

void DBOp_Lieferung::changeEvent( QEvent *aEvent )
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

void DBOp_Lieferung::getAutoID()
{
    query = new QSqlQuery( getLieferungen );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineLieferungsID->setText( QString::number(nextId) );
}

void DBOp_Lieferung::getBestellungen( )
{
    query = new QSqlQuery( getL_Bestellungen );
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

void DBOp_Lieferung::getLieferung( )
{
    query = new QSqlQuery( chooseLieferung + lId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineLieferungsID->setText( query->value(0).toString() );
        ui->lineLieferdatum->setText( query->value(1).toString() );
        ui->comboBestellungsID->setCurrentIndex( ui->comboBestellungsID->findText(query->value(2).toString(), Qt::MatchStartsWith) );
        ui->lineTrackingNr->setText( query->value(3).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Lieferung nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Lieferung::neuBestellung( )
{
    DBOp_Bestellung *newBestellung = new DBOp_Bestellung( "0" );
    newBestellung->exec( );
    getBestellungen( );
}

void DBOp_Lieferung::insertLieferung( )
{
    QStringList list = ui->comboBestellungsID->currentText().split(" ");
    query = new QSqlQuery( createLieferung + ui->lineLieferungsID->text() + ","
                                           + "\"" + ui->lineLieferdatum->text() + "\","
                                           + list[0] + ","
                                           + "\"" + ui->lineTrackingNr->text() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Lieferung nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Lieferung::updateLieferung( )
{
    QStringList list = ui->comboBestellungsID->currentText().split(" ");
    query = new QSqlQuery( changeLieferung + atrLieferung + "=" + ui->lineLieferungsID->text() + ","
                                           + atrLieferdatum + "=" + "\"" + ui->lineLieferdatum->text() + "\","
                                           + atrL_Bestellung + "=" + list[0] + ","
                                           + atrTrackingNr + "=" + "\"" + ui->lineTrackingNr->text() + "\""
                                           + " WHERE " + atrLieferung + "=" + lId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Lieferung nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
