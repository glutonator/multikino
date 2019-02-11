#ifndef SPRZEDAZ_H
#define SPRZEDAZ_H
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QDate>
#include <memory>
#include "sala_kinowa.h"
#include <vector>
#include "baza_danych.h"
#include "seans_miejsce.h"
#include "lista_seans_miejsce.h"
#include "klient.h"
#include "seans.h"


class Sprzedaz
{
public:
    Sprzedaz();
    bool create_klient(int id);
    bool select (int id);
    void setLista_seans_miejsce(std::shared_ptr<Lista_seans_miejsce> ptr);
    std::shared_ptr<Lista_seans_miejsce> getLista_seans_miejsce();
    bool dodanie_do_bazy();
    QString getRodzaj_znizki();
    int getId();
private:
    int IdKlient;
    std::vector<int> IdSeans_miejsce;
    int IdSprzedaz;
    int nr_sprzed;
    int wartosc;
    QDate data;
    std::shared_ptr<Lista_seans_miejsce> lista_seans_miejsce;
    std::shared_ptr<Klient> klient;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // SPRZEDAZ_H
