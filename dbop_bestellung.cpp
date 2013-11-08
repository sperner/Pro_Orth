/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_bestellung.cpp
 * Description: Database-Operation with Bestellungs-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/19 15:00 sven Exp $
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

#include "dbop_bestellung.h"
#include "statements.h"


DBOp_Bestellung::DBOp_Bestellung( QString Id, QWidget *parent ) :
    QDialog( parent ), ui( new Ui::DBOp_Bestellung )
{
    ui->setupUi( this );

    bId = Id;
    getAngebote( );
    getPersonenkunden( );
    QPushButton *applyButton = ui->buttonBox->button( QDialogButtonBox::Apply );
    if( bId == "0" )
    {
        getAutoID( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(insertBestellung()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(insertBestellung()) );
        this->setWindowIcon( QIcon(QString("db_add.png")) );
        ui->pushPositionenUebernehmen->setEnabled( true );
    }
    else
    {
        getBestellung( );
        getPositionen( );
        connect( applyButton, SIGNAL(clicked()), this, SLOT(updateBestellung()) );
        connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(updateBestellung()) );
        this->setWindowIcon( QIcon(QString("db_edit.png")) );
        ui->pushPositionenUebernehmen->setEnabled( false );
    }
    connect( ui->pushNeuA, SIGNAL(clicked()), this, SLOT(neuAngebot()) );
    connect( ui->pushNeuP, SIGNAL(clicked()), this, SLOT(neuPersonenkunde()) );
    connect( ui->pushPositionenUebernehmen, SIGNAL(clicked()), this, SLOT(applyPositionen()) );
    connect( ui->pushPositionEntfernen, SIGNAL(clicked()), this, SLOT(removePosition()) );
    connect( ui->pushAlleEntfernen, SIGNAL(clicked()), this, SLOT(removePositionen()) );
}

DBOp_Bestellung::~DBOp_Bestellung( )
{
    delete ui;
}

void DBOp_Bestellung::changeEvent( QEvent *aEvent )
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

void DBOp_Bestellung::getAutoID()
{
    query = new QSqlQuery( getB_Angebote );
    int nextId = 1;
    while( query->next() )
    {
        if( nextId == query->value(0).toInt() )
        {   nextId++;   }
    }
    ui->lineBestellungsID->setText( QString::number(nextId) );
}

