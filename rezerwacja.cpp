#include "rezerwacja.h"
#include <QMessageBox>
#include <QSqlDriver>
#include <QtCore/QVariant>
#include <QDebug>
#include "baza_danych.h"
#include <QBitArray>
#include <QByteArray>

Rezerwacja::Rezerwacja() : IdKlient(0), IdSeans_miejsce(0), IdRezerwacja(0), nr_rezerw(0), data(),
    klient(nullptr)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    auto pom2 = std::make_shared<Lista_seans_miejsce>();
    setLista_seans_miejsce(pom2);
}

bool Rezerwacja::select(int id)
{
    QSqlQuery zapytanie(db_ptr->getDb());
    zapytanie.prepare("SELECT * FROM Rezerwacja WHERE IdRezerwacja = :Id");
    zapytanie.bindValue(":Id", id);
    zapytanie.exec();
    if (zapytanie.size() < 1){
        qDebug() << zapytanie.size();
        return false;
    }
    while(zapytanie.next()){
        if (zapytanie.value("zrealizowane").toInt() == 1)
            return false;
        nr_rezerw = zapytanie.value("IdRezerwacja").toInt();
        IdSeans_miejsce.push_back(zapytanie.value("IdSeans_miejsce").toInt());
        IdKlient = zapytanie.value("IdKlient").toInt();
        data = zapytanie.value("data").toDate();
        qDebug() << nr_rezerw << IdKlient << data;
        std::shared_ptr<Kino> kino_ptr = std::make_shared<Kino>(Kino::getInstance());
        auto temp = std::make_shared<Seans_miejsce>();
        temp->select(IdSeans_miejsce.back());

        //uzupelninaie obiektu seans
        auto temp_seans = std::make_shared<Seans>();
        temp_seans->select(temp->getIdSeans());
        temp->setSeans(temp_seans);
        auto temp_wersja_filmu = std::make_shared<Wersja_filmu>();
        temp_wersja_filmu->select((temp_seans->getIdWersja_filmu()));
        temp_seans->setWersja_filmu(temp_wersja_filmu);
        auto temp_film = std::make_shared<Film>();
        temp_film->select(temp_wersja_filmu->getIdFilm());
        temp_wersja_filmu->setFilm(temp_film);
        temp->setMiejsce(kino_ptr->find_miejsce(temp->getIdMiejsce()));


        lista_seans_miejsce->addSeans_miejsce(temp);
    }
    return true;
}

//id jest nr karty bo potrzeba karty do aktywacji zniżek
bool Rezerwacja::create_klient(int id)
{
    QSqlQuery zapytanie(db_ptr->getDb());
    zapytanie.prepare("SELECT * FROM Klient WHERE numer_karty_lojanosciowej = :Id");
    zapytanie.bindValue(":Id", id);
    zapytanie.exec();
    qDebug() << db_ptr->getDb().driver()->hasFeature(QSqlDriver::QuerySize);
    if (zapytanie.size() != 1){
        qDebug() << zapytanie.size();
        return false;
    }
    while(zapytanie.next()){
        IdKlient = zapytanie.value(0).toInt();
        qDebug() << IdKlient;
        klient = std::make_shared<Klient>(IdKlient);
    }
    return true;
}

int Rezerwacja::dodanie_do_bazy()
{
    QSqlQuery zapytanie(db_ptr->getDb());
    zapytanie.prepare("SELECT * FROM Sprzedaz");
    zapytanie.exec();
    zapytanie.last();
    int index = zapytanie.value(0).toInt();
    index++;
    qDebug() <<index;

//    IdKlient = 5;
//    QDate datttta = QDate::currentDate();
//    int wartosc =12;

    //tutaj petla dla całej listy
    for (std::shared_ptr<Seans_miejsce> elem : lista_seans_miejsce->getLista()){
        zapytanie.prepare("INSERT INTO Sprzedaz (IdSprzedaz, IdSeans_miejsce, IdKlient, data, wartosc) "
                          "VALUES (:Index, :IdSM, :IdKl, :Data, :Wartosc)");
        zapytanie.bindValue(":Index",index);
        zapytanie.bindValue(":IdSM", elem->getIdSeans_miejsce());
        if (IdKlient == 0){
            zapytanie.bindValue(":IdKl", QVariant(QVariant::Int));
        } else {
            zapytanie.bindValue(":IdKl", IdKlient);
        }
        zapytanie.bindValue(":Data", QDate::currentDate());
        zapytanie.bindValue(":Wartosc", elem->getCena());
        zapytanie.exec();
        qDebug() << db_ptr->getDb().driver()->hasFeature(QSqlDriver::QuerySize);
        zapytanie.prepare("UPDATE Seans_miejsce SET IdRodzaj_biletu = :IdRB, zajete = 1 WHERE IdSeans_miejsce = :IdSM ");
        zapytanie.bindValue(":IdSM", elem->getIdSeans_miejsce());
        QString rodzaj_biletu = elem->getRodzaj_biletu();
        if (rodzaj_biletu == "studencki"){
            zapytanie.bindValue(":IdRB", 2);
        } else if (rodzaj_biletu == "emerycki"){
            zapytanie.bindValue(":IdRB", 3);
        } else {
            zapytanie.bindValue(":IdRB", 1);
        }
        zapytanie.exec();
        zapytanie.prepare("UPDATE Rezerwacja SET zrealizowane = :val, IdKlient = :IdKl WHERE IdSeans_miejsce = :IdSM ");
        zapytanie.bindValue(":val", 1);
        if (IdKlient == 0){
            zapytanie.bindValue(":IdKl", QVariant(QVariant::Int));
        } else {
            zapytanie.bindValue(":IdKl", IdKlient);
        }
        zapytanie.bindValue(":IdSM", elem->getIdSeans_miejsce());
        zapytanie.exec();
    }
    //koniec petli
    return index;
}

void Rezerwacja::setLista_seans_miejsce(std::shared_ptr<Lista_seans_miejsce> ptr){
    lista_seans_miejsce = ptr;
}

std::shared_ptr<Lista_seans_miejsce> Rezerwacja::getLista_seans_miejsce(){
    return lista_seans_miejsce;
}

QString Rezerwacja::getRodzaj_znizki(){
    return klient->getRodzaj_znizki();
}
