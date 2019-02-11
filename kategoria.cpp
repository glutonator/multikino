#include "kategoria.h"
#include <QtCore/QVariant>
#include <QDebug>

Kategoria::Kategoria()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Kategoria::select(int id){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Kategoria WHERE IdKategoria = :Id");
    pobieranie.bindValue(":Id", id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdKategoria = pobieranie.value(0).toInt();
        cena_bazowa = pobieranie.value(2).toInt();
        nazwa = pobieranie.value(1).toString();
    }
}

float Kategoria::getCena(){
    return cena_bazowa;
}

void Kategoria::wyswietl(){
    qDebug() << IdKategoria << cena_bazowa << nazwa;
}
