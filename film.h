#ifndef FILM_H
#define FILM_H

#include <QString>
#include <memory>
#include "kategoria.h"
#include "baza_danych.h"

class Film
{
public:
    Film();
    void wyswietl();
    void select(int id);
    QString& getTytul();
    float getCena();
    int getId();
private:
    int czas_trwania;
    int IdFilm;
    int IdKategoria;
    QString tytul;
    std::shared_ptr<Kategoria> kategoria;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // FILM_H
