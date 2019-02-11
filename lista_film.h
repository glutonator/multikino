#ifndef LISTA_FILM_H
#define LISTA_FILM_H

#include "film.h"
#include <QDate>
#include <vector>
#include "baza_danych.h"

class Lista_film
{
public:
    Lista_film();
    void select(QDate data);
    std::vector<std::shared_ptr<Film>>& getLista_film();
    std::shared_ptr<Film> find (QString tytul);
private:
    std::shared_ptr<const Baza_danych> db_ptr;
    std::vector<std::shared_ptr<Film>> lista;
};

#endif // LISTA_FILM_H
