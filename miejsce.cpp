#include "miejsce.h"


Miejsce::Miejsce(int Id)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Miejsce WHERE IdMiejsce = :Id");
    pobieranie.bindValue(":Id", Id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdMiejsce = pobieranie.value(0).toInt();
        IdSala_kinowa = pobieranie.value(1).toInt();
        rzad = pobieranie.value(2).toInt();
        wiersz = pobieranie.value(3).toInt();
    }
}

void Miejsce::wyswietl(){
    qDebug() << "Miejsce: " << IdMiejsce << ": "<< IdSala_kinowa << ": " << rzad << ": " << wiersz;
}

int& Miejsce::getId(){
    return IdMiejsce;
}

int Miejsce::getWiersz(){
    return wiersz;
}

int Miejsce::getIdSala_kinowa(){
    return IdSala_kinowa;
}

int Miejsce::getRzad(){
    return rzad;
}
