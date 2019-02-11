#include "lista_film.h"
#include <QtCore/QVariant>

Lista_film::Lista_film()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Lista_film::select(QDate data){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT IdFilm FROM Film WHERE data_ostaniego >= :Data");
    pobieranie.bindValue(":Data", data);
    pobieranie.exec();
    while(pobieranie.next()){
        auto temp = std::make_shared<Film>();
        temp->select(pobieranie.value(0).toInt());
        temp->wyswietl();
        lista.push_back(temp);
    }
}

std::vector<std::shared_ptr<Film>>& Lista_film::getLista_film(){
    return lista;
}

std::shared_ptr<Film> Lista_film::find (QString tytul){
    for (auto elem : lista){
        if (elem->getTytul() == tytul){
            return elem;
        }
    }
    return nullptr;
}
