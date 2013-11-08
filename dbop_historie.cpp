/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   dbop_historie.cpp
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

#include "dbop_historie.h"
#include "ui_dbop_historie.h"


DBOp_Historie::DBOp_Historie(QString ZvID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBOp_Historie)
{
    ui->setupUi(this);
    this->ZvID = ZvID;

    query = new QSqlQuery( getHistorie + ZvID + " ORDER BY HID;" );
    ui->tableHistorie->setColumnCount( query->record().count() );
    ui->tableHistorie->setRowCount( query->size() );
    for( int i=0; i<query->record().count(); i++ )
    {
        ui->tableHistorie->setHorizontalHeaderItem( i, new QTableWidgetItem(QString(query->record().fieldName(i)), QTableWidgetItem::Type) );
    }
    int row = 0;
    while( query->next() )
    {
        for( int i=0; i<query->record().count(); i++ )
        {
            item = new QTableWidgetItem( query->value(i).toString(), 0 );
            ui->tableHistorie->setItem( row, i, item );
        }
        row++;
    }

}

DBOp_Historie::~DBOp_Historie()
{
    delete ui;
}
