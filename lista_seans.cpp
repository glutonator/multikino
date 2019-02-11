#include "lista_seans.h"
#include <QDebug>
#include <QtCore/QVariant>
#include <QDate>
#include <QTime>

Lista_seans::Lista_seans()
{
    db_ptr = std::make_shared<const Baza_danych>(Baza_danych::getInstance());
}

void Lista_seans::select(std::shared_ptr<Wersja_filmu> ptr){
    QSqlQuery pobieranie(db_ptr->getDb());
    pobieranie.prepare("SELECT Seans.IdSeans FROM Seans " \
                       "INNER JOIN Slot_czasowy " \
                       "ON Seans.IdSlot_czasowy = Slot_czasowy.IdSlot_czasowy " \
                       "WHERE Seans.IdWersja_filmu = :Id AND (Slot_czasowy.data > :Data1 OR (Slot_czasowy.data = :Data2 AND Slot_czasowy.czas_rozpocz >= :Godzina))");
    pobieranie.bindValue(":Id", ptr->getId());
    pobieranie.bindValue(":Data1", "2017-01-26");
    pobieranie.bindValue(":Data2", "2017-01-26");
    pobieranie.bindValue(":Godzina", QTime::currentTime().toString());
    pobieranie.exec();
    while(pobieranie.next()){
        auto temp = std::make_shared<Seans>();
        qDebug() << pobieranie.value(0).toInt();
        temp->select(pobieranie.value(0).toInt());
        temp->setWersja_filmu(ptr);
        temp->wyswietl();
        lista[temp->getData()].push_back(temp);
    }
}

std::vector<QDate> Lista_seans::getLista_data(){
    std::vector<QDate> lista_data;
    for (auto elem : lista){
        lista_data.push_back(elem.first);
    }
    return lista_data;
}

std::vector<std::shared_ptr<Seans>>& Lista_seans::getLista_seans(const QDate& data_val){
    auto temp = lista.find(data_val);
    return (*temp).second;
}

std::shared_ptr<Seans> Lista_seans::find(QDate data, QTime godz){
    auto temp = lista.find(data);
    for (auto elem : (*temp).second){
        if (elem->getGodz() == godz)
            return elem;
    }
    return nullptr;
}
