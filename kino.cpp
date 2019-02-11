#include "kino.h"
#include <utility>

Kino Kino::getInstance(){
    static Kino instance(1);
    return instance;
}

Kino::Kino(int Id)
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT * FROM Kino WHERE IdKino = :Id");
    pobieranie.bindValue(":Id", Id);
    pobieranie.exec();
    while(pobieranie.next()){
        IdKino = pobieranie.value(0).toInt();
        Nazwa = pobieranie.value(1).toString();
    }
    pobieranie.prepare("SELECT IdSala_kinowa FROM Sala_kinowa WHERE IdKino = :Id");
    pobieranie.bindValue(":Id", Id);
    pobieranie.exec();
    int id_sala;
    while(pobieranie.next()){
        id_sala = pobieranie.value(0).toInt();
        auto temp = std::make_shared<Sala_kinowa>(id_sala);
        sale[id_sala] = temp;
    }
}

void Kino::wyswietl(){
    qDebug() << "Kino: " << IdKino << ": " << Nazwa;
    for (auto elem: sale){
        elem.second->wyswietl();
    }
}

std::shared_ptr<Sala_kinowa> Kino::find_sala(int id){
    auto temp = sale.find(id);
    return (*temp).second;
}

std::shared_ptr<Miejsce> Kino::find_miejsce(int id){
    for (std::pair<int, std::shared_ptr<Sala_kinowa>> elem : sale){
        std::shared_ptr<Miejsce> temp = elem.second->find_miejsce(id);
        if (temp != nullptr){
            return temp;
        }
    }
    return nullptr;
}
