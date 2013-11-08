/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_angebot.cpp
 * Description: Database-Operation with Angebot-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/18 13:00 sven Exp $
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

#include "dbop_angebot.h"
#include "statements.h"


DBOp_Angebot::DBOp_Angebot( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Angebot )
{
    ui->setupUi( this );

    aId = Id;
    getStandorte( );
    getProdukte( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( aId == "0" )
    {
        getAutoID( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertAngebot()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertAngebot()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getAngebot( );
        getPositionen( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateAngebot()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateAngebot()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    getPositionID( );
    setRabatt( );
    setTagespreis( );
    connect( ui->pushNeuS, SIGNAL(clicked()), this, SLOT(neuStandort()) );
    connect( ui->pushNeuP, SIGNAL(clicked()), this, SLOT(neuProdukt()) );
    connect( ui->doubleFirmenRabatt, SIGNAL(valueChanged(double)), this, SLOT(setRabatt()) );
    connect( ui->pushPositionHinzufuegen, SIGNAL(clicked()), this, SLOT(insertPosition()) );
    connect( ui->pushPositionEntfernen, SIGNAL(clicked()), this, SLOT(removePosition()) );
    connect( ui->comboProduktID, SIGNAL(currentIndexChanged(int)), this, SLOT(setTagespreis()) );
}

DBOp_Angebot::~DBOp_Angebot( )
{
    delete ui;
}

void DBOp_Angebot::changeEvent( QEvent *aEvent )
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

void DBOp_Angebot::getAutoID()
{
    query = new QSqlQuery( getAngebote );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineAngebotsID->setText( QString::number(nextId) );
}

void DBOp_Angebot::getPositionID()
{
    query = new QSqlQuery( getA_Positionen + aId + aPosOrder );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineAngebotspositionsID->setText( QString::number(nextId) );
}

void DBOp_Angebot::getStandorte( )
{
    query = new QSqlQuery( getA_Standorte );
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

void DBOp_Angebot::getProdukte( )
{
    query = new QSqlQuery( getA_Produkte );
    for( int i = ui->comboProduktID->count(); i>=0; i-- )
    {
        ui->comboProduktID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboProduktID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                     query->value(2).toString() + " " + query->value(3).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Produkte nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Angebot::getAngebot( )
{
    query = new QSqlQuery( chooseAngebot + aId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineAngebotsID->setText( query->value(0).toString() );
        ui->comboStandortID->setCurrentIndex( ui->comboStandortID->findText(query->value(1).toString(),Qt::MatchStartsWith) );
        ui->lineAngebotsdatum->setText(query->value(2).toString() );
        ui->lineGueltigkeit->setText( query->value(3).toString() );
        ui->doubleFirmenRabatt->setValue( query->value(4).toDouble() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Angebot nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Angebot::getPositionen( )
{
    query = new QSqlQuery( getA_Positionen + aId + " ORDER BY " + atrAPosition + ";" );
    ui->tableAngebotspositionen->setColumnCount( query->record().count() );
    ui->tableAngebotspositionen->setRowCount( query->size() );
    for( int i=0; i<query->record().count(); i++ )
    {
        ui->tableAngebotspositionen->setHorizontalHeaderItem( i, new QTableWidgetItem(QString(query->record().fieldName(i)), QTableWidgetItem::Type) );
    }
    int row = 0;
    while( query->next() )
    {
        for( int i=0; i<query->record().count(); i++ )
        {
            item = new QTableWidgetItem( query->value(i).toString(), 0 );
            ui->tableAngebotspositionen->setItem( row, i, item );
        }
        row++;
    }
}


//Slots
void DBOp_Angebot::setRabatt( )
{
    ui->doubleRabatt->setValue( ui->doubleFirmenRabatt->value() );
}

void DBOp_Angebot::setTagespreis( )
{
    QStringList list = ui->comboProduktID->currentText().split(" ");
    QString value = list.last();
    ui->doubleTagespreis->setValue( value.toDouble() );
}

void DBOp_Angebot::neuStandort( )
{
    DBOp_Standort *newStandort = new DBOp_Standort( "0" );
    newStandort->exec( );
    getStandorte( );
}

void DBOp_Angebot::neuProdukt( )
{
    DBOp_Produkt *newProdukt = new DBOp_Produkt( "0" );
    newProdukt->exec( );
    getProdukte( );
}

void DBOp_Angebot::insertAngebot( )
{
    if( aId == "0" )
    {
        aId = ui->lineAngebotsID->text();
        QStringList list = ui->comboStandortID->currentText().split(" ");
        query = new QSqlQuery( createAngebot + ui->lineAngebotsID->text() + ","
                                             + list[0] + ","
                                             + "\"" + ui->lineAngebotsdatum->text() + "\","
                                             + "\"" + ui->lineGueltigkeit->text() + "\","
                                             + "\"" + ui->doubleFirmenRabatt->text() + "\") ;" );
        if( query->lastError().isValid() )
        {
            QMessageBox::critical( 0, "Kann Angebot nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
        }
    }
    else
    {
        updateAngebot( );
    }
}

void DBOp_Angebot::updateAngebot( )
{
    QStringList list = ui->comboStandortID->currentText().split(" ");
    query = new QSqlQuery( changeAngebot + atrAngebot + "=" + ui->lineAngebotsID->text() + ","
                                         + atrA_Standort + "=" + list[0] + ","
                                         + atrAngebotsdatum + "=" + "\"" + ui->lineAngebotsdatum->text() + "\","
                                         + atrGueltigkeit + "=" + "\"" + ui->lineGueltigkeit->text() + "\","
                                         + atrFirmenrabatt + "=" + "\"" + ui->doubleFirmenRabatt->text() + "\""
                                         + " WHERE " + atrAngebot + "=" + aId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Angebot nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Angebot::insertPosition( )
{
    if( aId == "0" )
    {
        insertAngebot( );
    }
    if( ui->lineAngebotsID->text().toInt() > 0 )
    {
        QStringList list = ui->comboProduktID->currentText().split(" ");
        query = new QSqlQuery( createPosition + ui->lineAngebotsID->text() + ","
                                              + ui->lineAngebotspositionsID->text() + ","
                                              + list[0] + ","
                                              + "\"" + ui->spinAnzahl->text() + "\","
                                              + "\"" + ui->doubleRabatt->text() + "\","
                                              + "\"" + ui->doubleTagespreis->text() + "\");" );
        if( query->lastError().isValid() )
        {
            QMessageBox::critical( 0, "Kann Angebotsposition nicht hinzufügen", query->lastError().text(), QMessageBox::Cancel );
        }
        getPositionen( );
        getPositionID( );
    }
    else
    {
        QMessageBox::critical(0, "Keine AngebotsID angegeben",
                                 "Geben Sie erst eine AngebotsID an,\nder die Position zugeordnet werden soll", QMessageBox::Cancel);
    }
}

void DBOp_Angebot::removePosition( )
{
    if( ui->tableAngebotspositionen->currentRow() > -1 )
    {
        if( QMessageBox::question(this, "Wirklich Löschen?", "Wollen Sie die Position wirklich \nunwiederruflich löschen?",
                                  QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
        {
            query = new QSqlQuery( deleteAPosition + ui->lineAngebotsID->text() + " AND " + atrAPosition + "="
                                                   + ui->tableAngebotspositionen->item(ui->tableAngebotspositionen->currentRow(),0)->text() + ";");
            if( query->lastError().isValid() )
            {
                QMessageBox::critical( 0, "Kann Angebotsposition nicht löschen", query->lastError().text(), QMessageBox::Cancel );
            }
            getPositionen( );
        }
    }
    else
    {
        QMessageBox::critical(0, "Keine Position zum Löschen ausgewählt",
                                 "Wählen Sie erst eine zu löschende Position\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void DBOp_Angebot::updatePosition( )
{
    if( ui->lineAngebotspositionsID->text().toInt() > 0 )
    {
        QStringList list = ui->comboProduktID->currentText().split(" ");
        query = new QSqlQuery( changePosition + atrAP_Angebot + "=" + ui->lineAngebotsID->text() + ","
                                              + atrAPosition + "=" + ui->lineAngebotspositionsID->text() + ","
                                              + atrAP_Produkt + "=" + list[0] + ","
                                              + atrApAnzahl + "=" + "\"" + ui->spinAnzahl->text() + "\","
                                              + atrApRabatt + "=" + "\"" + ui->doubleRabatt->text() + "\","
                                              + atrApTagespreis + "=" + "\"" + ui->doubleTagespreis->text() + "\""
                                              + " WHERE " + atrPosition + "=" + aId + ";");
        if( query->lastError().isValid() )
        {
            QMessageBox::critical( 0, "Kann Angebotsposition nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
        }
        getPositionen( );
    }
    else
    {
        QMessageBox::critical(0, "Keine AngebotsID angegeben",
                                 "Geben Sie erst eine AngebotspositionsID an", QMessageBox::Cancel);
    }
}
