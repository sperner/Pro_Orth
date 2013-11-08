/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_lizenz.cpp
 * Description: Database-Operation with Lizenz-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/04 15:00 sven Exp $
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

#include "dbop_lizenz.h"
#include "statements.h"


DBOp_Lizenz::DBOp_Lizenz( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Lizenz )
{
    ui->setupUi( this );

    lzId = Id;
    getProdukte( );
    getPersonenkunden( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( lzId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertLizenz()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertLizenz()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getLizenz( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateLizenz()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateLizenz()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
    connect( ui->pushNeuPr, SIGNAL(clicked()), this, SLOT(neuProdukt()) );
    connect( ui->pushNeuPk, SIGNAL(clicked()), this, SLOT(neuPersonenkunde()) );
}

DBOp_Lizenz::~DBOp_Lizenz( )
{
    delete ui;
}

void DBOp_Lizenz::changeEvent( QEvent *aEvent )
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

void DBOp_Lizenz::getAutoID()
{
    query = new QSqlQuery( getLizenzen );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineLizenzID->setText( QString::number(nextId) );
}

void DBOp_Lizenz::getProdukte( )
{
    query = new QSqlQuery( getLZ_Produkte );
    for( int i = ui->comboProduktID->count(); i>=0; i-- )
    {
        ui->comboProduktID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboProduktID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                     query->value(2).toString() + " " + query->value(3).toString() + "Euro" );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Produkte nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Lizenz::getPersonenkunden( )
{
    query = new QSqlQuery( getLZ_Personenkunden );
    for( int i = ui->comboPersonenkunde->count(); i>=0; i-- )
    {
        ui->comboPersonenkunde->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboPersonenkunde->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                         query->value(2).toString() + " " + query->value(3).toString() + " " +
                                         query->value(4).toString() + " " + query->value(5).toString() + " " +
                                         query->value(6).toString() + " " + query->value(7).toString() + " " +
                                         query->value(8).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Personenkunden nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Lizenz::getLizenz( )
{
    query = new QSqlQuery( chooseLizenz + lzId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineLizenzID->setText( query->value(0).toString() );
        ui->comboPersonenkunde->setCurrentIndex( ui->comboPersonenkunde->findText(query->value(1).toString(),Qt::MatchStartsWith) );
        ui->comboProduktID->setCurrentIndex( ui->comboProduktID->findText(query->value(2).toString(),Qt::MatchStartsWith) );
        ui->lineSchluessel->setText( query->value(3).toString() );
        ui->lineInformation->setText( query->value(4).toString() );
        ui->lineVerkaufsdatum->setText( query->value(5).toString() );
        ui->lineAblaufsdatum->setText( query->value(6).toString() );
        if( query->value(7).toString() == "J" )
        {    ui->checkUpgrade->setChecked( true );    }
        else
        {    ui->checkUpgrade->setChecked( false );    }
        ui->lineTyp->setText( query->value(8).toString() );
        ui->doubleRabatt->setValue( query->value(9).toDouble() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Standort nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Lizenz::neuProdukt( )
{
    DBOp_Produkt *newProdukt = new DBOp_Produkt( "0" );
    newProdukt->exec();
    getProdukte( );
}

void DBOp_Lizenz::neuPersonenkunde( )
{
    DBOp_Personenkunde *newPersonenkunde = new DBOp_Personenkunde( "0" );
    newPersonenkunde->exec();
    getPersonenkunden( );
}

void DBOp_Lizenz::insertLizenz( )
{
    QStringList listPk = ui->comboPersonenkunde->currentText().split(" ");
    QStringList listPr = ui->comboProduktID->currentText().split(" ");
    QString upgradeValue;
    if( ui->checkUpgrade->isChecked() )
    {   upgradeValue = "J";}
    else
    {   upgradeValue = "N";}
    query = new QSqlQuery( createLizenz + ui->lineLizenzID->text() + ","
                                        + listPk[0] + ","
                                        + listPr[0] + ","
                                        + "\"" + ui->lineSchluessel->text() + "\","
                                        + "\"" + ui->lineInformation->text() + "\","
                                        + "\"" + ui->lineVerkaufsdatum->text() + "\","
                                        + "\"" + ui->lineAblaufsdatum->text() + "\","
                                        + "\"" + upgradeValue + "\","
                                        + "\"" + ui->lineTyp->text() + "\","
                                        + "\"" + ui->doubleRabatt->text() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Lizenz nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Lizenz::updateLizenz( )
{
    QStringList listPk = ui->comboPersonenkunde->currentText().split(" ");
    QStringList listPr = ui->comboProduktID->currentText().split(" ");
    QString upgradeValue;
    if( ui->checkUpgrade->isChecked() )
    {   upgradeValue = "J";}
    else
    {   upgradeValue = "N";}
    query = new QSqlQuery( changeLizenz + atrLizenz + "=" + ui->lineLizenzID->text() + ","
                                        + atrLZ_Personenkunde + "=" + listPk[0] + ","
                                        + atrLZ_Produkt + "=" + listPr[0] + ","
                                        + atrSchluessel + "=" + "\"" + ui->lineSchluessel->text() + "\","
                                        + atrInformation + "=" + "\"" + ui->lineInformation->text() + "\","
                                        + atrVerkaufsdatum + "=" + "\"" + ui->lineVerkaufsdatum->text() + "\","
                                        + atrAblaufsdatum + "=" + "\"" + ui->lineAblaufsdatum->text() + "\","
                                        + atrUpgrade + "=" + "\"" + upgradeValue + "\","
                                        + atrLizenztyp + "=" + "\"" + ui->lineTyp->text() + "\","
                                        + atrRabatt + "=" + "\"" + ui->doubleRabatt->text() + "\""
                                        + " WHERE " + atrLizenz + "=" + lzId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Lizenz nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
