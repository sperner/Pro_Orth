/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_produkt.cpp
 * Description: Database-Operation with Produkt-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/05 17:00 sven Exp $
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

#include "dbop_produkt.h"
#include "statements.h"


DBOp_Produkt::DBOp_Produkt( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Produkt )
{
    ui->setupUi( this );

    pId = Id;
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( pId == "0" )
    {
        getAutoID();
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertProdukt()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertProdukt()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
    }
    else
    {
        getProdukt( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateProdukt()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateProdukt()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
    }
}

DBOp_Produkt::~DBOp_Produkt( )
{
    delete ui;
}

void DBOp_Produkt::changeEvent( QEvent *aEvent )
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

void DBOp_Produkt::getAutoID()
{
    query = new QSqlQuery( getProdukte );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineProduktID->setText( QString::number(nextId) );
}

void DBOp_Produkt::getProdukt( )
{
    query = new QSqlQuery( chooseProdukt + pId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineProduktID->setText( query->value(0).toString() );
        ui->lineProduktname->setText( query->value(1).toString() );
        ui->lineVersion->setText( query->value(2).toString() );
        ui->doublePreis->setValue( query->value(3).toDouble() );
        ui->textAnforderungen->setText( query->value(4).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Produkt nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}


//Slots
void DBOp_Produkt::insertProdukt( )
{
    query = new QSqlQuery( createProdukt + ui->lineProduktID->text() + ","
                                         + "\"" + ui->lineProduktname->text() + "\","
                                         + "\"" + ui->lineVersion->text() + "\","
                                         + "\"" + ui->doublePreis->text() + "\","
                                         + "\"" + ui->textAnforderungen->toPlainText() + "\");" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Produkt nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Produkt::updateProdukt( )
{
    query = new QSqlQuery( changeProdukt + atrProdukt + "=" + ui->lineProduktID->text() + ","
                                         + atrProduktname + "=\"" + ui->lineProduktname->text() + "\","
                                         + atrVersion + "=\"" + ui->lineVersion->text() + "\","
                                         + atrPreis + "=\"" + ui->doublePreis->text() + "\","
                                         + atrAnforderungen + "=\"" + ui->textAnforderungen->toPlainText() + "\""
                                         + " WHERE " + atrProdukt + "=" + pId + ";" );
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Produkt nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}
