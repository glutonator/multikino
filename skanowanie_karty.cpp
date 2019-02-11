#include "skanowanie_karty.h"
#include "ui_skanowanie_karty.h"
#include <QEventLoop>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>
#include <QCloseEvent>

Skanowanie_Karty::Skanowanie_Karty(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Skanowanie_Karty),
    zamknij(false)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Skanowanie_Karty::~Skanowanie_Karty()
{
    delete ui;

}

void Skanowanie_Karty::closeEvent(QCloseEvent *event){
    event->ignore();
    zamknij = true;
    emit closeWindow();
}

bool Skanowanie_Karty::open(){
    this->show();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Skanowanie_Karty::reset(){
    sprzedaz = nullptr;
    zamknij = false;
}

void Skanowanie_Karty::close(){
    reset();
    this->hide();
    return;
}

void Skanowanie_Karty::on_okButton_clicked()
{
    qDebug() << ui->spinBox->value();
    if (sprzedaz->create_klient(ui->spinBox->value())){
        zamknij = false;
        emit closeWindow();
    } else {
        std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
        box->setText("Niepoprawny kod karty");
        box->setModal(true);
        box->exec();
    }
}

void Skanowanie_Karty::setSprzedaz(std::shared_ptr<Sprzedaz> ptr){
    sprzedaz = ptr;
}

void Skanowanie_Karty::on_brak_kartyButton_clicked()
{
    if (sprzedaz->create_klient(0)){
        zamknij = false;
        emit closeWindow();
    } else {
        std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
        box->setText("Problem w łączeniu z bazą");
        box->setModal(true);
        box->exec();
    }
}
