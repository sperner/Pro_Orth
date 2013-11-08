# -------------------------------------------------
# Project created by QtCreator 2010-05-15T13:04:26
# -------------------------------------------------
QT += sql
TARGET = Pro_Orth
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    connection.cpp \
    about.cpp \
    settings.cpp \
    dbop_firmenkunde.cpp \
    dbop_standort.cpp \
    dbop_personenkunde.cpp \
    dbop_produkt.cpp \
    dbop_lizenz.cpp \
    dbop_zeitvertrag.cpp \
    dbop_angebot.cpp \
    dbop_bestellung.cpp \
    dbop_lieferung.cpp \
    dbop_rechnung.cpp \
    db_printer.cpp \
    dbop_historie.cpp
HEADERS += mainwindow.h \
    connection.h \
    about.h \
    settings.h \
    statements.h \
    dbop_firmenkunde.h \
    dbop_standort.h \
    dbop_personenkunde.h \
    dbop_produkt.h \
    dbop_lizenz.h \
    dbop_zeitvertrag.h \
    dbop_angebot.h \
    dbop_bestellung.h \
    dbop_lieferung.h \
    dbop_rechnung.h \
    db_printer.h \
    dbop_historie.h
FORMS += mainwindow.ui \
    about.ui \
    settings.ui \
    dbop_firmenkunde.ui \
    dbop_standort.ui \
    dbop_personenkunde.ui \
    dbop_produkt.ui \
    dbop_lizenz.ui \
    dbop_zeitvertrag.ui \
    dbop_angebot.ui \
    dbop_bestellung.ui \
    dbop_lieferung.ui \
    dbop_rechnung.ui \
    dbop_historie.ui
RESOURCES += ressourcen.qrc
OTHER_FILES += 
