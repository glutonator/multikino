#ifndef CZAS_ZNIZKI_H
#define CZAS_ZNIZKI_H

#include <QString>
#include <QTime>
#include "baza_danych.h"
#include <memory>


class Czas_znizki
{
public:
    Czas_znizki(int id);
private:
    void select(int id);
    QString dzien;
    QTime godz_rozpocz;
    QTime godz_zakoncz;
    int IdCzas_znizki;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // CZAS_ZNIZKI_H
