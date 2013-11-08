/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   db_printer.cpp
 * Description: Print out of Documents
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
#include "db_printer.h"

DB_Printer::DB_Printer(QString Id)
{
    this->Id = Id;
}

DB_Printer::~DB_Printer()
{

}

void DB_Printer::printAngebot( )
{
    QPrintDialog printDialog(&printer);
    printDialog.exec();

    query = new QSqlQuery( getAngebotDaten + Id + " ORDER BY AP.APosition;");
    query->next();

    QString gueltigkeitsdatum = query->value(2).toString();

    tmpString.append(header + "<div>"
                   + query->value(7).toString() + "<br/>"
                   + query->value(8).toString() + "<br/>"
                   + query->value(9).toString() + "<br/>"
                   + query->value(10).toString() + "<br/>" + query->value(11).toString() + " "
                   + query->value(12).toString() + "</div>"
                   "<div align=\"right\">" + query->value(1).toString() + "</div><br/>"
                   "<div class=\"angebotheader\" align=\"center\">AngebotNr. " + query->value(0).toString() + "<br/></div>"
                   "<table><tr><th width=\"10%\">Pos</th><th>Bezeichnung</th><th width=\"10%\">Menge</th>"
                   "<th width=\"15%\">Preis p. Einheit</th><th width=\"15%\">Gesamtpreis</th></tr>");
    do {
        QVariant tagespreis = query->value(5).toFloat()*(1.0-query->value(3).toFloat()/100.0);
        QString tmpTagespreis; QString tmpGesamtpreis;
        QVariant gesamtpreis = tagespreis.toFloat()*query->value(6).toFloat();

        tmpString.append("<tr><td>" + query->value(4).toString() + "</td>"
                         "<td>" + query->value(13).toString() +"<br/>Version: " + query->value(14).toString() + "</td>"
                         "<td>" + query->value(6).toString() + "</td>"
                         "<td align=\"right\">" + tmpTagespreis.setNum(tagespreis.toFloat(), 'f', 2) + " &euro;</td>"
                         "<td align=\"right\">" + tmpGesamtpreis.setNum(gesamtpreis.toFloat(), 'f', 2) + " &euro;</td></tr>");
    } while (query->next());
    tmpString.append("</table><br/><div> Bedingungen: <br/>"
               "<br/> - Es gelten die Softwarevertrieb Sperner-Kaufmann Lizenzbedingungen<br/> "
               "<br/> - Alle Preise verstehen sich zzgl. ges. Ust.<br/>"
               "<br/> - Das Angebot ist gültig bis "+ gueltigkeitsdatum + "</div>"
               "<div><br/>Mit freundlichen Grüßen <br/>Softwarevertrieb Sperner-Kaufmann </div>"
               "</body></html>");

    textDoc.setHtml(tmpString);
    textDoc.print(&printer);
}

void DB_Printer::printLieferschein( )
{
    QPrintDialog printDialog(&printer);
    printDialog.exec();

    queryHauptdaten = new QSqlQuery( getLieferungsDaten + Id + ";");
    queryHauptdaten->next();
    queryAnschrift = new QSqlQuery( getLieferungsAnschrift + queryHauptdaten->value(5).toString() + ";");
    queryAnschrift->next();
    queryPositionen = new QSqlQuery( getLieferungsPositionen + queryHauptdaten->value(3).toString() + " ORDER BY BP.BPosition;");
    queryPositionen->next();

    tmpString.append(header + "<div>"
                     + queryAnschrift->value(9).toString() + "<br/>"
                     + "z.Hd. " + queryAnschrift->value(1).toString() + " " + queryAnschrift->value(2).toString() + "<br/>"
                     + queryAnschrift->value(7).toString() + "<br/>"
                     + queryAnschrift->value(5).toString() + " " + queryAnschrift->value(6).toString() + "</div>"
                     "<div align=\"right\">" + queryHauptdaten->value(1).toString() + "</div><br/>"
                     "<div class=\"angebotheader\" align=\"center\">Lieferung Nr. " + queryHauptdaten->value(0).toString() + "</div>"
                     "<div><br/>Betrifft Bestellung Nr." + queryHauptdaten->value(3).toString() + " vom " + queryHauptdaten->value(4).toString() + "<br/>"
                     "Tracking Nr.: " + queryHauptdaten->value(2).toString() + "<br/></div>"
                     "<table  width=\"100%\"><tr><th width=\"10%\">Pos</th><th>Bezeichnung</th><th width=\"10%\">Menge</th></tr>");

    do {
        tmpString.append("<tr><td>" + queryPositionen->value(0).toString() + "</td>"
                         "<td>" + queryPositionen->value(2).toString() + "<br/>Version: " + queryPositionen->value(3).toString() +"</td>"
                         "<td>" + queryPositionen->value(1).toString() + "</td></tr>");
    } while (queryPositionen->next());

    tmpString.append("</table><br/><div> Die Rechnungslegung erfolgt separat. <br/> Das Produkt bleibt bis zur "
                     "vollstaendigen Bezahlung unser Eigentum. </div>"
                     "<div><br/><br/>Mit freundlichen Grüßen <br/>Softwarevertrieb Sperner-Kaufmann </div>"
                     "</body></html>");

    textDoc.setHtml(tmpString);
    textDoc.print(&printer);
}

