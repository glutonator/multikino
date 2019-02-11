#include "podsumowanie_tranzakcji.h"
#include "ui_podsumowanie_tranzakcji.h"
#include <QEventLoop>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>
#include "kino.h"

Podsumowanie_Tranzakcji::Podsumowanie_Tranzakcji(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Podsumowanie_Tranzakcji)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList list;
    list << "Bilet" << "Rząd" << "Miejsce" << "Cena";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    ui->tableWidget->setColumnWidth(0, 80);
    ui->tableWidget->setColumnWidth(1, 60);
    ui->tableWidget->setColumnWidth(2, 60);
    ui->tableWidget->setColumnWidth(3, 60);
    ui->tableWidget->setEnabled(false);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Podsumowanie_Tranzakcji::~Podsumowanie_Tranzakcji()
{
    delete ui;
}

bool Podsumowanie_Tranzakcji::open()
{
    wybrane_miejsca = rezerwacja->getLista_seans_miejsce();
    // tylko 4 bilety ze zniżką.
    int i = 0;
    for (std::shared_ptr<Seans_miejsce> elem : wybrane_miejsca->getLista()){
        if (i == 0){
            ui->filmLabel->setText(elem->getSeans()->getWersja_filmu()->getFilm()->getTytul());
            ui->wersjaLabel->setText(elem->getSeans()->getWersja_filmu()->getWersja());
            ui->dataLabel->setText(elem->getSeans()->getData().toString());
            ui->godzinaLabel->setText(elem->getSeans()->getGodz().toString());
            ui->salaLabel->setText(QString::number(Kino::getInstance().find_sala(elem->getIdSala())->getNumer_sali()));
        }
        if (i < 4)
            elem->setRodzaj_biletu(rezerwacja->getRodzaj_znizki());
        else elem->setRodzaj_biletu("normalny");
        ++i;
    }
    this->show();
    updateTabela();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Podsumowanie_Tranzakcji::close()
{
    reset();
    this->hide();
    return;
}

void Podsumowanie_Tranzakcji::reset(){
    zamknij = false;
    rezerwacja = nullptr;
    wybrane_miejsca = nullptr;
}

void Podsumowanie_Tranzakcji::setRezerwacja(std::shared_ptr<Rezerwacja> ptr)
{
    rezerwacja = ptr;
}

void Podsumowanie_Tranzakcji::on_okButton_clicked()
{
        zamknij = false;
        emit closeWindow();
}

void Podsumowanie_Tranzakcji::on_cancelButton_clicked()
{
    zamknij = true;
    emit closeWindow();
}

void Podsumowanie_Tranzakcji::updateTabela(){
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
    }
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem("Suma"));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(QString::number(suma)));
}
