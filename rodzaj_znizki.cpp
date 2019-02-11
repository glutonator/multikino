#include "rodzaj_znizki.h"
#include <QtCore/QVariant>
#include <QDebug>

Rodzaj_znizki::Rodzaj_znizki(int id)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    select(id);
}

void Rodzaj_znizki::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT r.IdRodzaj_znizki, r.nazwa, r.procent_znizki, rc.IdCzas_znizki " \
                       "FROM Rodzaj_znizki as r " \
                       "INNER JOIN Rodzaj_czas_znizki as rc " \
                       "ON r.IdRodzaj_znizki = rc.IdRodzaj_znizki " \
                       "WHERE r.IdRodzaj_znizki = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    int i = 0;
    qDebug() << pobieranie.size();
    while(pobieranie.next()){
        if (i == 0){
            IdRodzaj_znizki = pobieranie.value(0).toInt();
            nazwa = pobieranie.value(1).toString();
            procent_znizki = pobieranie.value(2).toInt();
            qDebug() << IdRodzaj_znizki << nazwa << procent_znizki;
        }
        auto temp_id = pobieranie.value(3).toInt();
        idCzas_znizki.push_back(temp_id);
        czas_znizki.push_back(std::make_shared<Czas_znizki>(temp_id));
        i++;
    }
}

QString Rodzaj_znizki::getRodzaj_znizki(){
    return nazwa;
}
