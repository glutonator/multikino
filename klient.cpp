#include "klient.h"
#include <QtCore/QVariant>
#include <QDebug>

Klient::Klient(int id)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    select(id);
}

void Klient::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Klient WHERE IdKlient = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdKlient = pobieranie.value("IdKlient").toInt();
        IdRodzaj_znizki = pobieranie.value("IdRodzaj_znizki").toInt();
        imie = pobieranie.value("imie").toString();
        nazwisko = pobieranie.value("nazwisko").toString();
        mail = pobieranie.value("mail").toString();
        numer_karty_lojaln = pobieranie.value("numer_karty_lojanosciowej").toInt();
    }
    qDebug() << IdKlient << imie << nazwisko << mail << IdRodzaj_znizki;
    rodzaj_znizki = std::make_shared<Rodzaj_znizki>(IdRodzaj_znizki);
}

QString Klient::getRodzaj_znizki(){
    return rodzaj_znizki->getRodzaj_znizki();
}
