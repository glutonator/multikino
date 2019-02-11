#include "lista_wersja_filmu.h"
#include <QDebug>
#include <QtCore/QVariant>


Lista_wersja_filmu::Lista_wersja_filmu()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Lista_wersja_filmu::select(std::shared_ptr<Film> ptr){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT IdWersja_filmu FROM Wersja_filmu WHERE IdFilm = :Id");
    pobieranie.bindValue(":Id", ptr->getId());
    pobieranie.exec();
    while(pobieranie.next()){
        auto temp = std::make_shared<Wersja_filmu>();
        temp->select(pobieranie.value(0).toInt());
        temp->setFilm(ptr);
        temp->wyswietl();
        lista.push_back(temp);
    }
}


std::vector<std::shared_ptr<Wersja_filmu>>& Lista_wersja_filmu::getLista_wersja_filmu(){
    return lista;
}

std::shared_ptr<Wersja_filmu> Lista_wersja_filmu::find(QString wersja){
    //uzupelnic
    for (auto elem : lista){
        if (elem->getWersja() == wersja)
            return elem;
    }
    return nullptr;
}
