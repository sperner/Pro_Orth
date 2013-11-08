/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   mainwindow.cpp
 * Description: Main Graphical-User-Interface
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/05/18 19:20 sven Exp $
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statements.h"


//MainWindow::MainWindow( QWidget *parent, QSqlDatabase database )
MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent ), ui( new Ui::MainWindow )
{
    ui->setupUi( this );
    //Signale Menu Datei
    connect( ui->actionDateiNeu, SIGNAL(triggered()), this, SLOT(dateiNeu()) );
    connect( ui->actionDateiBearbeiten, SIGNAL(triggered()), this, SLOT(dateiBearbeiten()) );
    connect( ui->actionDateiLoeschen, SIGNAL(triggered()), this, SLOT(dateiLoeschen()) );
    connect( ui->actionDateiDrucken, SIGNAL(triggered()), this, SLOT(druckenDokument()) );
    connect( ui->actionDateiBeenden, SIGNAL(triggered()), this, SLOT(dateiBeenden()) );
    //Signale Menu Bearbeiten
    connect( ui->actionBearbeitenEinstellungen, SIGNAL(triggered()), this, SLOT(bearbeitenEinstellungen()) );
    //Signale Menu Hilfe
    connect( ui->actionHilfeUeber, SIGNAL(triggered()), this, SLOT(hilfeUeber()) );

    //Signale Tab Kunden
    connect( ui->radioFirmenkunden, SIGNAL(clicked()), this, SLOT(fillTableKunden_Firmenkunden()) );
    connect( ui->checkFiliale, SIGNAL(clicked()), this, SLOT(fillTableKunden_Firmenkunden()) );
    connect( ui->checkZentrale, SIGNAL(clicked()), this, SLOT(fillTableKunden_Firmenkunden()) );
    connect( ui->radioStandorte, SIGNAL(clicked()), this, SLOT(fillTableKunden_Standorte()) );
    connect( ui->radioPersonenkunden, SIGNAL(clicked()), this, SLOT(fillTableKunden_Personenkunden()) );
    connect( ui->pushSucheKunden, SIGNAL(clicked()), this, SLOT(sucheKunden()) );
    connect( ui->pushNeuKunde, SIGNAL(clicked()), this, SLOT(neuKunden()) );
    connect( ui->pushBearbeitenKunde, SIGNAL(clicked()), this, SLOT(bearbeitenKunden()) );
    connect( ui->pushLoeschenKunde, SIGNAL(clicked()), this, SLOT(loeschenKunden()) );
    connect( ui->lineKunden1, SIGNAL(returnPressed()), this, SLOT(sucheKunden()) );
    connect( ui->lineKunden2, SIGNAL(returnPressed()), this, SLOT(sucheKunden()) );
    connect( ui->lineKunden3, SIGNAL(returnPressed()), this, SLOT(sucheKunden()) );
    connect( ui->pushProdukte, SIGNAL(clicked()), this, SLOT(zeigeProdukte()) );
    connect( ui->pushLizenzen, SIGNAL(clicked()), this, SLOT(zeigeLizenzen()) );
    connect( ui->pushLeasing, SIGNAL(clicked()), this, SLOT(zeigeLeasing()) );
    connect( ui->pushMaintenace, SIGNAL(clicked()), this, SLOT(zeigeMaintenance()) );
    connect( ui->pushAngebote, SIGNAL(clicked()), this, SLOT(zeigeAngebote()) );
    connect( ui->pushBestellungen, SIGNAL(clicked()), this, SLOT(zeigeBestellungen()) );
    connect( ui->pushLieferungen, SIGNAL(clicked()), this, SLOT(zeigeLieferungen()) );
    connect( ui->pushRechnungen, SIGNAL(clicked()), this, SLOT(zeigeRechnungen()) );
    //Signale Tab Produkte
    connect( ui->radioProdukte, SIGNAL(clicked()), this, SLOT(fillTableProdukte_Produkte()) );
    connect( ui->radioLizenzen, SIGNAL(clicked()), this, SLOT(fillTableProdukte_Lizenzen()) );
    connect( ui->radioLeasing, SIGNAL(clicked()), this, SLOT(fillTableProdukte_Leasing()) );
    connect( ui->radioMaintenance, SIGNAL(clicked()), this, SLOT(fillTableProdukte_Maintenance()) );
    connect( ui->pushSucheProdukte, SIGNAL(clicked()), this, SLOT(sucheProdukte()) );
    connect( ui->pushNeuProdukt, SIGNAL(clicked()), this, SLOT(neuProdukt()) );
    connect( ui->pushBearbeitenProdukt, SIGNAL(clicked()), this, SLOT(bearbeitenProdukt()) );
    connect( ui->pushLoeschenProdukt, SIGNAL(clicked()), this, SLOT(loeschenProdukt()) );
    connect( ui->lineProdukte1, SIGNAL(returnPressed()), this, SLOT(sucheProdukte()) );
    connect( ui->lineProdukte2, SIGNAL(returnPressed()), this, SLOT(sucheProdukte()) );
    connect( ui->lineProdukte3, SIGNAL(returnPressed()), this, SLOT(sucheProdukte()) );
    connect( ui->pushHistorie, SIGNAL(clicked()), this, SLOT(zeigeHistorie()) );
    //Signale Tab Dokumente
    connect( ui->radioAngebote, SIGNAL(clicked()), this, SLOT(fillTableDokumente_Angebote()) );
    connect( ui->radioBestellungen, SIGNAL(clicked()), this, SLOT(fillTableDokumente_Bestellungen()) );
    connect( ui->radioLieferungen, SIGNAL(clicked()), this, SLOT(fillTableDokumente_Lieferungen()) );
    connect( ui->radioRechnungen, SIGNAL(clicked()), this, SLOT(fillTableDokumente_Rechnungen()) );
    connect( ui->pushSucheDokumente, SIGNAL(clicked()), this, SLOT(sucheDokumente()) );
    connect( ui->pushNeuDokument, SIGNAL(clicked()), this, SLOT(neuDokument()) );
    connect( ui->pushBearbeitenDokument, SIGNAL(clicked()), this, SLOT(bearbeitenDokument()) );
    connect( ui->pushLoeschenDokument, SIGNAL(clicked()), this, SLOT(loeschenDokument()) );
    connect( ui->lineDokumente1, SIGNAL(returnPressed()), this, SLOT(sucheDokumente()) );
    connect( ui->lineDokumente2, SIGNAL(returnPressed()), this, SLOT(sucheDokumente()) );
    connect( ui->lineDokumente3, SIGNAL(returnPressed()), this, SLOT(sucheDokumente()) );
    connect( ui->pushDrucken, SIGNAL(clicked()), this, SLOT(druckenDokument()) );

    //Tabellen fuellen
    fillTableKunden_Firmenkunden( );
    fillTableProdukte_Produkte( );
    fillTableDokumente_Angebote( );
}

