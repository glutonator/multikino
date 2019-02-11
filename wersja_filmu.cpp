#include "wersja_filmu.h"
#include <QDebug>
#include <QtCore/QVariant>

Wersja_filmu::Wersja_filmu()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Wersja_filmu::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Wersja_filmu WHERE IdWersja_filmu = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdWersja_filmu = pobieranie.value(0).toInt();
        IdFilm = pobieranie.value(1).toInt();
        wersja = pobieranie.value(2).toString();
        tech = pobieranie.value(3).toString();
    }
}

void Wersja_filmu::wyswietl(){
    qDebug() << IdWersja_filmu << IdFilm << wersja << tech;
    film->wyswietl();
}

void Wersja_filmu::setFilm(std::shared_ptr<Film> ptr){
    film = ptr;
    return;
}

QString Wersja_filmu::getWersja(){
    return (wersja + " " + tech);
}

int& Wersja_filmu::getId(){
    return IdWersja_filmu;
}

float Wersja_filmu::getCena(){
    return film->getCena();
}

int Wersja_filmu::getIdFilm()
{
    return IdFilm;
}

std::shared_ptr<Film> Wersja_filmu::getFilm()
{
    return film;
}
