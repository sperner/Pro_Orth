SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `Pro_Orth` ;
CREATE SCHEMA IF NOT EXISTS `Pro_Orth` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci ;

-- -----------------------------------------------------
-- Table `Pro_Orth`.`Firmenkunden`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Firmenkunden` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Firmenkunden` (
  `FkID` INT NOT NULL AUTO_INCREMENT ,
  `Firmenname` VARCHAR(45) NOT NULL ,
  `Homepage` VARCHAR(45) NULL ,
  `Branche` VARCHAR(45) NULL ,
  PRIMARY KEY (`FkID`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Standorte`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Standorte` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Standorte` (
  `SoID` INT NOT NULL ,
  `So_FkID` INT NOT NULL ,
  `Standorttyp` ENUM('Zentrale', 'Filiale') NOT NULL ,
  `PLZ` DECIMAL(5) NOT NULL ,
  `Stadt` VARCHAR(45) NOT NULL ,
  `Strasse_HNr` VARCHAR(45) NULL ,
  `Postfach` VARCHAR(45) NULL ,
  `Land` VARCHAR(45) NULL ,
  `KontoNr` VARCHAR(45) NULL ,
  `BLZ` VARCHAR(45) NULL ,
  PRIMARY KEY (`SoID`) ,
  INDEX `fk_Standort_Firmenkunden` (`So_FkID` ASC) ,
  CONSTRAINT `fk_Standort_Firmenkunden`
    FOREIGN KEY (`So_FkID` )
    REFERENCES `Pro_Orth`.`Firmenkunden` (`FkID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Personenkunden`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Personenkunden` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Personenkunden` (
  `PkID` INT NOT NULL AUTO_INCREMENT ,
  `Pk_SoID` INT NULL ,
  `Anrede` ENUM('Herr','Frau') NOT NULL ,
  `Vorname` VARCHAR(45) NOT NULL ,
  `Nachname` VARCHAR(45) NOT NULL ,
  `Position` VARCHAR(45) NOT NULL ,
  `Abteilung` VARCHAR(45) NOT NULL ,
  `Gebaeude` VARCHAR(45) NULL ,
  `Zimmer` VARCHAR(45) NULL ,
  `Telefon` VARCHAR(45) NULL ,
  `Fax` VARCHAR(45) NULL ,
  `Email` VARCHAR(45) NULL ,
  PRIMARY KEY (`PkID`) ,
  INDEX `fk_Personenkunden_Standorte1` (`Pk_SoID` ASC) ,
  CONSTRAINT `fk_Personenkunden_Standorte1`
    FOREIGN KEY (`Pk_SoID` )
    REFERENCES `Pro_Orth`.`Standorte` (`SoID` )
    ON DELETE SET NULL
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Bestellungen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Bestellungen` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Bestellungen` (
  `BID` INT NOT NULL AUTO_INCREMENT COMMENT '	' ,
  `BestellDatum` DATE NOT NULL ,
  `B_PkID` INT NOT NULL ,
  PRIMARY KEY (`BID`) ,
  INDEX `fk_Bestellungen_Personenkunden1` (`B_PkID` ASC) ,
  CONSTRAINT `fk_Bestellungen_Personenkunden1`
    FOREIGN KEY (`B_PkID` )
    REFERENCES `Pro_Orth`.`Personenkunden` (`PkID` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Angebote`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Angebote` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Angebote` (
  `AID` INT NOT NULL AUTO_INCREMENT ,
  `A_SoID` INT NOT NULL ,
  `AngDatum` DATE NOT NULL ,
  `Gueltigkeit` DATE NOT NULL ,
  `Firmenrabatt` FLOAT NOT NULL DEFAULT 0 ,
  PRIMARY KEY (`AID`) ,
  INDEX `fk_Angebote_Standort1` (`A_SoID` ASC) ,
  CONSTRAINT `fk_Angebote_Standort1`
    FOREIGN KEY (`A_SoID` )
    REFERENCES `Pro_Orth`.`Standorte` (`SoID` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Produkte`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Produkte` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Produkte` (
  `PrID` INT NOT NULL ,
  `PrName` VARCHAR(45) NOT NULL ,
  `Version` VARCHAR(45) NOT NULL ,
  `Preis` FLOAT NOT NULL ,
  `Anforderung` VARCHAR(45) NULL ,
  PRIMARY KEY (`PrID`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`AngebotsPositionen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`AngebotsPositionen` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`AngebotsPositionen` (
  `Ap_AID` INT NOT NULL ,
  `APosition` INT NOT NULL ,
  `Ap_PrID` INT NOT NULL ,
  `ApAnzahl` INT NOT NULL ,
  `Rabatt` FLOAT NOT NULL DEFAULT 0 ,
  `Tagespreis` FLOAT NOT NULL ,
  PRIMARY KEY (`APosition`, `Ap_AID`) ,
  INDEX `fk_Angebots_Positionen_Angebote1` (`Ap_AID` ASC) ,
  INDEX `fk_Angebots_Positionen_Produkte1` (`Ap_PrID` ASC) ,
  CONSTRAINT `fk_Angebots_Positionen_Angebote1`
    FOREIGN KEY (`Ap_AID` )
    REFERENCES `Pro_Orth`.`Angebote` (`AID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Angebots_Positionen_Produkte1`
    FOREIGN KEY (`Ap_PrID` )
    REFERENCES `Pro_Orth`.`Produkte` (`PrID` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`BestellungsPositionen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`BestellungsPositionen` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`BestellungsPositionen` (
  `Bp_BID` INT NOT NULL ,
  `BPosition` INT NOT NULL ,
  `Bp_AID` INT NOT NULL ,
  `Bp_ApID` INT NOT NULL ,
  `BpAnzahl` INT NOT NULL ,
  PRIMARY KEY (`BPosition`, `Bp_BID`) ,
  INDEX `fk_Bestellungs_Position_Bestellungen1` (`Bp_BID` ASC) ,
  INDEX `fk_Bestellungs_Position_Angebots_Positionen1` (`Bp_ApID` ASC) ,
  INDEX `fk_Bestellungs_Position_Angebote1` (`Bp_AID` ASC) ,
  CONSTRAINT `fk_Bestellungs_Position_Bestellungen1`
    FOREIGN KEY (`Bp_BID` )
    REFERENCES `Pro_Orth`.`Bestellungen` (`BID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Bestellungs_Position_Angebots_Positionen1`
    FOREIGN KEY (`Bp_ApID` )
    REFERENCES `Pro_Orth`.`AngebotsPositionen` (`APosition` )
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_Bestellungs_Position_Angebote1`
    FOREIGN KEY (`Bp_AID` )
    REFERENCES `Pro_Orth`.`Angebote` (`AID` )
    ON DELETE NO ACTION
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Lizenzen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Lizenzen` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Lizenzen` (
  `LzID` INT NOT NULL ,
  `Lz_PrID` INT NULL ,
  `Lz_PkId` INT NOT NULL ,
  `Schluessel` VARCHAR(45) NOT NULL ,
  `Information` VARCHAR(45) NULL ,
  `Verkaufsdatum` DATE NOT NULL ,
  `Ablaufsdatum` DATE NOT NULL ,
  `Upgrade` ENUM('J','N') NOT NULL ,
  `Lizenztyp` VARCHAR(45) NULL ,
  `Rabatt` FLOAT NOT NULL DEFAULT 0 ,
  PRIMARY KEY (`LzID`) ,
  INDEX `fk_Lizenzen_Produkte1` (`Lz_PrID` ASC) ,
  INDEX `fk_Lizenzen_Personenkunden1` (`Lz_PkId` ASC) ,
  CONSTRAINT `fk_Lizenzen_Produkte1`
    FOREIGN KEY (`Lz_PrID` )
    REFERENCES `Pro_Orth`.`Produkte` (`PrID` )
    ON DELETE SET NULL
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Lizenzen_Personenkunden1`
    FOREIGN KEY (`Lz_PkId` )
    REFERENCES `Pro_Orth`.`Personenkunden` (`PkID` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Rechnungen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Rechnungen` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Rechnungen` (
  `RID` INT NOT NULL ,
  `RDatum` DATE NOT NULL ,
  `Faelligkeit` DATE NOT NULL ,
  `MwSt` FLOAT NOT NULL ,
  `R_BID` INT NOT NULL ,
  `Zahlungsart` ENUM('Rechnung','Bankeinzug') NOT NULL ,
  PRIMARY KEY (`RID`) ,
  INDEX `fk_Rechnungen_Bestellungen1` (`R_BID` ASC) ,
  CONSTRAINT `fk_Rechnungen_Bestellungen1`
    FOREIGN KEY (`R_BID` )
    REFERENCES `Pro_Orth`.`Bestellungen` (`BID` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Lieferungen`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Lieferungen` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Lieferungen` (
  `LgID` INT NOT NULL ,
  `LieferDatum` DATE NOT NULL ,
  `Lg_BID` INT NOT NULL ,
  `TrackingNr` VARCHAR(45) NULL ,
  PRIMARY KEY (`LgID`) ,
  INDEX `fk_Lieferungen_Bestellungen1` (`Lg_BID` ASC) ,
  CONSTRAINT `fk_Lieferungen_Bestellungen1`
    FOREIGN KEY (`Lg_BID` )
    REFERENCES `Pro_Orth`.`Bestellungen` (`BID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Zeitvertraege`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Zeitvertraege` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Zeitvertraege` (
  `ZvID` INT NOT NULL ,
  `Zv_LzID` INT NOT NULL ,
  `Vertragstyp` ENUM('Leasing','Maintenance') NULL ,
  `Vertragsbeginn` DATE NOT NULL COMMENT '	' ,
  `Vertragsende` DATE NOT NULL ,
  `Monatsbetrag` FLOAT NOT NULL ,
  `Zahlungsart` ENUM('Bankeinzug','Rechnung') NOT NULL ,
  `BezahltBis` DATE NOT NULL ,
  PRIMARY KEY (`ZvID`) ,
  INDEX `fk_Maintenance_Lizenzen1` (`Zv_LzID` ASC) ,
  CONSTRAINT `fk_Maintenance_Lizenzen1`
    FOREIGN KEY (`Zv_LzID` )
    REFERENCES `Pro_Orth`.`Lizenzen` (`LzID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Historie`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Historie` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Historie` (
  `HID` INT NOT NULL ,
  `H_ZvID` INT NOT NULL ,
  `Rechnungs_Nr` INT NOT NULL ,
  `Rechnungsdatum` DATE NOT NULL ,
  `Rechnungsbetrag` FLOAT NOT NULL ,
  `Status` ENUM('Bezahlt','Offen') NOT NULL ,
  `Bezahlt_Von` DATE NOT NULL ,
  `Bezahlt_Bis` DATE NOT NULL ,
  PRIMARY KEY (`HID`) ,
  INDEX `fk_Maintenance_Historie_Maintenance1` (`H_ZvID` ASC) ,
  CONSTRAINT `fk_Maintenance_Historie_Maintenance1`
    FOREIGN KEY (`H_ZvID` )
    REFERENCES `Pro_Orth`.`Zeitvertraege` (`ZvID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `Pro_Orth`.`Lizenzpool`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `Pro_Orth`.`Lizenzpool` ;

CREATE  TABLE IF NOT EXISTS `Pro_Orth`.`Lizenzpool` (
  `LzpID` INT NOT NULL ,
  `Lzp_PrtID` INT NOT NULL ,
  `Schluessel` VARCHAR(45) NOT NULL ,
  PRIMARY KEY (`LzpID`, `Lzp_PrtID`) ,
  INDEX `fk_Lizenzpool_Produkte1` (`Lzp_PrtID` ASC) ,
  CONSTRAINT `fk_Lizenzpool_Produkte1`
    FOREIGN KEY (`Lzp_PrtID` )
    REFERENCES `Pro_Orth`.`Produkte` (`PrID` )
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Firmenkunden`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'Müller GmbH', 'www.mueller-gmbh.de', 'IT');
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'Abraham Dürninger + Co. GmbH', 'www.duerninger.com', 'Weberei');
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'ADAC Service GmbH', 'www.adac.de', 'Automobil');
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'AREVA NP GmbH', 'www.areva-np.com', 'Ingenieurbüros für technische Fachplanung');
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'cleverbridge AG', 'www.cleverbridge.com', 'Werbung und Marketing');
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'Euroglas AG', 'www.euroglas.com', 'Herstellung von Flachglas');
INSERT INTO `Pro_Orth`.`Firmenkunden` (`FkID`, `Firmenname`, `Homepage`, `Branche`) VALUES (NULL, 'Klaus Musterbuch GmbH', NULL, 'Herstellung von Tapeten');

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Standorte`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (1, 1, 'Zentrale', 65597, 'Hünfelden', 'Amselweg 10', NULL, NULL, '12342125', '41140019');
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (2, 2, 'Zentrale', 27475, 'Herrnhut', 'OderwitzerStrasse 12', NULL, 'Deutschland', NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (3, 3, 'Zentrale', 81373, 'München', 'Am Westpark 8', NULL, NULL, NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (4, 4, 'Zentrale', 91058, 'Erlangen', 'Freyeslebenstrasse 1', NULL, 'Deutschland', NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (5, 5, 'Zentrale', 50931, 'Köln', 'Aachener Strasse 209', NULL, 'Deutschland', NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (6, 6, 'Zentrale', 39171, 'Osterweddingen', 'Euroglas Strasse 101', NULL, 'Deutschland', NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (7, 7, 'Zentrale', 30900, 'Wedemark', 'Schaumburger Strasse 11', NULL, NULL, NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (8, 2, 'Filiale', 65597, 'Hünfelden', NULL, NULL, NULL, NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (9, 4, 'Filiale', 30900, 'Wedemark', NULL, 'Postfach 130', NULL, NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (10, 4, 'Filiale', 81373, 'München', 'Am Stadion 1', NULL, NULL, NULL, NULL);
INSERT INTO `Pro_Orth`.`Standorte` (`SoID`, `So_FkID`, `Standorttyp`, `PLZ`, `Stadt`, `Strasse_HNr`, `Postfach`, `Land`, `KontoNr`, `BLZ`) VALUES (11, 7, 'Filiale', 50931, 'Köln', 'Am Bahnhof 2', NULL, 'Deutschland', NULL, NULL);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Personenkunden`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Personenkunden` (`PkID`, `Pk_SoID`, `Anrede`, `Vorname`, `Nachname`, `Position`, `Abteilung`, `Gebaeude`, `Zimmer`, `Telefon`, `Fax`, `Email`) VALUES (1, 1, 'Herr', 'Hans', 'Müller', 'Geschäftsführer', 'Geschäftsführung', '1', '230', '0111/325245', '0111/325244', NULL);
INSERT INTO `Pro_Orth`.`Personenkunden` (`PkID`, `Pk_SoID`, `Anrede`, `Vorname`, `Nachname`, `Position`, `Abteilung`, `Gebaeude`, `Zimmer`, `Telefon`, `Fax`, `Email`) VALUES (2, 1, 'Frau', 'Angela', 'Müller', 'Sekretärin', 'Verwaltung', '1', '215', '0111/125903', '0111/390649', NULL);
INSERT INTO `Pro_Orth`.`Personenkunden` (`PkID`, `Pk_SoID`, `Anrede`, `Vorname`, `Nachname`, `Position`, `Abteilung`, `Gebaeude`, `Zimmer`, `Telefon`, `Fax`, `Email`) VALUES (3, 2, 'Herr', 'Peter', 'Schmidt', 'Geschäftsführer', 'Geschäftsführung', NULL, NULL, NULL, NULL, NULL);
INSERT INTO `Pro_Orth`.`Personenkunden` (`PkID`, `Pk_SoID`, `Anrede`, `Vorname`, `Nachname`, `Position`, `Abteilung`, `Gebaeude`, `Zimmer`, `Telefon`, `Fax`, `Email`) VALUES (4, 3, 'Herr', 'Jan', 'Peters', 'Angestellter', 'IT', '3', '001', '04523/345214', '04523/345214', NULL);
INSERT INTO `Pro_Orth`.`Personenkunden` (`PkID`, `Pk_SoID`, `Anrede`, `Vorname`, `Nachname`, `Position`, `Abteilung`, `Gebaeude`, `Zimmer`, `Telefon`, `Fax`, `Email`) VALUES (5, 3, 'Frau', 'Ulla', 'Schmidt', 'Sekretärin', 'Verwaltung', '3', '010', '04523/345210', NULL, NULL);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Bestellungen`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Bestellungen` (`BID`, `BestellDatum`, `B_PkID`) VALUES (1, '2010-04-30', 3);
INSERT INTO `Pro_Orth`.`Bestellungen` (`BID`, `BestellDatum`, `B_PkID`) VALUES (2, '2010-05-23', 5);
INSERT INTO `Pro_Orth`.`Bestellungen` (`BID`, `BestellDatum`, `B_PkID`) VALUES (3, '2010-05-24', 4);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Angebote`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Angebote` (`AID`, `A_SoID`, `AngDatum`, `Gueltigkeit`, `Firmenrabatt`) VALUES (1, 3, '2010-03-20', '2010-05-20', 0);
INSERT INTO `Pro_Orth`.`Angebote` (`AID`, `A_SoID`, `AngDatum`, `Gueltigkeit`, `Firmenrabatt`) VALUES (2, 2, '2010-04-18', '2010-07-18', 5);
INSERT INTO `Pro_Orth`.`Angebote` (`AID`, `A_SoID`, `AngDatum`, `Gueltigkeit`, `Firmenrabatt`) VALUES (3, 5, '2010-05-07', '2010-08-07', 3);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Produkte`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Produkte` (`PrID`, `PrName`, `Version`, `Preis`, `Anforderung`) VALUES (1, 'Windows XP', 'SP2', 120.5, '1 GHZ CPU, 512 MB RAM');
INSERT INTO `Pro_Orth`.`Produkte` (`PrID`, `PrName`, `Version`, `Preis`, `Anforderung`) VALUES (2, 'Mac OS X', '10.6.3', 90, '1 GHZ CPU');
INSERT INTO `Pro_Orth`.`Produkte` (`PrID`, `PrName`, `Version`, `Preis`, `Anforderung`) VALUES (3, 'Microsoft Office Home& Student', '2003', 78, 'Windows');
INSERT INTO `Pro_Orth`.`Produkte` (`PrID`, `PrName`, `Version`, `Preis`, `Anforderung`) VALUES (4, 'Microsoft Office Home & Student', '2008', 78, 'Mac');

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`AngebotsPositionen`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`AngebotsPositionen` (`Ap_AID`, `APosition`, `Ap_PrID`, `ApAnzahl`, `Rabatt`, `Tagespreis`) VALUES (1, 1, 1, 2, 5, 120.5);
INSERT INTO `Pro_Orth`.`AngebotsPositionen` (`Ap_AID`, `APosition`, `Ap_PrID`, `ApAnzahl`, `Rabatt`, `Tagespreis`) VALUES (1, 2, 3, 1, 1.5, 70);
INSERT INTO `Pro_Orth`.`AngebotsPositionen` (`Ap_AID`, `APosition`, `Ap_PrID`, `ApAnzahl`, `Rabatt`, `Tagespreis`) VALUES (1, 3, 2, 0, 2, 80);
INSERT INTO `Pro_Orth`.`AngebotsPositionen` (`Ap_AID`, `APosition`, `Ap_PrID`, `ApAnzahl`, `Rabatt`, `Tagespreis`) VALUES (2, 1, 2, 4, 10, 90);
INSERT INTO `Pro_Orth`.`AngebotsPositionen` (`Ap_AID`, `APosition`, `Ap_PrID`, `ApAnzahl`, `Rabatt`, `Tagespreis`) VALUES (2, 2, 3, 2, 1, 78);
INSERT INTO `Pro_Orth`.`AngebotsPositionen` (`Ap_AID`, `APosition`, `Ap_PrID`, `ApAnzahl`, `Rabatt`, `Tagespreis`) VALUES (3, 1, 1, 5, 12, 95);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`BestellungsPositionen`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`BestellungsPositionen` (`Bp_BID`, `BPosition`, `Bp_AID`, `Bp_ApID`, `BpAnzahl`) VALUES (1, 1, 2, 1, 3);
INSERT INTO `Pro_Orth`.`BestellungsPositionen` (`Bp_BID`, `BPosition`, `Bp_AID`, `Bp_ApID`, `BpAnzahl`) VALUES (1, 2, 2, 2, 2);
INSERT INTO `Pro_Orth`.`BestellungsPositionen` (`Bp_BID`, `BPosition`, `Bp_AID`, `Bp_ApID`, `BpAnzahl`) VALUES (2, 1, 1, 1, 2);
INSERT INTO `Pro_Orth`.`BestellungsPositionen` (`Bp_BID`, `BPosition`, `Bp_AID`, `Bp_ApID`, `BpAnzahl`) VALUES (3, 1, 1, 2, 1);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Lizenzen`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (1, 2, 3, 'jwohi-isdho-ahsie-sdiwp-spofh', '1 Platz Lizenz', '2010-04-30', '2013-04-30', 'ja', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (2, 2, 3, 'dwbfs-asife-sdpiw-sohwp-asdub', '1 Platz Lizenz', '2010-04-30', '2010-04-30', 'ja', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (3, 2, 3, 'dksiw-iwoh3-asdih-aadwi-wqpqp', '1 Platz Lizenz', '2010-04-30', '2013-04-30', 'ja', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (4, 3, 3, 'asdkln-aksdnd', NULL, '2010-04-30', '2015-04-30', 'nein', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (5, 3, 3, 'sadnpw-s93ndd', NULL, '2010-05-12', '2015-05-12', 'nein', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (6, 1, 5, 'klnld-awinf-jdwoe-nfkwe-dekew', '2 Platz Lizenz', '2010-05-23', '2015-05-23', 'ja', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (7, 1, 5, 'shqi4-djwle-eu239r-dkjr4-dkj2h4', '2 Platz Lizenz', '2010-05-23', '2015-05-23', 'ja', NULL, 0);
INSERT INTO `Pro_Orth`.`Lizenzen` (`LzID`, `Lz_PrID`, `Lz_PkId`, `Schluessel`, `Information`, `Verkaufsdatum`, `Ablaufsdatum`, `Upgrade`, `Lizenztyp`, `Rabatt`) VALUES (8, 3, 4, 'aslkdn-alksdn', NULL, '2010-05-24', '2020-05-24', 'ja', NULL, 0);

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Rechnungen`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Rechnungen` (`RID`, `RDatum`, `Faelligkeit`, `MwSt`, `R_BID`, `Zahlungsart`) VALUES (1, '2010-05-06', '2010-05-20', 19, 1, 'Bankeinzug');
INSERT INTO `Pro_Orth`.`Rechnungen` (`RID`, `RDatum`, `Faelligkeit`, `MwSt`, `R_BID`, `Zahlungsart`) VALUES (2, '2010-05-24', '2010-06-08', 19, 2, 'Rechnung');
INSERT INTO `Pro_Orth`.`Rechnungen` (`RID`, `RDatum`, `Faelligkeit`, `MwSt`, `R_BID`, `Zahlungsart`) VALUES (3, '2010-05-25', '2010-06-09', 19, 3, 'Nachname');

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Lieferungen`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Lieferungen` (`LgID`, `LieferDatum`, `Lg_BID`, `TrackingNr`) VALUES (1, '2010-05-07', 1, '2940394930');
INSERT INTO `Pro_Orth`.`Lieferungen` (`LgID`, `LieferDatum`, `Lg_BID`, `TrackingNr`) VALUES (2, '2010-05-25', 2, '3905949304');
INSERT INTO `Pro_Orth`.`Lieferungen` (`LgID`, `LieferDatum`, `Lg_BID`, `TrackingNr`) VALUES (3, '2010-05-26', 3, '9039503940');

COMMIT;

-- -----------------------------------------------------
-- Data for table `Pro_Orth`.`Lizenzpool`
-- -----------------------------------------------------
SET AUTOCOMMIT=0;
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (1, 1, 'asdkn-laskd-qpwof-awnrq-asfng');
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (2, 1, 'sawop-qwfn-aqwof-asfon-asüjq');
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (3, 1, 'asdjw-qwopd-woowd-sooqp-nvbdj');
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (4, 2, 'nospa-aowjq-püfpo-asnwp-nsklw');
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (5, 2, 'sdwoin-1niow-2npais-niwon-owpqo');
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (6, 3, 'alskndipe2ß');
INSERT INTO `Pro_Orth`.`Lizenzpool` (`LzpID`, `Lzp_PrtID`, `Schluessel`) VALUES (7, 3, 'asnwpqüsd24');

COMMIT;
