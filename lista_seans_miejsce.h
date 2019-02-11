#ifndef LISTA_SEANS_MIEJSCE_H
#define LISTA_SEANS_MIEJSCE_H

#include "seans_miejsce.h"
#include "seans.h"
#include <vector>
#include "baza_danych.h"
#include "kino.h"
#include <QDate>
#include <memory>

class Lista_seans_miejsce
{
public:
    Lista_seans_miejsce();
    void select(std::shared_ptr<Seans> ptr);
    std::vector<std::shared_ptr<Seans_miejsce>>& getLista();
    int getMax_rzad();
    int getMax_wiersz();
    void addSeans_miejsce(std::shared_ptr<Seans_miejsce> ptr);
    void removeSeans_miejsce(std::shared_ptr<Seans_miejsce> ptr);
    std::shared_ptr<Seans_miejsce> find(int id_sm);
    void wyswietl();
//    std::shared_ptr<Seans> find(int rzad, int wiersz);
private:
    std::shared_ptr<const Baza_danych> db_ptr;
    std::shared_ptr<Kino> kino_ptr;
    std::vector<std::shared_ptr<Seans_miejsce>> lista;
    int max_rzad;
    int max_wiersz;
};

#endif // LISTA_SEANS_MIEJSCE_H
