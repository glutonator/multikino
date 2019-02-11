#include "film.h"
#include <QtCore/QVariant>
#include <QDebug>

Film::Film()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Film::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Film WHERE IdFilm = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdFilm = pobieranie.value(0).toInt();
        IdKategoria = pobieranie.value(1).toInt();
        tytul = pobieranie.value(2).toString();
        czas_trwania = pobieranie.value(3).toInt();
    }
    kategoria = std::make_shared<Kategoria>();
    kategoria->select(IdKategoria);
}

void Film::wyswietl(){
    qDebug() << IdFilm << tytul  << czas_trwania;
    kategoria->wyswietl();
}

QString& Film::getTytul(){
    return tytul;
}

int Film::getId(){
    return IdFilm;
}

float Film::getCena(){
    return kategoria->getCena();
}
