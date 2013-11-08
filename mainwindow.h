/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMessageBox>
//#include <QSqlDatabase>
#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "settings.h"
#include "about.h"
#include "dbop_firmenkunde.h"
#include "dbop_personenkunde.h"
#include "dbop_standort.h"
#include "dbop_produkt.h"
#include "dbop_lizenz.h"
#include "dbop_zeitvertrag.h"
#include "dbop_angebot.h"
#include "dbop_bestellung.h"
#include "dbop_lieferung.h"
#include "dbop_rechnung.h"
#include "db_printer.h"
#include "dbop_historie.h"

// just for debugging:
#include <QDebug>
//qDebug() << query->lastError().text();


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(QWidget *parent, QSqlDatabase database);
    MainWindow(QWidget *parent);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //QSqlDatabase *database;
    QSqlQuery *query;
    QTableWidgetItem *item;
    void fillCombos(QComboBox *combo1,QComboBox *combo2,QComboBox *combo3,
                    QLineEdit *line1,QLineEdit *line2,QLineEdit *line3,QString statement);
    void fillTable(QTableWidget *table,QString statement);
    QString addConstraint(QString aString);
    QString buildSearchQuery(QComboBox *combo1,QComboBox *combo2,QComboBox *combo3,
                             QLineEdit *line1,QLineEdit *line2,QLineEdit *line3,QString aSearchQuery);

private slots:
    //Slots Menu Datei
    void dateiNeu();
    void dateiBearbeiten();
    void dateiLoeschen();
    void dateiBeenden();

    //Slots Menu Bearbeiten
    void bearbeitenEinstellungen();

    //Slots Menu Hilfe
    void hilfeUeber();


    //Slots Tab Kunden
    void fillTableKunden_Firmenkunden();
    void fillTableKunden_Standorte();
    void fillTableKunden_Personenkunden();
    void sucheKunden();
    void neuKunden();
    void bearbeitenKunden();
    void loeschenKunden();
    void zeigeProdukte();
    void zeigeLizenzen();
    void zeigeLeasing();
    void zeigeMaintenance();
    void zeigeAngebote();
    void zeigeBestellungen();
    void zeigeLieferungen();
    void zeigeRechnungen();

    //Slots Tab Produkte
    void fillTableProdukte_Produkte();
    void fillTableProdukte_Lizenzen();
    void fillTableProdukte_Leasing();
    void fillTableProdukte_Maintenance();
    void sucheProdukte();
    void neuProdukt();
    void bearbeitenProdukt();
    void loeschenProdukt();
    void zeigeHistorie();

    //Slots Tab Dokumente
    void fillTableDokumente_Angebote();
    void fillTableDokumente_Bestellungen();
    void fillTableDokumente_Lieferungen();
    void fillTableDokumente_Rechnungen();
    void sucheDokumente();
    void neuDokument();
    void bearbeitenDokument();
    void loeschenDokument();
    void druckenDokument();
};

#endif // MAINWINDOW_H
