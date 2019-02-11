#ifndef LISTA_WERSJA_FILMU_H
#define LISTA_WERSJA_FILMU_H

#include "wersja_filmu.h"
#include <vector>
#include "baza_danych.h"

class Lista_wersja_filmu
{
public:
    Lista_wersja_filmu();
    void select(std::shared_ptr<Film> ptr);
    std::vector<std::shared_ptr<Wersja_filmu>>& getLista_wersja_filmu();
    std::shared_ptr<Wersja_filmu> find (QString wersja);
private:
    std::shared_ptr<const Baza_danych> db_ptr;
    std::vector<std::shared_ptr<Wersja_filmu>> lista;
};

#endif // LISTA_WERSJA_FILMU_H
