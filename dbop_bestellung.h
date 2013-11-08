/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_bestellung.h
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

#ifndef DBOP_BESTELLUNG_H
#define DBOP_BESTELLUNG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "ui_dbop_bestellung.h"
#include "dbop_angebot.h"
#include "dbop_personenkunde.h"

#include <QDebug>


namespace Ui
{
    class DBOp_Bestellung;
}

class DBOp_Bestellung : public QDialog
{
    Q_OBJECT
public:
    DBOp_Bestellung(QString Id, QWidget *parent = 0);
    ~DBOp_Bestellung();

protected:
    void changeEvent(QEvent *aEvent);

private:
    Ui::DBOp_Bestellung *ui;
    QString bId;
    QSqlQuery *query;
    QTableWidgetItem *item;
    void getAutoID();
    void getAngebote();
    void getPersonenkunden();
    void getBestellung();
    void getPositionen();
    void setAngebot();

private slots:
    void neuAngebot();
    void neuPersonenkunde();
    void insertBestellung();
    void updateBestellung();
    void applyPositionen();
    void removePosition();
    void removePositionen();
};

#endif // DBOP_BESTELLUNG_H
