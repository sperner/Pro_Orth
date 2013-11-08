/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_historie.h
 * Description: Database-Operation with Historie-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/07/02 14:20 julian Exp $
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

#ifndef DBOP_HISTORIE_H
#define DBOP_HISTORIE_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include "statements.h"

namespace Ui {
    class DBOp_Historie;
}

class DBOp_Historie : public QDialog
{
    Q_OBJECT

public:
    explicit DBOp_Historie(QString id, QWidget *parent = 0);
    ~DBOp_Historie();

private:
    Ui::DBOp_Historie *ui;
    QString ZvID;
    QSqlQuery *query;
    QTableWidgetItem *item;
};

#endif // DBOP_HISTORIE_H
