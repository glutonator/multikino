#ifndef LISTA_SEANS_H
#define LISTA_SEANS_H

#include "seans.h"
#include <vector>
#include "baza_danych.h"
#include <QDate>
#include <map>
#include <memory>

class Lista_seans
{
public:
    Lista_seans();
    void select(std::shared_ptr<Wersja_filmu> ptr);
    std::vector<QDate> getLista_data();
    std::vector<std::shared_ptr<Seans>>& getLista_seans(const QDate& data_val);
    std::shared_ptr<Seans> find(QDate data, QTime godz);
private:
    std::shared_ptr<const Baza_danych> db_ptr;
    std::map<QDate, std::vector<std::shared_ptr<Seans>>> lista;
//    std::vector<std::shared_ptr<Seans>> lista;
};

#endif // LISTA_SEANS_H
