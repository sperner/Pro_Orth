/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_personenkunde.h
 * Description: Database-Operation with Personenkunden-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/05 15:00 sven Exp $
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

#ifndef DBOP_PERSONENKUNDE_H
#define DBOP_PERSONENKUNDE_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include "ui_dbop_personenkunde.h"
#include "dbop_standort.h"

#include <QDebug>

namespace Ui
{
    class DBOp_Personenkunde;
}

class DBOp_Personenkunde : public QDialog
{
    Q_OBJECT
public:
    DBOp_Personenkunde(QString Id, QWidget *parent = 0);
    ~DBOp_Personenkunde();

protected:
    void changeEvent(QEvent *aEvent);

private:
    Ui::DBOp_Personenkunde *ui;
    QString pkId;
    QSqlQuery *query;
    void getAutoID();
    void getStandorte();
    void getPersonenkunde();

private slots:
    void neuStandort();
    void insertPersonenkunde();
    void updatePersonenkunde();
};

#endif // DBOP_PERSONENKUNDE_H
