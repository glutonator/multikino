#include "seans.h"
#include <QDebug>
#include <QtCore/QVariant>

Seans::Seans()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}


void Seans::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT Seans.IdSeans, Seans.IdSlot_czasowy, Seans.IdWersja_filmu, Slot_czasowy.data, " \
                   "Slot_czasowy.czas_rozpocz FROM Seans INNER JOIN Slot_czasowy " \
                   "ON Seans.IdSlot_czasowy = Slot_czasowy.IdSlot_czasowy " \
                   "WHERE Seans.IdSeans=:Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdSeans = pobieranie.value(0).toInt();
        IdSlot_czasowy = pobieranie.value(1).toInt();
        IdWerjsa_filmu = pobieranie.value(2).toInt();
        data = pobieranie.value(3).toDate();
        godz_rozpocz = pobieranie.value(4).toTime();
    }
}

void Seans::wyswietl(){
    qDebug() << IdSeans << IdSlot_czasowy << IdWerjsa_filmu << data << godz_rozpocz;
}

void Seans::setWersja_filmu(std::shared_ptr<Wersja_filmu> ptr){
    wersja_filmu = ptr;
    return;
}

QDate& Seans::getData(){
    return data;
}

QTime& Seans::getGodz(){
    return godz_rozpocz;
}

int& Seans::getId(){
    return IdSeans;
}

int Seans::getIdWersja_filmu() {
    return IdWerjsa_filmu;
}

std::shared_ptr<Wersja_filmu> Seans::getWersja_filmu()
{
    return wersja_filmu;
}

float Seans::getCena(){
    return wersja_filmu->getCena();
}