void DB_Printer::printRechnung( )
{
    QPrintDialog printDialog(&printer);
    printDialog.exec();

    queryHauptdaten = new QSqlQuery( getRechnungsDaten + Id + ";");
    queryHauptdaten->next();
    queryAnschrift = new QSqlQuery( getRechnungsAnschrift + queryHauptdaten->value(7).toString() + ";");
    queryAnschrift->next();
    queryPositionen = new QSqlQuery( getRechnungsPositionen + queryHauptdaten->value(5).toString() + " ORDER BY BP.BPosition;");
    queryPositionen->next();
    nettoPreis=0;

    tmpString.append(header + "<div>" + queryAnschrift->value(9).toString() + "<br/>"
                    + "z.Hd. " + queryAnschrift->value(1).toString() + " " + queryAnschrift->value(2).toString() + "<br/>"
                    + queryAnschrift->value(7).toString() + "<br/>"
                    + queryAnschrift->value(5).toString() + " "
                    + queryAnschrift->value(6).toString() + "</div>"
                    "<div align=\"right\">" + queryHauptdaten->value(1).toString() + "</div><br/>"
                    "<div class=\"angebotheader\" align=\"center\">Rechnung Nr. " + queryHauptdaten->value(0).toString() + "</div>"
                    "<div><br/>Betrifft Bestellung Nr." + queryHauptdaten->value(5).toString() + " vom " + queryHauptdaten->value(6).toString() + "<br/></div>"
                    "<div>Sehr geehrte Damen und Herren, <br/><br/>hiermit erlauben wir uns für unsere Lieferung Nr. " + queryHauptdaten->value(8).toString()
                    + " vom " + queryHauptdaten->value(9).toString() + " folgenden Betrag in Rechnung zu stellen.<br/></div>"
                    "<table  width=\"100%\"><tr><th width=\"10%\">Pos</th><th>Bezeichnung</th><th width=\"10%\">Menge</th>"
                    "<th width=\"15%\">Preis p. Einheit</th><th width=\"10%\">Gesamtpreis</th></tr>");
    do {
        QVariant tagespreis = queryPositionen->value(3).toFloat() * ( 1.0-queryPositionen->value(2).toFloat() / 100.0 );
        QString tmpTagespreis; QString tmpProduktGesamtpreis;
        QVariant produktGesamtpreis = tagespreis.toFloat()*queryPositionen->value(1).toFloat();

        tmpString.append("<tr><td>" + queryPositionen->value(0).toString() + "</td>"
                         "<td>" + queryPositionen->value(4).toString() + "<br/>Version: " + queryPositionen->value(5).toString() +"</td>"
                         "<td>" + queryPositionen->value(1).toString() + "</td>"
                         "<td align=\"right\">" + tmpTagespreis.setNum(tagespreis.toFloat(), 'f', 2) + " &euro;</td>"
                         "<td align=\"right\">" + tmpProduktGesamtpreis.setNum(produktGesamtpreis.toFloat(), 'f', 2) + " &euro;</td></tr>");
        nettoPreis = nettoPreis.toFloat() + produktGesamtpreis.toFloat();
    } while (queryPositionen->next());

    mwst = nettoPreis.toFloat() * ( queryHauptdaten->value(3).toFloat() / 100 );
    formattedMwst.setNum( mwst.toFloat(), 'f', 2 );
    bruttoPreis = nettoPreis.toFloat() + mwst.toFloat();
    formattedBruttoPreis.setNum( bruttoPreis.toFloat(), 'f', 2 );

    tmpString.append("<tr><td/><td/><td/><td>Netto </td><td align=\"right\">" + nettoPreis.toString() + " &euro;</td></tr>"
                     "<tr><td/><td/><td/><td>MwSt " + queryHauptdaten->value(3).toString() + "%</td><td align=\"right\">" + formattedMwst + " &euro;</td></tr>"
                     "<tr><td/><td/><td/><td>Brutto </td><td align=\"right\">" + formattedBruttoPreis + " &euro;</td></tr>");

    if ( queryHauptdaten->value(4).toString() == "Bankeinzug" ) {
        tmpString.append("</table><br/><div>Der Gesamtbetrag von " + formattedBruttoPreis + " &euro; wird von ihrem folgenden Konto abgebucht: "
                         "<br/>KtoNr. " + queryAnschrift->value(10).toString() + ", BLZ " + queryAnschrift->value(11).toString()  + "</div>"
                         "<div><br/><br/>Mit freundlichen Grüßen <br/>Softwarevertrieb Sperner-Kaufmann </div>"
                         "</body></html>");
    }
    else {
        tmpString.append("</table><br/><div>Wir bitten Sie den Gesamtbetrag in von " + formattedBruttoPreis + " &euro; auf das "
                         "folgende Konto zu überweisen: <br/>KtoNr. 1111111, Sparkasse Frankfurt, BLZ 10020030</div>"
                         "<div><br/><br/>Mit freundlichen Grüßen <br/>Softwarevertrieb Sperner-Kaufmann </div>"
                         "</body></html>");
    }

    textDoc.setHtml(tmpString);
    textDoc.print(&printer);
}



