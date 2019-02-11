#ifndef SEANS_MIEJSCE_H
#define SEANS_MIEJSCE_H

#include <QString>
#include <memory>
#include "seans.h"
#include "miejsce.h"
#include "baza_danych.h"

class Seans_miejsce
{
public:
    Seans_miejsce();
    void select(int id);
    void setSeans(std::shared_ptr<Seans> ptr);
    void setMiejsce(std::shared_ptr<Miejsce> ptr);
    int getRzad();
    int getWiersz();
    bool getZajete();
    float getCena();
    int getIdSeans_miejsce();
    QString getRodzaj_biletu();
    int getIdSala();
    int getIdMiejsce();
    void wyswietl();
    int getIdSeans();
    std::shared_ptr<Seans> getSeans();
    void setRodzaj_biletu(QString rodzaj);
private:
    int IdRodzaj_biletu;
    int IdMiejsce;
    int IdSeans_miejsce;
    int IdSeans;
    QString rodzaj_biletu;
    int procent_znizki;
    bool zajete;
    std::shared_ptr<Seans> seans;
    std::shared_ptr<Miejsce> miejsce;
    std::shared_ptr<const Baza_danych> db_ptr;
};

#endif // SEANS_MIEJSCE_H