MainWindow::~MainWindow( )
{
    delete ui;
}

void MainWindow::fillCombos( QComboBox *combo1, QComboBox *combo2, QComboBox *combo3,
                             QLineEdit *line1, QLineEdit *line2, QLineEdit *line3, QString statement )
{
    for( int i = combo1->count(); i>=0; i-- )
    {
        combo1->removeItem( i );
        combo2->removeItem( i );
        combo3->removeItem( i );
    }
    line1->clear();
    line2->clear();
    line3->clear();
    query = new QSqlQuery( statement );
    for( int i=0; i<query->record().count(); i++ )
    {
        combo1->addItem( query->record().fieldName(i) );
        combo2->addItem( query->record().fieldName(i) );
        combo3->addItem( query->record().fieldName(i) );
    }

}

void MainWindow::fillTable( QTableWidget *table, QString statement )
{
    query = new QSqlQuery( statement );
    //qDebug() << query->lastQuery()<<endl<<query->lastError();
    table->setColumnCount( query->record().count() );
    table->setRowCount( query->size() );
    for( int i=0; i<query->record().count(); i++ )
    {
        table->setHorizontalHeaderItem( i, new QTableWidgetItem(QString(query->record().fieldName(i)), QTableWidgetItem::Type) );
    }
    int row = 0;
    while( query->next() )
    {
        for( int i=0; i<query->record().count(); i++ )
        {
            item = new QTableWidgetItem( query->value(i).toString(), 0 );
            table->setItem( row, i, item );
        }
        row++;
    }
}

