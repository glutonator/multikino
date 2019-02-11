#include "lista_seans_miejsce.h"
#include <QDebug>
#include <QtCore/QVariant>

Lista_seans_miejsce::Lista_seans_miejsce()
{
    max_rzad = 0;
    max_wiersz = 0;
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
    kino_ptr = std::make_shared<Kino>(Kino::getInstance());
    lista.clear();
}

void Lista_seans_miejsce::select(std::shared_ptr<Seans> ptr){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT IdSeans_miejsce FROM Seans_miejsce WHERE IdSeans = :Id");
    pobieranie.bindValue(":Id", ptr->getId());
    pobieranie.exec();
    int id_sm;
    while(pobieranie.next()){
        id_sm = pobieranie.value(0).toInt();
        auto temp = std::make_shared<Seans_miejsce>();
        qDebug() << id_sm;
        temp->select(id_sm);
        temp->setSeans(ptr);
        temp->setMiejsce(kino_ptr->find_miejsce(temp->getIdMiejsce()));
        temp->wyswietl();
        if (temp->getWiersz() > max_wiersz)
            max_wiersz = temp->getWiersz();
        if (temp->getRzad() > max_rzad)
            max_rzad = temp->getRzad();
        lista.push_back(temp);
    }
}

std::vector<std::shared_ptr<Seans_miejsce>>& Lista_seans_miejsce::getLista(){
    return lista;
}

int Lista_seans_miejsce::getMax_rzad(){
    return max_rzad;
}

int Lista_seans_miejsce::getMax_wiersz(){
    return max_wiersz;
}

void Lista_seans_miejsce::addSeans_miejsce(std::shared_ptr<Seans_miejsce> ptr){
    lista.push_back(ptr);
}

std::shared_ptr<Seans_miejsce> Lista_seans_miejsce::find(int id_sm){
    for (auto it = lista.begin(); it != lista.end(); ++it){
        if ((*it)->getIdSeans_miejsce() == id_sm)
            return *it;
    }
    return nullptr;
}

void Lista_seans_miejsce::removeSeans_miejsce(std::shared_ptr<Seans_miejsce> ptr){
    for (auto it = lista.begin(); it != lista.end(); ++it){
        if (*it == ptr){
            lista.erase(it);
            return;
        }
    }
}

void Lista_seans_miejsce::wyswietl(){
    for (std::shared_ptr<Seans_miejsce> elem : lista){
        elem->wyswietl();
    }
}
