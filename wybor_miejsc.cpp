#include "wybor_miejsc.h"
#include "ui_wybor_miejsc.h"
#include <QSignalMapper>
#include <QGridLayout>
#include <QPalette>
#include <QLabel>
#include "kino.h"

Wybor_miejsc::Wybor_miejsc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Wybor_miejsc),
    lb_biletow(0)
{
    signalMapper = std::make_shared<QSignalMapper>(this);
    connect(signalMapper.get(), SIGNAL(mapped(int)), this, SIGNAL(miejsceClicked(int)));
    connect(this, SIGNAL(miejsceClicked(int)), this, SLOT(wybierzMiejsce(int)));
    wybrane_miejsca = std::make_shared<Lista_seans_miejsce>();
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList list;
    list << "Bilet" << "Rząd" << "Miejsce" << "Cena";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 60);
    ui->tableWidget->setColumnWidth(2, 60);
    ui->tableWidget->setColumnWidth(3, 60);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Wybor_miejsc::~Wybor_miejsc()
{
    delete ui;
}

bool Wybor_miejsc::open(){
    lista_seans_miejsce = sprzedaz->getLista_seans_miejsce();
    generujModel();
    updateLista_biletow();
    this->show();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Wybor_miejsc::reset(){
    lb_biletow = 0;
    sprzedaz = nullptr;
    lista_seans_miejsce = nullptr;
    wybrane_miejsca = std::make_shared<Lista_seans_miejsce>();
    for (std::shared_ptr<QPushButton> przycisk : przyciski){
        signalMapper->removeMappings(przycisk.get());
        ui->gridLayout->removeWidget(przycisk.get());
        przycisk.reset();
    }
    przyciski.clear();
    zamknij = false;
}

void Wybor_miejsc::close(){
    reset();
    this->hide();
    return;
}

void Wybor_miejsc::setSprzedaz(std::shared_ptr<Sprzedaz> ptr){
    sprzedaz = ptr;
}

void Wybor_miejsc::generujModel(){
    auto lista = lista_seans_miejsce->getLista();
    int max_rzad = lista_seans_miejsce->getMax_rzad();
    int max_wiersz = lista_seans_miejsce->getMax_wiersz();
    for (int i = 0; i < max_rzad; ++i){
        ui->gridLayout->addWidget(new QLabel(QString::number(i+1)), i+1, 0);
        ui->gridLayout->addWidget(new QLabel(""), i+1, max_wiersz+1);
    }

    int i = 0;
    for (std::shared_ptr<Seans_miejsce> elem : lista) {
        if (i == 0){
            ui->filmLabel->setText(elem->getSeans()->getWersja_filmu()->getFilm()->getTytul());
            ui->wersjaLabel->setText(elem->getSeans()->getWersja_filmu()->getWersja());
            ui->dataLabel->setText(elem->getSeans()->getData().toString());
            ui->godzinaLabel->setText(elem->getSeans()->getGodz().toString());
            ui->salaLabel->setText(QString::number(Kino::getInstance().find_sala(elem->getIdSala())->getNumer_sali()));
        }
        ++i;
        std::shared_ptr<QPushButton> przycisk = std::make_shared<QPushButton>(QString::number(elem->getWiersz()));
        przycisk->setFixedSize(50,50);
        przycisk->setAutoFillBackground(true);
        if (elem->getZajete()){
            przycisk->setStyleSheet("QPushButton { background-color: rgb(245, 81, 81); border: 0px } ");
            przycisk->setEnabled(false);
        } else {
            przycisk->setStyleSheet("QPushButton { background-color: rgb(142, 176, 255); border: 0px } " \
                                    "QPushButton:checked { background-color: rgb(134,195,36); border: 0px; }");
            przycisk->setCheckable(true);
            przycisk->setEnabled(true);
        }

        signalMapper->setMapping(przycisk.get(), elem->getIdSeans_miejsce());
        connect(przycisk.get(), SIGNAL(clicked()), signalMapper.get(), SLOT(map()));
        ui->gridLayout->addWidget(przycisk.get(), elem->getRzad(), elem->getWiersz());
        przyciski.push_back(przycisk);
    }
}

void Wybor_miejsc::on_cancelButton_clicked()
{
    for (std::shared_ptr<Seans_miejsce> elem : wybrane_miejsca->getLista()){
        zmien_status_seans_miejsce(elem, 0);
    }
    zamknij = true;
    emit closeWindow();
}

void Wybor_miejsc::on_okButton_clicked(){
    sprzedaz->setLista_seans_miejsce(wybrane_miejsca);
    zamknij = false;
    emit closeWindow();
}

void Wybor_miejsc::wybierzMiejsce(int id_sm){
    qDebug() << id_sm;
    std::shared_ptr<Seans_miejsce> temp = lista_seans_miejsce->find(id_sm);
    if (wybrane_miejsca->find(temp->getIdSeans_miejsce()) != nullptr){
        temp->setRodzaj_biletu("normalny");
        --lb_biletow;
        wybrane_miejsca->removeSeans_miejsce(temp);
        zmien_status_seans_miejsce(temp, 0);
    } else {
        if (lb_biletow <4){
            temp->setRodzaj_biletu(sprzedaz->getRodzaj_znizki());
        }
        wybrane_miejsca->addSeans_miejsce(temp);
        ++lb_biletow;
        zmien_status_seans_miejsce(temp, 1);
    }
    updateLista_biletow();
}

void Wybor_miejsc::updateLista_biletow(){
    if (lb_biletow < 1)
        ui->okButton->setEnabled(false);
    else ui->okButton->setEnabled(true);
    int current_rows = ui->tableWidget->rowCount();
    for (int i = 0; i < current_rows; ++i){
        ui->tableWidget->removeRow(0);
    }
    float suma = 0;
    for (std::shared_ptr<Seans_miejsce> elem : wybrane_miejsca->getLista()){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(elem->getRodzaj_biletu()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(elem->getRzad())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(elem->getWiersz())));
        // cena ze znizka
        float cena = elem->getCena();
        suma += cena;
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(QString::number(cena)));
        qDebug() << elem->getRodzaj_biletu() << elem->getRzad() << elem->getWiersz() << cena;
    }
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem("Suma"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(QString::number(suma)));
}

void Wybor_miejsc::zmien_status_seans_miejsce(std::shared_ptr<Seans_miejsce> aktualny_ptr, int dodaj){
    QSqlQuery zapytanie(Baza_danych::getInstance().getDb());
    zapytanie.prepare("UPDATE Seans_miejsce SET IdRodzaj_biletu = :IdRB, zajete = :val WHERE IdSeans_miejsce = :IdSM ");
    zapytanie.bindValue(":IdSM", aktualny_ptr->getIdSeans_miejsce());
    zapytanie.bindValue(":val", dodaj);
    QString rodzaj_biletu = aktualny_ptr->getRodzaj_biletu();
    if (rodzaj_biletu == "studencki"){
        zapytanie.bindValue(":IdRB", 2);
    } else if (rodzaj_biletu == "emerycki"){
        zapytanie.bindValue(":IdRB", 3);
    } else {
        zapytanie.bindValue(":IdRB", 1);
    }
    zapytanie.exec();
}