QString MainWindow::addConstraint( QString aQuery )
{
    if( aQuery.contains( "WHERE" ) )
    {   aQuery += " AND ";      }
    else
    {   aQuery += " WHERE ";    }
    return aQuery;
}

QString MainWindow::buildSearchQuery( QComboBox *combo1, QComboBox *combo2, QComboBox *combo3,
                                      QLineEdit *line1, QLineEdit *line2, QLineEdit *line3, QString aSearchQuery )
{
    if( line1->text() != "" )
    {
        aSearchQuery = addConstraint( aSearchQuery );
        aSearchQuery += combo1->currentText() + " LIKE \"%" + line1->text() + "%\"";
    }
    if( line2->text() != "" )
    {
        aSearchQuery = addConstraint( aSearchQuery );
        aSearchQuery += combo2->currentText() + " LIKE \"%" + line2->text() + "%\"";
    }
    if( line3->text() != "" )
    {
        aSearchQuery = addConstraint( aSearchQuery );
        aSearchQuery += combo3->currentText() + " LIKE \"%" + line3->text() + "%\"";
    }
    return aSearchQuery;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Slots Menu Datei
void MainWindow::dateiNeu( )
{
    if( ui->tabKunden->isVisible() )
    {   neuKunden();    }
    else if( ui->tabProdukte->isVisible() )
    {   neuProdukt();   }
    else if( ui->tabDokumente->isVisible() )
    {   neuDokument();  }
}

void MainWindow::dateiBearbeiten( )
{
    if( ui->tabKunden->isVisible() )
    {   bearbeitenKunden();    }
    else if( ui->tabProdukte->isVisible() )
    {   bearbeitenProdukt();   }
    else if( ui->tabDokumente->isVisible() )
    {   bearbeitenDokument();  }
}

void MainWindow::dateiLoeschen( )
{
    if( ui->tabKunden->isVisible() )
    {   loeschenKunden();    }
    else if( ui->tabProdukte->isVisible() )
    {   loeschenProdukt();   }
    else if( ui->tabDokumente->isVisible() )
    {   loeschenDokument();  }
}

void MainWindow::dateiBeenden( )
{
    QApplication::quit();
}


//Slots Menu Bearbeiten
void MainWindow::bearbeitenEinstellungen()
{
    Settings *einstellungen = new Settings();
    einstellungen->exec();
}


//Slots Menu Hilfe
void MainWindow::hilfeUeber( )
{
    About *ueber = new About();
    ueber->exec();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Slots Tab Kunden
void MainWindow::fillTableKunden_Firmenkunden( )
{
    if( ui->radioFirmenkunden->isChecked() )
    {
        QString queryStatement = selectFirmenkunden;
        if( ui->checkFiliale->isChecked() && ui->checkZentrale->isChecked() )
        {   queryStatement += whereZentraleFiliale;    }
        else if( ui->checkFiliale->isChecked() )
        {   queryStatement += whereFiliale;     }
        else if( ui->checkZentrale->isChecked() )
        {   queryStatement += whereZentrale;    }
        else if( !ui->checkFiliale->isChecked() && !ui->checkZentrale->isChecked() )
        {   queryStatement += whereStandortNULL;    }

        fillCombos( ui->comboKunden1, ui->comboKunden2, ui->comboKunden3,
                    ui->lineKunden1, ui->lineKunden2, ui->lineKunden3, queryStatement + ";" );
        fillTable( ui->tableKunden, queryStatement + ";" );
    }
}

void MainWindow::fillTableKunden_Standorte( )
{
    fillCombos( ui->comboKunden1, ui->comboKunden2, ui->comboKunden3,
                ui->lineKunden1, ui->lineKunden2, ui->lineKunden3, selectStandorte + ";" );
    fillTable( ui->tableKunden, selectStandorte + ";" );
}

void MainWindow::fillTableKunden_Personenkunden( )
{
    fillCombos( ui->comboKunden1, ui->comboKunden2, ui->comboKunden3,
                ui->lineKunden1, ui->lineKunden2, ui->lineKunden3, selectPersonenkunden + ";" );
    fillTable( ui->tableKunden, selectPersonenkunden + ";" );
}

void MainWindow::sucheKunden( )
{
    QString queryStatement;
    if( ui->radioFirmenkunden->isChecked() )
    {
        queryStatement = selectFirmenkunden;
        if( ui->checkFiliale->isChecked() && ui->checkZentrale->isChecked() )
        {   queryStatement += whereZentraleFiliale;     }
        else if( ui->checkFiliale->isChecked() )
        {   queryStatement += whereFiliale;             }
        else if( ui->checkZentrale->isChecked() )
        {   queryStatement += whereZentrale;            }
        else if( !ui->checkFiliale->isChecked() && !ui->checkZentrale->isChecked() )
        {   queryStatement += whereStandortNULL;        }
    }
    else if( ui->radioStandorte->isChecked() )
    {   queryStatement = selectStandorte;      }
    else if( ui->radioPersonenkunden->isChecked() )
    {   queryStatement = selectPersonenkunden;      }

    queryStatement = buildSearchQuery( ui->comboKunden1, ui->comboKunden2, ui->comboKunden3,
                                       ui->lineKunden1, ui->lineKunden2, ui->lineKunden3, queryStatement );

    fillTable( ui->tableKunden, queryStatement + ";" );
}

void MainWindow::neuKunden( )
{
    if( ui->radioFirmenkunden->isChecked() )
    {
        DBOp_Firmenkunde *newFirmenkunde = new DBOp_Firmenkunde( "0" );
        newFirmenkunde->exec( );
        fillTableKunden_Firmenkunden( );
    }
    else if( ui->radioStandorte->isChecked() )
    {
        DBOp_Standort *newStandort = new DBOp_Standort( "0" );
        newStandort->exec( );
        fillTableKunden_Standorte( );
    }
    else if( ui->radioPersonenkunden->isChecked() )
    {
        DBOp_Personenkunde *newPersonenkunde = new DBOp_Personenkunde( "0" );
        newPersonenkunde->exec( );
        fillTableKunden_Personenkunden( );
    }
}

void MainWindow::bearbeitenKunden( )
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        if( ui->radioFirmenkunden->isChecked() )
        {
            DBOp_Firmenkunde *newFirmenkunde = new DBOp_Firmenkunde( ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() );
            newFirmenkunde->exec( );
            fillTableKunden_Firmenkunden( );
        }
        else if( ui->radioStandorte->isChecked() )
        {
            DBOp_Standort *newStandort = new DBOp_Standort( ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() );
            newStandort->exec( );
            fillTableKunden_Standorte( );
        }
        else if( ui->radioPersonenkunden->isChecked() )
        {
            DBOp_Personenkunde *newPersonenkunde = new DBOp_Personenkunde( ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() );
            newPersonenkunde->exec( );
            fillTableKunden_Personenkunden( );
        }
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Bearbeiten ausgewählt",
                                 "Wählen Sie erst einen zu bearbeitenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void MainWindow::loeschenKunden( )
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        if( QMessageBox::question(this, "Wirklich Löschen?", "Wollen Sie den Kunden wirklich \nunwiederruflich löschen?",
                                  QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
        {
            if( ui->radioFirmenkunden->isChecked() )
            {
                query = new QSqlQuery( deleteFirmenkunden + ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() );
                fillTableKunden_Firmenkunden( );
            }
            else if( ui->radioStandorte->isChecked() )
            {
                query = new QSqlQuery( deleteStandort + ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() );
                fillTableKunden_Standorte( );
            }
            else if( ui->radioPersonenkunden->isChecked() )
            {
                query = new QSqlQuery( deletePersonenkunden + ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() );
                fillTableKunden_Personenkunden( );
            }
        }
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Löschen ausgewählt",
                                 "Wählen Sie erst einen zu löschenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void MainWindow::zeigeProdukte()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectProdukteWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectProdukteWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectProdukteWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByProdukt;
        ui->tabWidget->setCurrentIndex(1);
        ui->radioProdukte->setChecked( true );
        fillTable( ui->tableProdukte, queryStatement );
    }
}

void MainWindow::zeigeLizenzen()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectLizenzenWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectLizenzenWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectLizenzenWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByLizenz;
        ui->tabWidget->setCurrentIndex(1);
        ui->radioLizenzen->setChecked( true );
        fillTable( ui->tableProdukte, queryStatement );
    }
}

