#include "panel_biletomat.h"
#include "ui_panel_biletomat.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


Panel_Biletomat::Panel_Biletomat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Panel_Biletomat)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Panel_Biletomat::~Panel_Biletomat()
{
    delete ui;
}

void Panel_Biletomat::sprzedaz(){
    sprzedaz_ptr = std::make_shared<Sprzedaz>();
    skanowanie_karty.setSprzedaz(sprzedaz_ptr);
    wybor_seansu.setSprzedaz(sprzedaz_ptr);
    wybor_miejsc.setSprzedaz(sprzedaz_ptr);
    system_platnosci.setSprzedaz(sprzedaz_ptr);
    this->hide();
    bool zamknij = skanowanie_karty.open();
    skanowanie_karty.close();
    if (zamknij){
        this->show();
        return;
    }
    zamknij = wybor_seansu.open();
    wybor_seansu.close();
    if (zamknij){
        this->show();
        return;
    }
    zamknij = wybor_miejsc.open();
    wybor_miejsc.close();
    if (zamknij){
        this->show();
        return;
    }
    zamknij = system_platnosci.open();
    system_platnosci.close();
    if (zamknij){
        this->show();
        return;
    }
    sprzedaz_ptr->dodanie_do_bazy();
    this->show();
    std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
    box->setText("Trwa drukowanie biletu");
    box->setModal(true);
    box->exec();
    drukuj_bilety();
}

void Panel_Biletomat::rezerwacja()
{
    rezerwacja_ptr = std::make_shared<Rezerwacja>();
    numer_rezerwacji.setRezerwacja(rezerwacja_ptr);

    this->hide();
    bool zamknij = numer_rezerwacji.open();
    numer_rezerwacji.close();
    if(zamknij){
        this->show();
        return;
    }
    skanowanie_karty_2.setRezerwacja(rezerwacja_ptr);
    zamknij = skanowanie_karty_2.open();
    skanowanie_karty_2.close();
    if (zamknij){
        this->show();
        return;
    }
    podsumowanie_tranzakcji.setRezerwacja(rezerwacja_ptr);
    zamknij = podsumowanie_tranzakcji.open();
    podsumowanie_tranzakcji.close();
    if (zamknij){
        this->show();
        return;
    }

    system_platnosci.setRezerwacja(rezerwacja_ptr);
    zamknij = system_platnosci.open();
    system_platnosci.close();
    if (zamknij){
        this->show();
        return;
    }
    int id_sprzedaz = rezerwacja_ptr->dodanie_do_bazy();
    sprzedaz_ptr = std::make_shared<Sprzedaz>();
    sprzedaz_ptr->select(id_sprzedaz);
    this->show();
    std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
    box->setText("Trwa drukowanie biletu");
    box->setModal(true);
    box->exec();
    drukuj_bilety();
}

void Panel_Biletomat::drukuj()
{
    sprzedaz_ptr = std::make_shared<Sprzedaz>();
    numer_zamowienia.setSprzedaz(sprzedaz_ptr);
    this->hide();
    bool zamknij = numer_zamowienia.open();
    numer_zamowienia.close();
    if (zamknij){
        this->show();
        return;
    }
    //koniec
    this->show();
    std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
    box->setText("Trwa drukowanie biletu");
    box->setModal(true);
    box->exec();
    drukuj_bilety();
}

void Panel_Biletomat::on_sprzedazButton_clicked()
{
    sprzedaz();
}

void Panel_Biletomat::on_rezerwacjaButton_clicked()
{
    rezerwacja();
}

void Panel_Biletomat::on_drukowanieButton_clicked()
{
    drukuj();
}

void Panel_Biletomat::drukuj_bilety(){
    QFile file("bilet_" + QString::number(sprzedaz_ptr->getId()) + ".txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (std::shared_ptr<Seans_miejsce> elem : sprzedaz_ptr->getLista_seans_miejsce()->getLista()){
        out << "Film: ";
        out << elem->getSeans()->getWersja_filmu()->getFilm()->getTytul();
        out << "\t Wersja: ";
        out << elem->getSeans()->getWersja_filmu()->getWersja();
        out << "\t Dzien: " << elem->getSeans()->getData().toString();
        out << " Godzina: " << elem->getSeans()->getGodz().toString() << "\n";
        out << "Rzad: ";
        out << elem->getRzad() << "\t" << "Miejsce: " << elem->getWiersz();
        out << "\tBilet: " << elem->getRodzaj_biletu();
        out << "\tCena: " << elem->getCena() << "\n\n";
    }
}
