#ifndef SEANS_H
#define SEANS_H

#include <memory>
#include <QDate>
#include <QTime>
#include "wersja_filmu.h"
#include "baza_danych.h"

class Seans
{
public:
    Seans();
    void select(int id);
    void wyswietl();
    void setWersja_filmu(std::shared_ptr<Wersja_filmu> ptr);
    int& getId();
    QDate& getData();
    QTime& getGodz();
    float getCena();
    int getIdWersja_filmu();
    std::shared_ptr<Wersja_filmu> getWersja_filmu();
private:
    QDate data;
    QTime godz_rozpocz;
    int IdSeans;
    int IdSlot_czasowy;
    int IdWerjsa_filmu;
    std::shared_ptr<Wersja_filmu> wersja_filmu;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // SEANS_H
