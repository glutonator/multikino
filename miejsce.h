#ifndef MIEJSCE_H
#define MIEJSCE_H
#include <memory>
#include "baza_danych.h"
#include <QDebug>
#include <QString>

class Miejsce
{
public:
    Miejsce(int Id);
    void wyswietl();
    int& getId();
    int getWiersz();
    int getRzad();
    int getIdSala_kinowa();
private:
    std::shared_ptr<const Baza_danych> db_ptr;
    int IdMiejsce;
    int IdSala_kinowa;
    int rzad;
    int wiersz;
};

#endif // MIEJSCE_H