void MainWindow::zeigeLeasing()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectLeasingWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectLeasingWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectLeasingWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByLeasing;
        ui->tabWidget->setCurrentIndex(1);
        ui->radioLeasing->setChecked( true );
        fillTable( ui->tableProdukte, queryStatement );
    }
}

void MainWindow::zeigeMaintenance()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectMaintenanceWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectMaintenanceWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectMaintenanceWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByMaintenance;
        ui->tabWidget->setCurrentIndex(1);
        ui->radioMaintenance->setChecked( true );
        fillTable( ui->tableProdukte, queryStatement );
    }
}

void MainWindow::zeigeAngebote()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectAngeboteWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectAngeboteWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectAngeboteWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByAngebot;
        ui->tabWidget->setCurrentIndex(2);
        ui->radioAngebote->setChecked( true );
        fillTable( ui->tableDokumente, queryStatement );
    }
}

void MainWindow::zeigeBestellungen()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectBestellungenWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectBestellungenWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectBestellungenWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByBestellung;
        ui->tabWidget->setCurrentIndex(2);
        ui->radioBestellungen->setChecked( true );
        fillTable( ui->tableDokumente, queryStatement );
    }
}

void MainWindow::zeigeLieferungen()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectLieferungenWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectLieferungenWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectLieferungenWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByLieferung;
        ui->tabWidget->setCurrentIndex(2);
        ui->radioLieferungen->setChecked( true );
        fillTable( ui->tableDokumente, queryStatement );
    }
}

