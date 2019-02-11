#ifndef WERSJA_FILMU_H
#define WERSJA_FILMU_H

#include <QString>
#include <memory>
#include "film.h"
#include "baza_danych.h"

class Wersja_filmu
{
public:
    Wersja_filmu();
    void select(int id);
    void wyswietl();
    void setFilm(std::shared_ptr<Film> ptr);
    QString getWersja();
    float getCena();
    int& getId();
    int getIdFilm();
    std::shared_ptr<Film> getFilm();
private:
    int IdFilm;
    int IdWersja_filmu;
    QString tech;
    QString wersja;
    std::shared_ptr<Film> film;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // WERSJA_FILMU_H
