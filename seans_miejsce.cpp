#include "seans_miejsce.h"
#include <QDebug>
#include <QtCore/QVariant>

Seans_miejsce::Seans_miejsce()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Seans_miejsce::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT Seans_miejsce.IdSeans_miejsce, Seans_miejsce.IdMiejsce, Seans_miejsce.IdSeans, " \
                       "Seans_miejsce.zajete, Rodzaj_biletu.rodzaj_biletu, Rodzaj_biletu.procent_znizki, Rodzaj_biletu.IdRodzaj_biletu " \
                       "FROM Seans_miejsce " \
                       "INNER JOIN Rodzaj_biletu " \
                       "ON Seans_miejsce.IdRodzaj_biletu = Rodzaj_biletu.IdRodzaj_biletu " \
                       "WHERE Seans_miejsce.IdSeans_miejsce = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdSeans_miejsce = pobieranie.value(0).toInt();
        IdMiejsce = pobieranie.value(1).toInt();
        IdSeans = pobieranie.value(2).toInt();
        zajete = pobieranie.value(3).toBool();
        rodzaj_biletu = pobieranie.value(4).toString();
        procent_znizki = pobieranie.value(5).toInt();
        IdRodzaj_biletu = pobieranie.value(6).toInt();
    }
}

void Seans_miejsce::setSeans(std::shared_ptr<Seans> ptr){
    seans = ptr;
}

void Seans_miejsce::setMiejsce(std::shared_ptr<Miejsce> ptr){
    miejsce = ptr;
}

int Seans_miejsce::getRzad(){
    return miejsce->getRzad();
}

int Seans_miejsce::getWiersz(){
    return miejsce->getWiersz();
}

int Seans_miejsce::getIdSeans_miejsce(){
    return IdSeans_miejsce;
}

int Seans_miejsce::getIdMiejsce(){
    return IdMiejsce;
}

void Seans_miejsce::wyswietl(){
    qDebug() << IdSeans_miejsce << IdMiejsce << zajete << rodzaj_biletu;
    miejsce->wyswietl();
}

bool Seans_miejsce::getZajete(){
    return zajete;
}

int Seans_miejsce::getIdSeans(){
    return IdSeans;
}

std::shared_ptr<Seans> Seans_miejsce::getSeans()
{
    return seans;
}

float Seans_miejsce::getCena(){
    return seans->getCena() * (100 - procent_znizki)/100;
}

QString Seans_miejsce::getRodzaj_biletu(){
    return rodzaj_biletu;
}

void Seans_miejsce::setRodzaj_biletu(QString rodzaj){
    rodzaj_biletu = rodzaj;
    if (rodzaj == "studencki"){
        IdRodzaj_biletu = 2;
        procent_znizki = 40;
    } else if (rodzaj == "seniorski"){
        IdRodzaj_biletu = 3;
        procent_znizki = 50;
    } else {
        rodzaj_biletu = "normalny";
        IdRodzaj_biletu = 1;
        procent_znizki = 0;
    }
}

int Seans_miejsce::getIdSala(){
    return miejsce->getIdSala_kinowa();
}
