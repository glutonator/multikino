#ifndef SALA_KINOWA_H
#define SALA_KINOWA_H
#include "miejsce.h"

#include <memory>
#include <QDebug>
#include <QString>
#include <map>


class Sala_kinowa
{
public:
    Sala_kinowa(int Id);
    void wyswietl();
    std::shared_ptr<Miejsce> find_miejsce(int id);
    int& getId();
    int getNumer_sali();
private:
    int IdSala_kinowa;
    int IdKino;
    int Numer_sali;
    std::shared_ptr<const Baza_danych> db_ptr;
    // map <id miejsce, miejsce ptr>
    std::map<int, std::shared_ptr<Miejsce>> miejsca;
};

#endif // SALA_KINOWA_H
