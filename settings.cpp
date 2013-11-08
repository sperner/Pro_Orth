/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   settings.cpp
 * Description: Settings of the Program
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

#include "settings.h"
#include "statements.h"


Settings::Settings( )
{
    setupUi( this );
    fillCombo( );

    //Signale
    connect( this->buttonBox, SIGNAL(accepted()), this, SLOT(save()) );
    connect( this->buttonBox, SIGNAL(rejected()), this, SLOT(close()) );
    connect( this->pushOeffnen, SIGNAL(clicked()), this, SLOT(openFile()) );
    connect( this->pushSchemaErstellen, SIGNAL(clicked()), this, SLOT(createSchema()) );
    connect( this->pushSchemaLoeschen, SIGNAL(clicked()), this, SLOT(deleteSchema()) );

    konfiguration = new QSettings( "settings.conf", QSettings::NativeFormat );
    load( );
}

Settings::~Settings( )
{
    delete this;
}


void Settings::fillCombo( )
{
    /*
    comboDatenbanktyp->addItem( "IBM_DB2" );
    comboDatenbanktyp->addItem( "Interbase" );
    comboDatenbanktyp->addItem( "MySQL" );
    comboDatenbanktyp->addItem( "ODBC" );
    comboDatenbanktyp->addItem( "Oracle" );
    comboDatenbanktyp->addItem( "PostgreSQL" );
    comboDatenbanktyp->addItem( "SQLite_v2" );
    comboDatenbanktyp->addItem( "SQLite_v3" );
    comboDatenbanktyp->addItem( "Sybase" );
    */
    comboDatenbanktyp->addItem( "QDB2" );
    comboDatenbanktyp->addItem( "QIBASE" );
    comboDatenbanktyp->addItem( "QMYSQL" );
    comboDatenbanktyp->addItem( "QOCI" );
    comboDatenbanktyp->addItem( "QODBC" );
    comboDatenbanktyp->addItem( "QPSQL" );
    comboDatenbanktyp->addItem( "QSQLITE" );
    comboDatenbanktyp->addItem( "QSQLITE2" );
    comboDatenbanktyp->addItem( "QTDS" );
}

void Settings::load()
{
    lineServername->insert( konfiguration->value("Servername").toString() );
    lineServerport->insert( konfiguration->value("Serverport").toString() );
    comboDatenbanktyp->setCurrentIndex( comboDatenbanktyp->findText(konfiguration->value("Datenbanktyp").toString(),Qt::MatchCaseSensitive) );
    lineDatenbankname->insert( konfiguration->value("Datenbankname").toString() );
    lineBenutzername->insert( konfiguration->value("Benutzername").toString() );
    linePasswort->insert( konfiguration->value("Passwort").toString() );
}



//Slots Buttons
void Settings::save( )
{
    konfiguration->setValue( "Servername", lineServername->text());
    konfiguration->setValue( "Serverport", lineServerport->text());
    konfiguration->setValue( "Datenbanktyp", comboDatenbanktyp->currentText());
    konfiguration->setValue( "Datenbankname", lineDatenbankname->text());
    konfiguration->setValue( "Benutzername", lineBenutzername->text());
    konfiguration->setValue( "Passwort", linePasswort->text());
    konfiguration->sync();
}

void Settings::close( )
{
    qDebug() << "closed Settings";
}

void Settings::openFile( )
{
    QFileDialog *fileSchema = new QFileDialog( );
    fileSchema->exec( );
    QStringList filesList = fileSchema->selectedFiles();
    this->lineSchema->setText( filesList[0] );
}

void Settings::createSchema( )
{
    QSqlQuery *query = new QSqlQuery( dropSchema );
}

void Settings::deleteSchema( )
{
    if( QMessageBox::question(this, "Schema wirklich Löschen?", "Wollen Sie das Datenbankschema wirklich \nunwiederruflich löschen?",
                              QMessageBox::Ok|QMessageBox::Cancel) == QMessageBox::Ok )
    {
        QSqlQuery *query = new QSqlQuery( dropSchema );
        if( query->lastError().isValid() )
        {
            QMessageBox::critical( 0, "Kann Schema nicht löschen", query->lastError().text(), QMessageBox::Cancel );
        }
    }
}
