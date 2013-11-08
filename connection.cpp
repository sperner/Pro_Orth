/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   connection.h
 * Description: Create a Connection to the Database
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

#include "connection.h"


//bool createConnection( )
//QSqlDatabase createConnection(QString driver, QString host, int port, QString dbname, QString user, QString pass)
bool createConnection(QString driver, QString host, int port, QString dbname, QString user, QString pass)
{
    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("Pro_Orth");
    db.setUserName("root");
    db.setPassword("pass");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection to"
            "\nServer: " + db.hostName() +" / " + QString::number(db.port()) +
            "\nDatabase: " + db.databaseName() +
            "\nDriver: " + db.driverName(),
            QMessageBox::Cancel);
        return false;
    }
    */
    /*
    QSqlDatabase database = QSqlDatabase::addDatabase(driver);
    database.setHostName(host);
    database.setPort(port);
    database.setDatabaseName(dbname);
    database.setUserName(user);
    database.setPassword(pass);
    if (!database.open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection to"
            "\nServer: " + host +" / " + port +
            "\nDatabase: " + dbname +
            "\nDriver: " + driver,
            QMessageBox::Cancel);
    }
    return database;
    */
    QSqlDatabase database = QSqlDatabase::addDatabase(driver);
    database.setHostName(host);
    database.setPort(port);
    database.setDatabaseName(dbname);
    database.setUserName(user);
    database.setPassword(pass);
    if (!database.open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection to"
            "\nServer: " + host +" / " + QString::number(port) +
            "\nDatabase: " + dbname +
            "\nDriver: " + driver,
            QMessageBox::Cancel);
        return false;
    }
    return true;
}
