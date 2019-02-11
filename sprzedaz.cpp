#include "sprzedaz.h"
#include <QMessageBox>
#include <QSqlDriver>

Sprzedaz::Sprzedaz() : IdKlient(0), IdSprzedaz(0), nr_sprzed(0), wartosc(0), data(),
    klient(nullptr)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

bool Sprzedaz::create_klient(int id){
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

bool Sprzedaz::select (int id){
    lista_seans_miejsce = std::make_shared<Lista_seans_miejsce>();
    QSqlQuery zapytanie(db_ptr->getDb());
    zapytanie.prepare("SELECT * FROM Sprzedaz WHERE IdSprzedaz = :Id");
    zapytanie.bindValue(":Id", id);
    zapytanie.exec();
    qDebug() << db_ptr->getDb().driver()->hasFeature(QSqlDriver::QuerySize);
    if (zapytanie.size() < 1){
        qDebug() << zapytanie.size();
        return false;
    }
    while(zapytanie.next()){
        IdSprzedaz = zapytanie.value(0).toInt();
        IdSeans_miejsce.push_back(zapytanie.value(1).toInt());
        IdKlient = zapytanie.value(2).toInt();
        data = zapytanie.value(3).toDate();
        wartosc = zapytanie.value(4).toInt();
        qDebug() << IdSprzedaz << IdKlient << data << wartosc ;


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

bool Sprzedaz::dodanie_do_bazy(){
    QSqlQuery zapytanie(db_ptr->getDb());
    zapytanie.prepare("SELECT * FROM Sprzedaz");
    zapytanie.exec();
    zapytanie.last();
    int index = zapytanie.value(0).toInt();
    index++;
    IdSprzedaz = index;
    qDebug() <<index;

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
    }
    //koniec petli
    return true;
}

void Sprzedaz::setLista_seans_miejsce(std::shared_ptr<Lista_seans_miejsce> ptr){
    lista_seans_miejsce = ptr;
}

std::shared_ptr<Lista_seans_miejsce> Sprzedaz::getLista_seans_miejsce(){
    return lista_seans_miejsce;
}

QString Sprzedaz::getRodzaj_znizki(){
    return klient->getRodzaj_znizki();
}

int Sprzedaz::getId(){
    return IdSprzedaz;
}
