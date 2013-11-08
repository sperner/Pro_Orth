/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   db_printer.h
 * Description: Database-Operation to Print Documents
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/25 15:00 julian Exp $
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

#ifndef DB_PRINTER_H
#define DB_PRINTER_H

#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <QVariant>
#include <QSqlError>
#include <QWidget>
#include "statements.h"
#include "float.h"

static QString header = "<html>"
                        "<head>"
                        "<style type=\"text/css\">"
                        ".abs {font-size:6pt;}"
                        ".angebotheader {font-size:15pt;}"
                        "</style>"
                        "</head>"
                        "<body>"
                        "<h2>Softwarevertrieb Sperner-Kaufmann</h2>"
                        "<div align=\"right\">Niebelungenplatz 1<br/>D-60318 Frankfurt am Main<br/>Tel: 01234-5678<br/>Fax: 01234-5679</div>"
                        "<div class=\"abs\">Softwarevertrieb Sperner-Kaufmann, Niebelungenplatz 1, D-60318 Frankfurt am Main</font></div>";

class DB_Printer
{
public:
    DB_Printer(QString Id);
    ~DB_Printer();
    void printAngebot();
    void printLieferschein();
    void printRechnung();

private:
    QString Id;
    QSqlQuery *query;
    QSqlQuery *queryHauptdaten;
    QSqlQuery *queryAnschrift;
    QSqlQuery *queryPositionen;
    QTextDocument textDoc;
    QPrinter printer;
    QString tmpString;
    QVariant nettoPreis;
    QVariant mwst;
    QString formattedMwst;
    QVariant bruttoPreis;
    QString formattedBruttoPreis;
};

#endif // DB_PRINTER_H