void MainWindow::zeigeRechnungen()
{
    if( ui->tableKunden->currentRow() > -1 )
    {
        QString queryStatement;
        if( ui->radioFirmenkunden->isChecked() )
        {   queryStatement += selectRechnungenWhereFK;      }
        else if( ui->radioStandorte->isChecked() )
        {   queryStatement += selectRechnungenWhereSO;         }
        else if( ui->radioPersonenkunden->isChecked() )
        {   queryStatement += selectRechnungenWherePK;    }
        queryStatement += ui->tableKunden->item(ui->tableKunden->currentRow(),0)->text() + orderByRechnung;
        ui->tabWidget->setCurrentIndex(2);
        ui->radioRechnungen->setChecked( true );
        fillTable( ui->tableDokumente, queryStatement );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Slots Tab Produkte
void MainWindow::fillTableProdukte_Produkte( )
{
    ui->pushHistorie->setEnabled( false );
    fillCombos( ui->comboProdukte1, ui->comboProdukte2, ui->comboProdukte3,
                ui->lineProdukte1, ui->lineProdukte2, ui->lineProdukte3, selectProdukte + ";" );
    fillTable( ui->tableProdukte, selectProdukte + ";" );
}

void MainWindow::fillTableProdukte_Lizenzen( )
{
    ui->pushHistorie->setEnabled( false );
    fillCombos( ui->comboProdukte1, ui->comboProdukte2, ui->comboProdukte3,
                ui->lineProdukte1, ui->lineProdukte2, ui->lineProdukte3, selectLizenzen + ";" );
    fillTable( ui->tableProdukte, selectLizenzen + ";" );
    qDebug()<<query->lastError();
}

void MainWindow::fillTableProdukte_Leasing( )
{
    ui->pushHistorie->setEnabled( true );
    fillCombos( ui->comboProdukte1, ui->comboProdukte2, ui->comboProdukte3,
                ui->lineProdukte1, ui->lineProdukte2, ui->lineProdukte3, selectZeitvertraege + whereLeasing + ";" );
    fillTable( ui->tableProdukte, selectZeitvertraege + whereLeasing + ";" );
}

void MainWindow::fillTableProdukte_Maintenance( )
{
    ui->pushHistorie->setEnabled( true );
    fillCombos( ui->comboProdukte1, ui->comboProdukte2, ui->comboProdukte3,
                ui->lineProdukte1, ui->lineProdukte2, ui->lineProdukte3, selectZeitvertraege + whereMaintenance + ";" );
    fillTable( ui->tableProdukte, selectZeitvertraege + whereMaintenance + ";" );
}

void MainWindow::sucheProdukte( )
{
    QString queryStatement;
    if( ui->radioProdukte->isChecked() )
    {   queryStatement = selectProdukte;        }
    else if( ui->radioLizenzen->isChecked() )
    {   queryStatement = selectLizenzen;        }
    else if( ui->radioLeasing->isChecked() )
    {   queryStatement = selectZeitvertraege + whereLeasing;         }
    else if( ui->radioMaintenance->isChecked() )
    {   queryStatement = selectZeitvertraege + whereMaintenance;     }

    queryStatement = buildSearchQuery( ui->comboProdukte1, ui->comboProdukte2, ui->comboProdukte3,
                                       ui->lineProdukte1, ui->lineProdukte2, ui->lineProdukte3, queryStatement );

    fillTable( ui->tableProdukte, queryStatement + ";" );
}

void MainWindow::neuProdukt( )
{
    if( ui->radioProdukte->isChecked() )
    {
        DBOp_Produkt *newProdukt = new DBOp_Produkt( "0" );
        newProdukt->exec( );
        fillTableProdukte_Produkte( );
    }
    else if( ui->radioLizenzen->isChecked() )
    {
        DBOp_Lizenz *newLizenz = new DBOp_Lizenz( "0" );
        newLizenz->exec( );
        fillTableProdukte_Lizenzen( );
    }
    else if( ui->radioLeasing->isChecked() )
    {
        DBOp_Zeitvertrag *newZeitvertrag = new DBOp_Zeitvertrag( "0", "Leasing" );
        newZeitvertrag->exec( );
        fillTableProdukte_Leasing( );
    }
    else if( ui->radioMaintenance->isChecked() )
    {
        DBOp_Zeitvertrag *newZeitvertrag = new DBOp_Zeitvertrag( "0", "Maintenance" );
        newZeitvertrag->exec( );
        fillTableProdukte_Maintenance( );
    }
}

void MainWindow::bearbeitenProdukt( )
{
    if( ui->tableProdukte->currentRow() > -1 )
    {
        if( ui->radioProdukte->isChecked() )
        {
            DBOp_Produkt *newProdukt = new DBOp_Produkt( ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
            newProdukt->exec( );
            fillTableProdukte_Produkte( );
        }
        else if( ui->radioLizenzen->isChecked() )
        {
            DBOp_Lizenz *newLizenz = new DBOp_Lizenz( ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
            newLizenz->exec( );
            fillTableProdukte_Lizenzen( );
        }
        else if( ui->radioLeasing->isChecked() )
        {
            DBOp_Zeitvertrag *newZeitvertrag = new DBOp_Zeitvertrag( ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text(), "Leasing" );
            newZeitvertrag->exec( );
            fillTableProdukte_Leasing( );
        }
        else if( ui->radioMaintenance->isChecked() )
        {
            DBOp_Zeitvertrag *newZeitvertrag = new DBOp_Zeitvertrag( ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text(), "Maintenance" );
            newZeitvertrag->exec( );
            fillTableProdukte_Maintenance( );
        }
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Bearbeiten ausgewählt",
                                 "Wählen Sie erst einen zu bearbeitenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void MainWindow::loeschenProdukt( )
{
    if( ui->tableProdukte->currentRow() > -1 )
    {
        if( QMessageBox::question(this, "Wirklich Löschen?", "Wollen Sie das Produkt wirklich \nunwiederruflich löschen?",
                                  QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
        {
            if( ui->radioProdukte->isChecked() )
            {
                query = new QSqlQuery( deleteProdukt + ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
                fillTableProdukte_Produkte( );
            }
            else if( ui->radioLizenzen->isChecked() )
            {
                query = new QSqlQuery( deleteLizenz + ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
                fillTableProdukte_Lizenzen( );
            }
            else if( ui->radioLeasing->isChecked() )
            {
                query = new QSqlQuery( deleteLeasing + ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
                fillTableProdukte_Leasing( );
            }
            else if( ui->radioMaintenance->isChecked() )
            {
                query = new QSqlQuery( deleteMaintenance + ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
                fillTableProdukte_Maintenance( );
            }
        }
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Löschen ausgewählt",
                                 "Wählen Sie erst einen zu löschenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void MainWindow::zeigeHistorie()
{
    if( ui->tableProdukte->currentRow() > -1 )
    {
        DBOp_Historie *newHistorie = new DBOp_Historie( ui->tableProdukte->item(ui->tableProdukte->currentRow(),0)->text() );
        newHistorie->exec( );
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Anzeigen der Historie ausgewählt",
                                 "Wählen Sie erst einen Eintrag aus der Tabelle aus\nzu dem die Historie angezeigt werden soll", QMessageBox::Cancel);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Slots Tab Dokumente
void MainWindow::fillTableDokumente_Angebote( )
{
    ui->pushDrucken->setEnabled( true );
    fillCombos( ui->comboDokumente1, ui->comboDokumente2, ui->comboDokumente3,
                ui->lineDokumente1, ui->lineDokumente2, ui->lineDokumente3, selectAngebote + ";" );
    fillTable( ui->tableDokumente, selectAngebote + ";" );
}

void MainWindow::fillTableDokumente_Bestellungen( )
{
    ui->pushDrucken->setEnabled( false );
    fillCombos( ui->comboDokumente1, ui->comboDokumente2, ui->comboDokumente3,
                ui->lineDokumente1, ui->lineDokumente2, ui->lineDokumente3, selectBestellungen + ";" );
    fillTable( ui->tableDokumente, selectBestellungen + ";" );
}

void MainWindow::fillTableDokumente_Lieferungen( )
{
    ui->pushDrucken->setEnabled( true );
    fillCombos( ui->comboDokumente1, ui->comboDokumente2, ui->comboDokumente3,
                ui->lineDokumente1, ui->lineDokumente2, ui->lineDokumente3, selectLieferungen + ";" );
    fillTable( ui->tableDokumente, selectLieferungen + ";" );
}

void MainWindow::fillTableDokumente_Rechnungen( )
{
    ui->pushDrucken->setEnabled( true );
    fillCombos( ui->comboDokumente1, ui->comboDokumente2, ui->comboDokumente3,
                ui->lineDokumente1, ui->lineDokumente2, ui->lineDokumente3, selectRechnungen + ";" );
    fillTable( ui->tableDokumente, selectRechnungen + ";" );
}

void MainWindow::sucheDokumente( )
{
    QString queryStatement;
    if( ui->radioAngebote->isChecked() )
    {   queryStatement = selectAngebote;    }
    else if( ui->radioBestellungen->isChecked() )
    {   queryStatement = selectBestellungen;  }
    else if( ui->radioLieferungen->isChecked() )
    {   queryStatement = selectLieferungen;  }
    else if( ui->radioRechnungen->isChecked() )
    {   queryStatement = selectRechnungen;  }

    queryStatement = buildSearchQuery( ui->comboDokumente1, ui->comboDokumente2, ui->comboDokumente3,
                                       ui->lineDokumente1, ui->lineDokumente2, ui->lineDokumente3, queryStatement );

    fillTable( ui->tableDokumente, queryStatement + ";" );
}

void MainWindow::neuDokument( )
{
    if( ui->radioAngebote->isChecked() )
    {
        DBOp_Angebot *newAngebot = new DBOp_Angebot( "0" );
        newAngebot->exec( );
        fillTableDokumente_Angebote( );
    }
    else if( ui->radioBestellungen->isChecked() )
    {
        DBOp_Bestellung *newBestellung = new DBOp_Bestellung( "0" );
        newBestellung->exec( );
        fillTableDokumente_Bestellungen( );
    }
    else if( ui->radioLieferungen->isChecked() )
    {
        DBOp_Lieferung *newLieferung = new DBOp_Lieferung( "0" );
        newLieferung->exec( );
        fillTableDokumente_Lieferungen( );
    }
    else if( ui->radioRechnungen->isChecked() )
    {
        DBOp_Rechnung *newRechnung = new DBOp_Rechnung( "0" );
        newRechnung->exec( );
        fillTableDokumente_Rechnungen( );
    }
}

void MainWindow::bearbeitenDokument( )
{
    if( ui->tableDokumente->currentRow() > -1 )
    {
        if( ui->radioAngebote->isChecked() )
        {
            DBOp_Angebot *newAngebot = new DBOp_Angebot( ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
            newAngebot->exec( );
            fillTableDokumente_Angebote( );
        }
        else if( ui->radioBestellungen->isChecked() )
        {
            DBOp_Bestellung *newBestellung = new DBOp_Bestellung( ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
            newBestellung->exec( );
            fillTableDokumente_Bestellungen( );
        }
        else if( ui->radioLieferungen->isChecked() )
        {
            DBOp_Lieferung *newLieferung = new DBOp_Lieferung( ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
            newLieferung->exec( );
            fillTableDokumente_Lieferungen( );
        }
        else if( ui->radioRechnungen->isChecked() )
        {
            DBOp_Rechnung *newRechnung = new DBOp_Rechnung( ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
            newRechnung->exec( );
            fillTableDokumente_Rechnungen( );
        }
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Bearbeiten ausgewählt",
                                 "Wählen Sie erst einen zu bearbeitenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void MainWindow::loeschenDokument( )
{
    if( ui->tableDokumente->currentRow() > -1 )
    {
        if( QMessageBox::question(this, "Wirklich Löschen?", "Wollen Sie das Dokument wirklich \nunwiederruflich löschen?",
                                  QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
        {
            if( ui->radioAngebote->isChecked() )
            {
                query = new QSqlQuery( deleteAngebot + ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
                fillTableDokumente_Angebote( );
            }
            else if( ui->radioBestellungen->isChecked() )
            {
                query = new QSqlQuery( deleteBestellung + ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
                fillTableDokumente_Bestellungen( );
            }
            else if( ui->radioLieferungen->isChecked() )
            {
                query = new QSqlQuery( deleteLieferung + ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
                fillTableDokumente_Lieferungen( );
            }
            else if( ui->radioRechnungen->isChecked() )
            {
                query = new QSqlQuery( deleteRechnung + ui->tableDokumente->item(ui->tableDokumente->currentRow(),0)->text() );
                fillTableDokumente_Rechnungen( );
            }
        }
    }
    else
    {
        QMessageBox::critical(0, "Kein Eintrag zum Löschen ausgewählt",
                                 "Wählen Sie erst einen zu löschenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
    }
}

void MainWindow::druckenDokument( )
{
    if( ui->tabWidget->currentIndex() == 2 )    
    {
        if ( ui->tableDokumente->currentRow() > -1 )
        {
            if ( ui->radioAngebote->isChecked() )
            {
                DB_Printer *printer = new DB_Printer( ui->tableDokumente->item(ui->tableDokumente->currentRow(), 0)->text() );
                printer->printAngebot();
            }
            if ( ui->radioLieferungen->isChecked() )
            {
                DB_Printer *printer = new DB_Printer( ui->tableDokumente->item(ui->tableDokumente->currentRow(), 0)->text() );
                printer->printLieferschein();
            }
            if ( ui->radioRechnungen->isChecked() )
            {
                DB_Printer *printer = new DB_Printer( ui->tableDokumente->item(ui->tableDokumente->currentRow(), 0)->text() );
                printer->printRechnung();
            }
            if ( ui->radioBestellungen->isChecked() )
            {
                QMessageBox::critical(0, "Bestellungen können nicht gedruckt werden",
                                         "Wählen Sie zwischen Angebot, Lieferung oder Rechnung", QMessageBox::Cancel);
            }
        }
        else
        {
            QMessageBox::critical(0, "Kein Eintrag zum Drucken ausgewählt",
                                     "Wählen Sie erst einen zu druckenden Eintrag\n aus der Tabelle aus", QMessageBox::Cancel);
        }
    }
    else
    {
        QMessageBox::critical(0, "Drucken ist hier nicht möglich",
                                 "Es können nur Dokumente ausgedruckt werden.\nGehen Sie dazu auf den Drucken-Tab.", QMessageBox::Cancel);
    }
}
