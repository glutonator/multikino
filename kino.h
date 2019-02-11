#ifndef KINO_H
#define KINO_H
#include <QDebug>
#include <QString>
#include <memory>
#include "sala_kinowa.h"
#include "miejsce.h"
#include "baza_danych.h"
#include <map>

class Kino
{
public:
    static Kino getInstance();
    std::shared_ptr<Sala_kinowa> find_sala(int id);
    std::shared_ptr<Miejsce> find_miejsce(int id);
    void wyswietl();
private:
    Kino(int Id);
    int IdKino;
    QString Nazwa;
    std::shared_ptr<const Baza_danych> db_ptr;
    std::map<int, std::shared_ptr<Sala_kinowa>> sale;
};

#endif // KINO_H
