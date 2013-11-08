/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_angebot.h
 * Description: Database-Operation with Angebot-Object
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2010/06/11 13:00 sven Exp $
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

#ifndef DBOP_ANGEBOT_H
#define DBOP_ANGEBOT_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include "ui_dbop_angebot.h"
#include "dbop_standort.h"
#include "dbop_produkt.h"

#include <QDebug>


namespace Ui
{
    class DBOp_Angebot;
}

class DBOp_Angebot : public QDialog
{
    Q_OBJECT
public:
    DBOp_Angebot(QString Id,QWidget *parent = 0);
    ~DBOp_Angebot();

protected:
    void changeEvent(QEvent *aEvent);

private:
    Ui::DBOp_Angebot *ui;
    QString aId;
    QSqlQuery *query;
    QTableWidgetItem *item;
    void getAutoID();
    void getPositionID();
    void getStandorte();
    void getProdukte();
    void getAngebot();
    void getPositionen();

private slots:
    void setRabatt();
    void setTagespreis();
    void neuStandort();
    void neuProdukt();
    void insertAngebot();
    void updateAngebot();
    void insertPosition();
    void removePosition();
    void updatePosition();
};

#endif // DBOP_ANGEBOT_H
