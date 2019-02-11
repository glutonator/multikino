#include "sala_kinowa.h"
#include <exception>

Sala_kinowa::Sala_kinowa(int Id)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Sala_kinowa WHERE IdSala_kinowa = :Id");
    pobieranie.bindValue(":Id", Id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdSala_kinowa = pobieranie.value(0).toInt();
        Numer_sali = pobieranie.value(1).toInt();
        IdKino = pobieranie.value(2).toInt();
    }
    pobieranie.prepare("SELECT IdMiejsce FROM Miejsce WHERE IdSala_kinowa = :Id");
    pobieranie.bindValue(":Id", Id);
    pobieranie.exec();
    int id_miejsce;
    while(pobieranie.next()){
        id_miejsce = pobieranie.value(0).toInt();
        auto temp = std::make_shared<Miejsce>(id_miejsce);
        miejsca[id_miejsce] = temp;
    }
}

void Sala_kinowa::wyswietl(){
    qDebug() << "Sala: " << IdSala_kinowa << ": " << IdKino << ": " << Numer_sali;
    for (auto elem: miejsca){
        elem.second->wyswietl();
    }
}

std::shared_ptr<Miejsce> Sala_kinowa::find_miejsce(int id){
    try {
        std::shared_ptr<Miejsce> temp = miejsca.at(id);
        return temp;
    } catch (std::exception e){
        qDebug() << e.what();
        return nullptr;
    }
}

int& Sala_kinowa::getId(){
    return IdSala_kinowa;
}

int Sala_kinowa::getNumer_sali(){
    return Numer_sali;
}
