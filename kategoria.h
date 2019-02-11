#ifndef KATEGORIA_H
#define KATEGORIA_H

#include <QString>
#include <memory>
#include "baza_danych.h"

class Kategoria
{
public:
    Kategoria();
    void wyswietl();
private:
    float cena_bazowa;
    int IdKategoria;
    QString nazwa;
    std::shared_ptr<const Baza_danych> db_ptr;
public:
    void select(int id);
    float getCena();
};

#endif // KATEGORIA_H
