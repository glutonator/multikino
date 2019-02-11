#include "baza_danych.h"

Baza_danych::Baza_danych()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("serwer1769423.home.pl");
    db.setDatabaseName("22865034_kino");
    db.setUserName("22865034_kino");
    db.setPassword("Password1");
    db.open();
}

Baza_danych Baza_danych::getInstance(){
    static Baza_danych instance;
    return instance;
}

const QSqlDatabase& Baza_danych::getDb() const{
    return db;
}

void Baza_danych::close(){
    db.close();
}