void DBOp_Bestellung::getAngebote( )
{
    query = new QSqlQuery( getB_Angebote );
    for( int i = ui->comboAngebotsID->count(); i>=0; i-- )
    {
        ui->comboAngebotsID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboAngebotsID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                      query->value(2).toString() + " " + query->value(3).toString() + " " +
                                      query->value(4).toString() + " " + query->value(5).toString() + " " +
                                      query->value(6).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Angebote nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Bestellung::getPersonenkunden( )
{
    query = new QSqlQuery( getB_Personenkunden );
    for( int i = ui->comboPersonenkundenID->count(); i>=0; i-- )
    {
        ui->comboPersonenkundenID->removeItem( i );
    }
    while( query->next() )
    {
        ui->comboPersonenkundenID->addItem( query->value(0).toString() + " " + query->value(1).toString() + " " +
                                            query->value(2).toString() + " " + query->value(3).toString() + " " +
                                            query->value(4).toString() + " " + query->value(5).toString() + " " +
                                            query->value(6).toString() );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Personenkunden nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Bestellung::getBestellung( )
{
    query = new QSqlQuery( chooseBestellung + bId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->lineBestellungsID->setText( query->value(0).toString() );
        ui->lineBestllungsdatum->setText(query->value(1).toString() );
        ui->comboPersonenkundenID->setCurrentIndex( ui->comboPersonenkundenID->findText(query->value(2).toString(),Qt::MatchStartsWith) );
    }
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Bestellung nicht finden", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Bestellung::getPositionen( )
{
    setAngebot();
    query = new QSqlQuery( getB_Positionen + bId + bPosOrder );
    ui->tableBestellungspositionen->setColumnCount( query->record().count() );
    ui->tableBestellungspositionen->setRowCount( query->size() );
    for( int i=0; i<query->record().count(); i++ )
    {
        ui->tableBestellungspositionen->setHorizontalHeaderItem( i, new QTableWidgetItem(QString(query->record().fieldName(i)), QTableWidgetItem::Type) );
    }
    int row = 0;
    while( query->next() )
    {
        for( int i=0; i<query->record().count(); i++ )
        {
            item = new QTableWidgetItem( query->value(i).toString(), 0 );
            ui->tableBestellungspositionen->setItem( row, i, item );
        }
        row++;
    }
}

void DBOp_Bestellung::setAngebot( )
{
    query = new QSqlQuery( getB_AngebotsID + bId + ";" );
    query->next( );
    if( query->isValid() )
    {
        ui->comboAngebotsID->setCurrentIndex( ui->comboAngebotsID->findText(query->value(2).toString(),Qt::MatchStartsWith) );
    }
}


//Slots
void DBOp_Bestellung::neuAngebot( )
{
    DBOp_Angebot *newAngebot = new DBOp_Angebot( "0" );
    newAngebot->exec( );
    getAngebote( );
}

void DBOp_Bestellung::neuPersonenkunde( )
{
    DBOp_Personenkunde *newPersonenkunde = new DBOp_Personenkunde( "0" );
    newPersonenkunde->exec( );
    getPersonenkunden( );
}

void DBOp_Bestellung::insertBestellung( )
{
    if( bId == "0" )
    {
        bId = ui->lineBestellungsID->text();
        QStringList list = ui->comboPersonenkundenID->currentText().split(" ");
        query = new QSqlQuery( createBestellung + ui->lineBestellungsID->text() + ","
                                                + "\"" + ui->lineBestllungsdatum->text() + "\","
                                                + list[0] + ");" );
        if( query->lastError().isValid() )
        {
            QMessageBox::critical( 0, "Kann Bestellung nicht erstellen", query->lastError().text(), QMessageBox::Cancel );
        }
    }
    else
    {
        updateBestellung( );
    }
}

void DBOp_Bestellung::updateBestellung( )
{
    QStringList list = ui->comboPersonenkundenID->currentText().split(" ");
    query = new QSqlQuery( changeBestellung + atrBestellung + "=" + ui->lineBestellungsID->text() + ","
                                            + atrBestellungsdatum + "=" + "\"" + ui->lineBestllungsdatum->text() + "\","
                                            + atrB_Personenkunde + "=" + list[0]
                                            + " WHERE " + atrBestellung + "=" + bId + ";");
    if( query->lastError().isValid() )
    {
        QMessageBox::critical( 0, "Kann Bestellung nicht bearbeiten", query->lastError().text(), QMessageBox::Cancel );
    }
}

void DBOp_Bestellung::applyPositionen( )
{
    if( bId == "0" )
    {
        insertBestellung( );
    }
    if( ui->lineBestellungsID->text().toInt() > 0 )
    {
        ui->pushPositionenUebernehmen->setEnabled( false );
        QSqlQuery *iQuery;
        QStringList list = ui->comboAngebotsID->currentText().split(" ");
        query = new QSqlQuery( getB_APositionen + list[0] + ";" );
        while( query->next() )
        {
            iQuery = new QSqlQuery( setB_Position + ui->lineBestellungsID->text() + "," + query->value(1).toString() + ","
                                                  + query->value(0).toString() + "," + query->value(1).toString() + ","
                                                  + query->value(3).toString() + ");" );
            qDebug() << "Query: " << iQuery->lastQuery() << endl << "Error: " << iQuery->lastError();
        }
        getPositionen( );
    }
    else
    {
        QMessageBox::critical(0, "Keine BestellungsID angegeben",
                                 "Geben Sie erst eine BestellungsID an,\nder die Positionen zugeordnet werden sollen", QMessageBox::Cancel);
    }
}

void DBOp_Bestellung::removePosition( )
{
    if( ui->tableBestellungspositionen->currentRow() > -1 )
    {
        if( QMessageBox::question(this, "Wirklich Löschen?", "Wollen Sie die Positionen wirklich \nunwiederruflich löschen?",
                                  QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
        {
            query = new QSqlQuery( deleteBPosition + ui->lineBestellungsID->text() + " AND " + atrBPosition + "="
                                                   + ui->tableBestellungspositionen->item(ui->tableBestellungspositionen->currentRow(),0)->text() + ";");
            if( query->lastError().isValid() )
            {
                QMessageBox::critical( 0, "Kann Bestellungsposition nicht löschen", query->lastError().text(), QMessageBox::Cancel );
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

void DBOp_Bestellung::removePositionen( )
{
    if( QMessageBox::critical(0, "Alle Positionen entfernen", "Wollen Sie wirklich alle Positionen\naus der Bestellung entfernen?",
                              QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
    {
        query = new QSqlQuery( deleteBPosition + ui->lineBestellungsID->text() + ";");
        if( query->lastError().isValid() )
        {
            QMessageBox::critical( 0, "Kann Bestellungspositionen nicht löschen", query->lastError().text(), QMessageBox::Cancel );
        }
        getPositionen( );
        ui->pushPositionenUebernehmen->setEnabled( true );
    }
}
