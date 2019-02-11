#ifndef REZERWACJA_H
#define REZERWACJA_H
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QDate>
#include <memory>
#include "sala_kinowa.h"
#include <vector>
#include "baza_danych.h"
#include "seans_miejsce.h"
#include "klient.h"
#include "lista_seans_miejsce.h"
#include "seans.h"


class Rezerwacja
{
public:
    Rezerwacja();
    bool select (int id);
    bool create_klient(int id);
    int dodanie_do_bazy();
    void setLista_seans_miejsce(std::shared_ptr<Lista_seans_miejsce> ptr);
    std::shared_ptr<Lista_seans_miejsce> getLista_seans_miejsce();
    QString getRodzaj_znizki();

private:
    int IdKlient;
    std::vector<int> IdSeans_miejsce;
    int IdRezerwacja;
    int nr_rezerw;
    QDate data;
    std::shared_ptr<Lista_seans_miejsce> lista_seans_miejsce;
    std::shared_ptr<Klient> klient;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // REZERWACJA_H
