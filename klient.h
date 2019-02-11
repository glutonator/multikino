#ifndef KLIENT_H
#define KLIENT_H

#include <QString>
#include <memory>
#include "rodzaj_znizki.h"
#include "baza_danych.h"

class Klient
{
public:
    Klient(int id);
    QString getRodzaj_znizki();
private:
    void select(int id);
    int IdKlient;
    int IdRodzaj_znizki;
    QString imie;
    QString mail;
    QString nazwisko;
    QString numer_karty_lojaln;
    std::shared_ptr<Rodzaj_znizki> rodzaj_znizki;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // KLIENT_H
