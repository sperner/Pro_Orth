/**
 * Project:     Programmier-Praktikum mit Datenbanken
 * File name:   statements.h
 * Description: SQL-Statements
 *
 * @author:     Julian Kaufmann & Sven Sperner
 * @version $Id: gpl.txt,v 1.0 2014/02/11 09:40 sven Exp $
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

#ifndef STATEMENTS_H
#define STATEMENTS_H


static QString dropSchema =             "DROP SCHEMA IF EXISTS ";
static QString createSchema =           "CREATE SCHEMA IF NOT EXISTS ";


static QString selectFirmenkunden =     "SELECT FK.FkID, FK.Firmenname, FK.Homepage, FK.Branche, SO.Standorttyp, "
                                        "SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Postfach, SO.Land, SO.KontoNr, SO.BLZ "
                                        "FROM Firmenkunden FK LEFT OUTER JOIN Standorte SO ON FK.FkID = SO.So_FkID ";
static QString whereZentraleFiliale =   "WHERE (SO.Standorttyp = \"Filiale\" OR SO.Standorttyp = \"Zentrale\")";
static QString whereFiliale =           "WHERE SO.Standorttyp = \"Filiale\"";
static QString whereZentrale =          "WHERE SO.Standorttyp = \"Zentrale\"";
static QString whereStandortNULL =      ""; //WHERE S.Standorttyp = NULL";
static QString selectStandorte =        "SELECT SoID, Standorttyp, PLZ, Stadt, Strasse_HNr, Postfach, Land, KontoNr, BLZ "
                                        "FROM Standorte";
static QString selectPersonenkunden =   "SELECT PK.PkID, PK.Anrede, PK.Vorname, PK.Nachname, PK.Position, "
                                        "PK.Telefon, PK.Fax, PK.Email, FK.Firmenname, "
                                        "SO.Standorttyp, SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Land "
                                        "FROM Personenkunden PK LEFT OUTER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "LEFT OUTER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID";


static QString selectProdukte =         "SELECT * FROM Produkte";
static QString selectLizenzen =         "SELECT LZ.LzID, PR.PrName, PR.Version, LZ.Schluessel, LZ.Information, "
                                        "LZ.Lizenztyp, LZ.Verkaufsdatum, LZ.Ablaufsdatum, LZ.Upgrade, LZ.Rabatt, "
                                        "FK.Firmenname, SO.Stadt, PK.Anrede, PK.Vorname, PK.Nachname "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID";
static QString selectZeitvertraege =    "SELECT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, PR.PrName, PR.Version, "
                                        "LZ.Schluessel, LZ.Information, LZ.Lizenztyp "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID ";
static QString whereLeasing =           "WHERE ZV.Vertragstyp = \"Leasing\"";
static QString whereMaintenance =       "WHERE ZV.Vertragstyp = \"Maintenance\"";


static QString selectAngebote =         "SELECT A.AID, A.AngDatum, A.Gueltigkeit, A.Firmenrabatt, FK.Firmenname, "
                                        "SO.Standorttyp, SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Postfach, SO.Land "
                                        "FROM Angebote A INNER JOIN Standorte SO ON A.A_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID";
static QString selectBestellungen =     "SELECT B.BID, B.BestellDatum, FK.Firmenname, "
                                        "PK.Anrede, PK.Vorname, PK.Nachname, PK.Telefon, PK.Fax, PK.Email, PK.Gebaeude, "
                                        "SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Postfach, SO.Land "
                                        "FROM Bestellungen B INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID";
static QString selectLieferungen =      "SELECT LG.LgID, LG.TrackingNr, LG.LieferDatum, "
                                        "B.BestellDatum, FK.Firmenname, "
                                        "PK.Anrede, PK.Vorname, PK.Nachname, PK.Telefon, PK.Email, "
                                        "SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Postfach, SO.Land "
                                        "FROM Lieferungen LG INNER JOIN Bestellungen B ON LG.Lg_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID";
static QString selectRechnungen =       "SELECT R.RID, R.RDatum, R.Faelligkeit, R.Zahlungsart, R.MwSt, FK.Firmenname, "
                                        "PK.Anrede, PK.Vorname, PK.Nachname, PK.Telefon, PK.Email, "
                                        "SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Postfach, SO.Land "
                                        "FROM Rechnungen R INNER JOIN Bestellungen B ON R.R_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID";



static QString chooseFirmenkunde =      "SELECT * FROM Firmenkunden WHERE FkID=";
static QString createFirmenkunde =      "INSERT INTO Firmenkunden VALUES(";
static QString changeFirmenkunde =      "UPDATE Firmenkunden SET ";
static QString getFirmenkunden =        "SELECT * FROM Firmenkunden ORDER BY FkID;";
static QString atrFirmenkunde =         "FkID";
static QString atrFirmenname =          "Firmenname";
static QString atrHomepage =            "Homepage";
static QString atrBranche =             "Branche";

static QString chooseStandort =         "SELECT * FROM Standorte WHERE SoID=";
static QString createStandort =         "INSERT INTO Standorte VALUES(";
static QString changeStandort =         "UPDATE Standorte SET ";
static QString getStandorte =           "SELECT * FROM Standorte ORDER BY SoID;";
static QString getSO_Firmenkunden =     "SELECT * FROM Firmenkunden ORDER BY FkID;";
static QString atrStandort =            "SoID";
static QString atrSO_Firmenkunde =      "SO_FkID";
static QString atrStandorttyp =         "Standorttyp";
static QString atrPLZ =                 "PLZ";
static QString atrStadt =               "Stadt";
static QString atrStrasse =             "Strasse_HNr";
static QString atrPostfach =            "Postfach";
static QString atrLand =                "Land";
static QString atrKonto =               "KontoNr";
static QString atrBank =                "BLZ";

static QString choosePersonenkunde =    "SELECT * FROM Personenkunden WHERE PkID=";
static QString createPersonenkunde =    "INSERT INTO Personenkunden VALUES(";
static QString changePersonenkunde =    "UPDATE Personenkunden SET ";
static QString getPersonenkunden =      "SELECT * FROM Personenkunden ORDER BY PkID;";
static QString getPK_Standorte =        "SELECT * FROM Standorte SO, Firmenkunden FK WHERE SO.So_FkID = FK.FkID ORDER BY SO.SoID;";
static QString atrPersonenkunde =       "PkID";
static QString atrPK_Standort =         "PK_SoID";
static QString atrAnrede =              "Anrede";
static QString atrVorname =             "Vorname";
static QString atrNachname =            "Nachname";
static QString atrPosition =            "Position";
static QString atrAbteilung =           "Abteilung";
static QString atrGebaeude =            "Gebaeude";
static QString atrZimmer =              "Zimmer";
static QString atrTelefon =             "Telefon";
static QString atrFax =                 "Fax";
static QString atrEmail =               "Email";


static QString chooseProdukt =          "SELECT * FROM Produkte WHERE PrID=";
static QString createProdukt =          "INSERT INTO Produkte VALUES(";
static QString changeProdukt =          "UPDATE Produkte SET ";
static QString getProdukte =            "SELECT * FROM Produkte ORDER BY PrID;";
static QString atrProdukt =             "PrId";
static QString atrProduktname =         "PrName";
static QString atrVersion =             "Version";
static QString atrPreis =               "Preis";
static QString atrAnforderungen =       "Anforderung";

static QString chooseLizenz =           "SELECT * FROM Lizenzen WHERE LzID=";
static QString createLizenz =           "INSERT INTO Lizenzen VALUES(";
static QString changeLizenz =           "UPDATE Lizenzen SET ";
static QString getLizenzen =            "SELECT * FROM Lizenzen ORDER BY LzID;";
static QString getLZ_Produkte =         "SELECT * FROM Produkte ORDER BY  PrID;";
static QString getLZ_Personenkunden =   "SELECT PK.PkID, PK.Anrede, PK.Vorname, PK.Nachname, "
                                        "FK.Firmenname, SO.PLZ, SO.Stadt, SO.Strasse_HNr, SO.Land "
                                        "FROM Personenkunden PK LEFT OUTER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "LEFT OUTER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID ORDER BY PK.PkID;";
static QString atrLizenz =              "LzID";
static QString atrLZ_Produkt =          "Lz_PrID";
static QString atrLZ_Personenkunde =    "Lz_PkID";
static QString atrSchluessel =          "Schluessel";
static QString atrInformation =         "Information";
static QString atrVerkaufsdatum =       "Verkaufsdatum";
static QString atrAblaufsdatum =        "Ablaufsdatum";
static QString atrUpgrade =             "Upgrade";
static QString atrLizenztyp =           "Lizenztyp";
static QString atrRabatt =              "Rabatt";

static QString chooseZeitvertrag =      "SELECT * FROM Zeitvertraege WHERE ZvID=";
static QString createZeitvertrag =      "INSERT INTO Zeitvertraege VALUES(";
static QString changeZeitvertrag =      "UPDATE Zeitvertraege SET ";
static QString getZeitvertraege =       "SELECT * FROM Zeitvertraege ORDER BY ZvID;";
static QString getZV_Lizenzen =         "SELECT LZ.LzID, PR.PrName, PR.Version, LZ.Schluessel, "
                                        "FK.Firmenname, SO.Stadt, PK.Anrede, PK.Vorname, PK.Nachname "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID ORDER BY LZ.LzID;";
static QString atrZeitvertrag =         "ZvID";
static QString atrZV_Lizenz =           "Zv_LzID";
static QString atrVertragstyp =         "Vertragstyp";
static QString atrVertragsbeginn =      "Vertragsbeginn";
static QString atrVertragsende =        "Vertragsende";
static QString atrMonatsbetrag =        "Monatsbetrag";
static QString atrZahlungsart =         "Zahlungsart";
static QString atrBezahltBis =          "BezahltBis";


static QString chooseAngebot =          "SELECT * FROM Angebote WHERE AID=";
static QString createAngebot =          "INSERT INTO Angebote VALUES(";
static QString changeAngebot =          "UPDATE Angebote SET ";
static QString getAngebote =            "SELECT * FROM Angebote ORDER BY AID;";
static QString getA_Standorte =         "SELECT * FROM Standorte SO INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID ORDER BY SO.SoID;";
static QString getA_Produkte =          "SELECT * FROM Produkte ORDER BY PrID;";
static QString getA_Positionen =        "SELECT AP.APosition, PR.PrName, PR.Version, AP.ApAnzahl, AP.Rabatt, AP.Tagespreis "
                                        "FROM AngebotsPositionen AP INNER JOIN Produkte PR ON AP.Ap_PrID = PR.PrID WHERE AP.Ap_AID=";
static QString aPosOrder =              " ORDER BY AP.APosition;";
static QString createPosition =         "INSERT INTO AngebotsPositionen VALUES(";
static QString changePosition =         "UPDATE AngebotsPositionen SET ";
static QString atrAngebot =             "AID";
static QString atrA_Standort =          "A_SoID";
static QString atrAngebotsdatum =       "AngDatum";
static QString atrGueltigkeit =         "Gueltigkeit";
static QString atrFirmenrabatt =        "Firmenrabatt";
static QString atrAP_Angebot =          "Ap_AID";
static QString atrAPosition =           "APosition";
static QString atrAP_Produkt =          "Ap_PrID";
static QString atrApAnzahl =            "ApAnzahl";
static QString atrApRabatt =            "Rabatt";
static QString atrApTagespreis =        "Tagespreis";

static QString chooseBestellung =       "SELECT * FROM Bestellungen WHERE BID=";
static QString createBestellung =       "INSERT INTO Bestellungen VALUES(";
static QString changeBestellung =       "UPDATE Bestellungen SET ";
static QString getBestellungen =        "SELECT * FROM Bestellungen ORDER BY BID;";
static QString getB_Angebote =          "SELECT A.AID, FK.Firmenname, A.AngDatum, A.Gueltigkeit, SO.PLZ, SO.Stadt, SO.Strasse_HNr "
                                        "FROM Angebote A INNER JOIN Standorte SO ON A.A_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID ORDER BY A.AID;";
static QString getB_Personenkunden =    "SELECT PK.PkID, FK.Firmenname, SO.Standorttyp, SO.Stadt, PK.Anrede, PK.Vorname, PK.Nachname "
                                        "FROM Personenkunden PK INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID ORDER BY PK.PkID;";
static QString getB_Positionen =        "SELECT BP.BPosition, PR.PrName, PR.Version, BP.BpAnzahl, AP.Rabatt, AP.Tagespreis "
                                        "FROM BestellungsPositionen BP INNER JOIN AngebotsPositionen AP "
                                        "ON BP.Bp_AID = AP.Ap_AID AND BP.Bp_ApID = AP.APosition "
                                        "INNER JOIN Produkte PR ON AP.Ap_PrID = PR.PrID WHERE BP.Bp_BID=";
static QString bPosOrder =              " ORDER BY BP.BPosition;";
static QString getB_AngebotsID =        "SELECT * FROM BestellungsPositionen WHERE Bp_BID=";
static QString getB_APositionen =       "SELECT * FROM AngebotsPositionen WHERE Ap_AID=";
static QString setB_Position =          "INSERT INTO BestellungsPositionen VALUES(";
static QString atrBestellung =          "BID";
static QString atrB_Personenkunde =     "B_PkID";
static QString atrBestellungsdatum =    "BestellDatum";
static QString atrBPosition =           "BPosition";
static QString atrBP_Bestellung =       "Bp_BID";
static QString atrBP_Angebot =          "Bp_AID";
static QString atrBP_APosition =        "Bp_ApID";
static QString atrBP_Anzahl =           "BpAnzahl";

static QString chooseLieferung =        "SELECT * FROM Lieferungen WHERE LgID=";
static QString createLieferung =        "INSERT INTO Lieferungen VALUES(";
static QString changeLieferung =        "UPDATE Lieferungen SET ";
static QString getLieferungen =         "SELECT * FROM Lieferungen ORDER BY LgID;";
static QString getL_Bestellungen =      "SELECT B.BID, B.Bestelldatum, FK.Firmenname, PK.Anrede, PK.Vorname, PK.Nachname, "
                                        "SO.PLZ, SO.Stadt, SO.Strasse_HNr "
                                        "FROM Bestellungen B INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID;";
static QString atrLieferung =           "LgID";
static QString atrLieferdatum =         "LieferDatum";
static QString atrL_Bestellung =        "Lg_BID";
static QString atrTrackingNr =          "TrackingNr";

static QString chooseRechnung =         "SELECT * FROM Rechnungen WHERE RID=";
static QString createRechnung =         "INSERT INTO Rechnungen VALUES(";
static QString changeRechnung =         "UPDATE Rechnungen SET ";
static QString getRechnungen =          "SELECT * FROM Rechnungen ORDER BY RID;";
static QString getR_Bestellungen =      "SELECT B.BID, B.Bestelldatum, FK.Firmenname, PK.Anrede, PK.Vorname, PK.Nachname, "
                                        "SO.PLZ, SO.Stadt, SO.Strasse_HNr "
                                        "FROM Bestellungen B INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID;";
static QString atrRechnung =            "RID";
static QString atrRechnungsdatum =      "RDatum";
static QString atrFaelligkeit =         "Faelligkeit";
static QString atrMwSt =                "MwSt";
static QString atrR_Bestellung =        "R_BID";
static QString atrZahlungsArt =         "Zahlungsart";



static QString deleteFirmenkunden =     "DELETE FROM Firmenkunden WHERE FkID = ";
static QString deleteStandort =         "DELETE FROM Standorte WHERE SoID = ";
static QString deletePersonenkunden =   "DELETE FROM Personenkunden WHERE PkID = ";
static QString deleteProdukt =          "DELETE FROM Produkte WHERE PrID = ";
static QString deleteLizenz =           "DELETE FROM Lizenzen WHERE LzID = ";
static QString deleteLeasing =          "DELETE FROM Zeitvertraege WHERE Vertragstyp = \"Leasing\" AND ZvID = ";
static QString deleteMaintenance =      "DELETE FROM Zeitvertraege WHERE Vertragstyp = \"Maintenance\" AND ZvID = ";
static QString deleteAngebot =          "DELETE FROM Angebote WHERE AID = ";
static QString deleteAPosition =        "DELETE FROM AngebotsPositionen WHERE Ap_AID = ";
static QString deleteBestellung =       "DELETE FROM Bestellungen WHERE BID = ";
static QString deleteBPosition =        "DELETE FROM BestellungsPositionen WHERE Bp_BID = ";
static QString deleteLieferung =        "DELETE FROM Lieferungen WHERE LgID = ";
static QString deleteRechnung =         "DELETE FROM Rechnungen WHERE RID = ";



static QString selectProdukteWhereFK =  "SELECT DISTINCT PR.*, FK.Firmenname "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectProdukteWherePK =  "SELECT DISTINCT PR.*, PK.Vorname, PK.Nachname "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectProdukteWhereSO =  "SELECT DISTINCT PR.*, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByProdukt =         " ORDER BY PR.PrID;";

static QString selectLizenzenWhereFK =  "SELECT DISTINCT LZ.LzID, LZ.Schluessel, LZ.Information, LZ.Lizenztyp, "
                                        "LZ.Verkaufsdatum, LZ.Ablaufsdatum, LZ.Upgrade, LZ.Rabatt, FK.Firmenname, PR.PrName, PR.Version "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectLizenzenWherePK =  "SELECT DISTINCT LZ.LzID, LZ.Schluessel, LZ.Information, LZ.Lizenztyp, "
                                        "LZ.Verkaufsdatum, LZ.Ablaufsdatum, LZ.Upgrade, LZ.Rabatt, PK.Vorname, PK.Nachname, PR.PrName, PR.Version "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectLizenzenWhereSO =  "SELECT DISTINCT LZ.LzID, LZ.Schluessel, LZ.Information, LZ.Lizenztyp, "
                                        "LZ.Verkaufsdatum, LZ.Ablaufsdatum, LZ.Upgrade, LZ.Rabatt, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt, PR.PrName, PR.Version "
                                        "FROM Lizenzen LZ INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByLizenz =         " ORDER BY LZ.LzID;";

static QString selectLeasingWhereFK =  "SELECT DISTINCT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, FK.Firmenname, PR.PrName, PR.Version, LZ.Schluessel "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectLeasingWherePK =  "SELECT DISTINCT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, PK.Vorname, PK.Nachname, PR.PrName, PR.Version, LZ.Schluessel "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectLeasingWhereSO =  "SELECT DISTINCT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt, PR.PrName, PR.Version, LZ.Schluessel "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByLeasing =         " AND ZV.Vertragstyp=\"Leasing\" ORDER BY LZ.LzID;";

static QString selectMaintenanceWhereFK =  "SELECT DISTINCT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, FK.Firmenname, PR.PrName, PR.Version, LZ.Schluessel "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectMaintenanceWherePK =  "SELECT DISTINCT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, PK.Vorname, PK.Nachname, PR.PrName, PR.Version, LZ.Schluessel "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectMaintenanceWhereSO =  "SELECT DISTINCT ZV.ZvID, ZV.Vertragsbeginn, ZV.Vertragsende, ZV.Monatsbetrag, "
                                        "ZV.Zahlungsart, ZV.BezahltBis, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt, PR.PrName, PR.Version, LZ.Schluessel "
                                        "FROM Zeitvertraege ZV INNER JOIN Lizenzen LZ ON ZV.Zv_LzID = LZ.LzID "
                                        "INNER JOIN Produkte PR ON LZ.Lz_PrID = PR.PrID "
                                        "INNER JOIN Personenkunden PK ON LZ.Lz_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByMaintenance =     " AND ZV.Vertragstyp=\"Maintenance\" ORDER BY LZ.LzID;";


static QString selectAngeboteWhereFK =  "SELECT DISTINCT A.AID, A.AngDatum, A.Gueltigkeit, A.Firmenrabatt, FK.Firmenname "
                                        "FROM Angebote A INNER JOIN Standorte SO ON A.AID = A.A_SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectAngeboteWherePK =  "SELECT DISTINCT A.AID, A.AngDatum, A.Gueltigkeit, A.Firmenrabatt, PK.Vorname, PK.Nachname "
                                        "FROM Angebote A INNER JOIN Standorte SO ON A.AID = A.A_SoID "
                                        "INNER JOIN Personenkunden PK ON PK.Pk_SoID = SO.SoID WHERE PK.PkID=";
static QString selectAngeboteWhereSO =  "SELECT DISTINCT A.AID, A.AngDatum, A.Gueltigkeit, A.Firmenrabatt, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt "
                                        "FROM Angebote A INNER JOIN Standorte SO ON A.AID = A.A_SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByAngebot =         " ORDER BY A.AID;";

static QString selectBestellungenWhereFK =  "SELECT DISTINCT B.BID, B.BestellDatum, FK.Firmenname "
                                        "FROM Bestellungen B INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectBestellungenWherePK =  "SELECT DISTINCT B.BID, B.BestellDatum, PK.Vorname, PK.Nachname "
                                        "FROM Bestellungen B INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectBestellungenWhereSO =  "SELECT DISTINCT B.BID, B.BestellDatum, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt "
                                        "FROM Bestellungen B INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByBestellung =      " ORDER BY B.BID;";

static QString selectLieferungenWhereFK =  "SELECT DISTINCT LG.LgID, LG.TrackingNr, LG.LieferDatum, FK.Firmenname "
                                        "FROM Lieferungen LG INNER JOIN Bestellungen B ON LG.Lg_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectLieferungenWherePK =  "SELECT DISTINCT LG.LgID, LG.TrackingNr, LG.LieferDatum, PK.Vorname, PK.Nachname "
                                        "FROM Lieferungen LG INNER JOIN Bestellungen B ON LG.Lg_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectLieferungenWhereSO =  "SELECT DISTINCT LG.LgID, LG.TrackingNr, LG.LieferDatum, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt "
                                        "FROM Lieferungen LG INNER JOIN Bestellungen B ON LG.Lg_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByLieferung =       " ORDER BY LG.LgID;";

static QString selectRechnungenWhereFK =  "SELECT DISTINCT R.RID, R.RDatum, R.Faelligkeit, R.Zahlungsart, R.MwSt, FK.Firmenname "
                                        "FROM Rechnungen R INNER JOIN Bestellungen B ON R.R_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE FK.FkID=";
static QString selectRechnungenWherePK =  "SELECT DISTINCT R.RID, R.RDatum, R.Faelligkeit, R.Zahlungsart, R.MwSt, PK.Vorname, PK.Nachname "
                                        "FROM Rechnungen R INNER JOIN Bestellungen B ON R.R_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE PK.PkID=";
static QString selectRechnungenWhereSO =  "SELECT DISTINCT R.RID, R.RDatum, R.Faelligkeit, R.Zahlungsart, R.MwSt, FK.Firmenname, SO.Strasse_HNr, SO.PLZ, SO.Stadt "
                                        "FROM Rechnungen R INNER JOIN Bestellungen B ON R.R_BID = B.BID "
                                        "INNER JOIN Personenkunden PK ON B.B_PkID = PK.PkID "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID = SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID = FK.FkID WHERE SO.SoID=";
static QString orderByRechnung =        " ORDER BY R.RID;";



static QString getAngebotDaten=         "SELECT A.AID, A.AngDatum, A.Gueltigkeit, AP.Rabatt, AP.APosition, "
                                        "AP.Tagespreis , AP.APAnzahl, F.Firmenname, S.Standorttyp, S.Strasse_HNr, "
                                        "S.Postfach, S.PLZ, S.Stadt, P.PrName, P.Version "
                                        "FROM Angebote A "
                                        "INNER JOIN AngebotsPositionen AP ON A.AID=AP.Ap_AID "
                                        "INNER JOIN Standorte S ON A.A_SoID=S.SoID "
                                        "INNER JOIN Firmenkunden F ON S.So_FkID=F.FkID "
                                        "INNER JOIN Produkte P ON AP.Ap_PrID=P.PrID "
                                        "WHERE A.AID=";

static QString getLieferungsDaten=      "SELECT L.LgID, L.Lieferdatum, L.TrackingNr, L.Lg_BID, B.Bestelldatum, B.B_PkID "
                                        "FROM Lieferungen L "
                                        "INNER JOIN Bestellungen B "
                                        "ON L.Lg_BID=B.BID "
                                        "WHERE L.LgID=";
static QString getLieferungsAnschrift=  "SELECT PK.Anrede, PK.Vorname, PK.Nachname, PK.Gebaeude, PK.Zimmer, SO.PLZ, "
                                        "SO.Stadt, SO.Strasse_HNr, SO.Postfach, FK.Firmenname FROM Pro_Orth.Personenkunden PK "
                                        "INNER JOIN Pro_Orth.Standorte SO ON PK.Pk_SoID=SO.SoID "
                                        "INNER JOIN Pro_Orth.Firmenkunden FK ON SO.So_FkID=FK.FkID WHERE PK.PkID=";
static QString getLieferungsPositionen=  "SELECT BP.BPosition, BP.BpAnzahl, P.PrName, P.Version, P.Anforderung "
                                        "FROM BestellungsPositionen BP "
                                        "INNER JOIN AngebotsPositionen AP "
                                        "ON BP.Bp_AID=AP.Ap_AID AND BP.Bp_ApID=AP.APosition "
                                        "INNER JOIN Produkte P ON AP.Ap_PrID=P.PrID "
                                        "WHERE BP.Bp_BID=";

static QString  getRechnungsDaten=       "SELECT R.RID, R.RDatum, R.Faelligkeit, R.MwSt, R.Zahlungsart, B.BID, B.BestellDatum, "
                                        "B.B_PkID, L.LgID, L.LieferDatum FROM Rechnungen R INNER JOIN "
                                        "Bestellungen B ON R.R_BID=B.BID INNER JOIN Lieferungen L ON "
                                        "L.Lg_BID=B.BID WHERE R.RID=";
static QString getRechnungsAnschrift=   "SELECT PK.Anrede, PK.Vorname, PK.Nachname, PK.Gebaeude, PK.Zimmer, SO.PLZ, "
                                        "SO.Stadt, SO.Strasse_HNr, SO.Postfach, FK.Firmenname, SO.KontoNr, SO.BLZ FROM Personenkunden PK "
                                        "INNER JOIN Standorte SO ON PK.Pk_SoID=SO.SoID "
                                        "INNER JOIN Firmenkunden FK ON SO.So_FkID=FK.FkID WHERE PK.PkID=";
static QString getRechnungsPositionen=  "SELECT BP.BPosition, BP.BpAnzahl, AP.Rabatt, AP.Tagespreis, P.PrName, P.Version "
                                        "FROM BestellungsPositionen BP INNER JOIN AngebotsPositionen AP "
                                        "ON BP.Bp_AID=AP.Ap_AID AND BP.Bp_ApID=AP.APosition INNER JOIN Produkte P "
                                        "ON AP.Ap_PrID=P.PrID WHERE BP.Bp_BID=";

static QString getHistorie=             "select H.HID, Z.Vertragstyp, H.Rechnungs_Nr, H.Rechnungsdatum, H.Rechnungsbetrag, H.Status, H.Bezahlt_Von, "
                                        "H.Bezahlt_Bis from Historie H "
                                        "inner join Zeitvertraege Z on H.H_ZvID=Z.ZvID where H_ZvID=";

#endif // STATEMENTS_H
