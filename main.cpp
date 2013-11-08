/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   mainwindow.h
 * Description: Main-Funktion / -Program
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

#include <QtGui/QApplication>
#include <QFile>
#include <QSplashScreen>
#include <unistd.h>
#include "connection.h"
#include "mainwindow.h"
#include "settings.h"


int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    QIcon icon( "database.png" );
    app.setWindowIcon( icon );
    QSettings *conf;
    if( QFile::exists("settings.conf") == false )
    {
        Settings *einstellungen = new Settings( );
        einstellungen->exec( );
    }
    if( QFile::exists("settings.conf") )
    {
        conf = new QSettings( "settings.conf", QSettings::NativeFormat );
        int ret = createConnection(conf->value("Datenbanktyp").toString(),
                                   conf->value("Servername").toString(),
                                   conf->value("Serverport").toInt(),
                                   conf->value("Datenbankname").toString(),
                                   conf->value("Benutzername").toString(),
                                   conf->value("Passwort").toString()
                                  );
        while( ret == false )
        {
            Settings *einstellungen = new Settings( );
            if( einstellungen->exec() == 0 )
            {
                return -1;
            }
            ret = createConnection(conf->value("Datenbanktyp").toString(),
                                               conf->value("Servername").toString(),
                                               conf->value("Serverport").toInt(),
                                               conf->value("Datenbankname").toString(),
                                               conf->value("Benutzername").toString(),
                                               conf->value("Passwort").toString()
                                              );
        }
        if( ret == true )
        {
            QPixmap pic( "splash.jpg" );
            QSplashScreen splash( pic );
            splash.show( );
            MainWindow win( 0 );
            win.setWindowState( Qt::WindowMaximized );
            splash.setFont( QFont("OldEnglish", 18, QFont::Bold) );
            splash.showMessage( "starting application...", Qt::AlignHCenter|Qt::AlignTop, Qt::white );
            app.processEvents( );
            sleep( 1 );
            win.show( );
            splash.finish( &win );
            return app.exec( );
        }
    }
    return -1;
    //QSqlDatabase db = createConnection("QMYSQL","127.0.0.1",3306,"Pro_Orth","root","pass");
    //MainWindow win(0,db);
    //if( createConnection("QMYSQL","127.0.0.1",3306,"Pro_Orth","root","pass") == false )
}
