/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_zeitvertrag.h
 * Description: Database-Operation with Zeitvertrags-Object
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

#ifndef DBOP_ZEITVERTRAG_H
#define DBOP_ZEITVERTRAG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include "ui_dbop_zeitvertrag.h"
#include "dbop_lizenz.h"

#include <QDebug>

namespace Ui
{
    class DBOp_Zeitvertrag;
}

class DBOp_Zeitvertrag : public QDialog
{
    Q_OBJECT
public:
    DBOp_Zeitvertrag(QString Id,QString Typ,QWidget *parent = 0);
    ~DBOp_Zeitvertrag();

protected:
    void changeEvent(QEvent *aEvent);

private:
    Ui::DBOp_Zeitvertrag *ui;
    QString zvId;
    QString zvTyp;
    QSqlQuery *query;
    void getAutoID();
    void getLizenzen();
    void getZeitvertrag();

private slots:
    void neuLizenz();
    void insertZeitvertrag();
    void updateZeitvertrag();
};

#endif // DBOP_ZEITVERTRAG_H
