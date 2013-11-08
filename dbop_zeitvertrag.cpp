/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_zeitvertrag.cpp
 * Description: Database-Operation with Zeitvertrags-Object
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

#include "dbop_zeitvertrag.h"
#include "statements.h"


DBOp_Zeitvertrag::DBOp_Zeitvertrag( QString Id, QString Typ, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Zeitvertrag )
{
    ui->setupUi( this );

    zvId = Id;
    zvTyp = Typ;
    getLizenzen( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( zvId == "0" )
    {
        getAutoID();
        ui->comboVertragsart->setCurrentIndex( ui->comboVertragsart->findText(Typ) );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertZeitvertrag()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertZeitvertrag()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getZeitvertrag( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateZeitvertrag()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateZeitvertrag()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    connect( ui->pushNeuL, SIGNAL(clicked()), this, SLOT(neuLizenz()) );
}

DBOp_Zeitvertrag::~DBOp_Zeitvertrag( )
{
    delete ui;
}

void DBOp_Zeitvertrag::changeEvent( QEvent *aEvent )
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

void DBOp_Zeitvertrag::getAutoID()
{
    query = new QSqlQuery( getZeitvertraege );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineZeitvertragsID->setText( QString::number(nextId) );
}

void DBOp_Zeitvertrag::getLizenzen( )
{
    query = new QSqlQuery( getZV_Lizenzen );
    for( int i = ui->comboLizenzID->count(); i>=0; i-- )
    {
        ui->comboLizenzID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboLizenzID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                    query->value(2).toString() + " " + query->value(3).toString() + " " +
                                    query->value(4).toString() + " " + query->value(5).toString() + " " +
                                    query->value(6).toString() + " " + query->value(7).toString() + " " +
                                    query->value(8).toString() + " " + query->value(9).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Lizenzen nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Zeitvertrag::getZeitvertrag( )
{
    query = new QSqlQuery( chooseZeitvertrag + zvId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineZeitvertragsID->setText( query->value(0).toString() );
        ui->comboLizenzID->setCurrentIndex( ui->comboLizenzID->findText(query->value(1).toString(),Qt::MatchStartsWith) );
        ui->comboVertragsart->setCurrentIndex( ui->comboVertragsart->findText(query->value(2).toString()) );
        ui->lineVertragsbeginn->setText( query->value(3).toString() );
        ui->lineVertragsende->setText( query->value(4).toString() );
        ui->doubleMonatsbeitrag->setValue( query->value(5).toDouble() );
        ui->comboZahlungsart->setCurrentIndex( ui->comboZahlungsart->findText(query->value(6).toString()) );
        ui->lineBezahltbis->setText( query->value(7).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Zeitvertrag nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Zeitvertrag::neuLizenz( )
{
    DBOp_Lizenz *newLizenz = new DBOp_Lizenz( "0" );
    newLizenz->exec();
}

void DBOp_Zeitvertrag::insertZeitvertrag( )
{
    QStringList list = ui->comboLizenzID->currentText().split(" ");
    query = new QSqlQuery( createZeitvertrag + ui->lineZeitvertragsID->text() + ","
                                             + list[0] + ","
                                             + "\"" + ui->comboVertragsart->currentText() + "\","
                                             + "\"" + ui->lineVertragsbeginn->text() + "\","
                                             + "\"" + ui->lineVertragsende->text() + "\","
                                             + "\"" + ui->doubleMonatsbeitrag->text() + "\","
                                             + "\"" + ui->comboZahlungsart->currentText() + "\","
                                             + "\"" + ui->lineBezahltbis->text() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Zeitvertrag nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Zeitvertrag::updateZeitvertrag( )
{
    QStringList list = ui->comboLizenzID->currentText().split(" ");
    query = new QSqlQuery( changeZeitvertrag + atrZeitvertrag + "=" + ui->lineZeitvertragsID->text() + ","
                                             + atrZV_Lizenz + "=" + list[0] + ","
                                             + atrVertragstyp + "=" + "\"" + ui->comboVertragsart->currentText() + "\","
                                             + atrVertragsbeginn + "=" + "\"" + ui->lineVertragsbeginn->text() + "\","
                                             + atrVertragsende + "=" + "\"" + ui->lineVertragsende->text() + "\","
                                             + atrMonatsbetrag + "=" + "\"" + ui->doubleMonatsbeitrag->text() + "\","
                                             + atrZahlungsart + "=" + "\"" + ui->comboZahlungsart->currentText() + "\","
                                             + atrBezahltBis + "=" + "\"" + ui->lineBezahltbis->text() + "\""
                                             + " WHERE " + atrZeitvertrag + "=" + zvId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Zetivertrag nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
