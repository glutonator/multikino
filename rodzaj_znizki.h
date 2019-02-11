#ifndef RODZAJ_ZNIZKI_H
#define RODZAJ_ZNIZKI_H

#include <vector>
#include<memory>
#include <QString>
#include "czas_znizki.h"
#include "baza_danych.h"

class Rodzaj_znizki
{
public:
    Rodzaj_znizki(int id);
//    std::vector<std::shared_ptr<Czas_znizki>>& getCzas_znizki();
    QString getRodzaj_znizki();
private:
    void select(int id);
    std::vector<int> idCzas_znizki;
    int IdRodzaj_znizki;
    QString nazwa;
    int procent_znizki;
    std::vector<std::shared_ptr<Czas_znizki>> czas_znizki;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // RODZAJ_ZNIZKI_H
