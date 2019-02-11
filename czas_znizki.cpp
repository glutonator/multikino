#include "czas_znizki.h"
#include <QtCore/QVariant>
#include <QDebug>

Czas_znizki::Czas_znizki(int id)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    select(id);
}

void Czas_znizki::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT c.IdCzas_znizki, c.godz_rozpocz, c.godz_zakoncz, d.dzien "
                       "FROM Czas_znizki as c " \
                       "INNER JOIN Dzien as d " \
                       "ON c.IdDzien = d.IdDzien " \
                       "WHERE c.IdCzas_znizki = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdCzas_znizki = pobieranie.value(0).toInt();
        dzien = pobieranie.value(3).toString();
        godz_rozpocz = pobieranie.value(1).toTime();
        godz_zakoncz = pobieranie.value(2).toTime();
        qDebug() << IdCzas_znizki << dzien << godz_rozpocz << godz_zakoncz;
    }
}
