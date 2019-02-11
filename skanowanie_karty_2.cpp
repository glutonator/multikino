#include "skanowanie_karty_2.h"
#include "ui_skanowanie_karty_2.h"
#include <QEventLoop>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>

Skanowanie_Karty_2::Skanowanie_Karty_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Skanowanie_Karty_2)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Skanowanie_Karty_2::~Skanowanie_Karty_2()
{
    delete ui;
}

void Skanowanie_Karty_2::closeEvent(QCloseEvent *event){
    event->ignore();
    zamknij = true;
    emit closeWindow();
}

bool Skanowanie_Karty_2::open()
{
    this->show();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Skanowanie_Karty_2::close()
{
    reset();
    this->hide();
    return;
}

void Skanowanie_Karty_2::reset(){
    zamknij = false;
    rezerwacja = nullptr;
}

void Skanowanie_Karty_2::setRezerwacja(std::shared_ptr<Rezerwacja> ptr)
{
    rezerwacja = ptr;
}

void Skanowanie_Karty_2::on_okButton_clicked()
{
    qDebug() << ui->spinBox->value();
    if (rezerwacja->create_klient(ui->spinBox->value())){
        zamknij = false;
        emit closeWindow();
    } else {
        std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
        box->setText("Niepoprawny kod karty");
        box->setModal(true);
        box->exec();
    }
}

void Skanowanie_Karty_2::on_brak_kartyButton_clicked()
{
    if (rezerwacja->create_klient(0)){
        zamknij = false;
        emit closeWindow();
    } else {
        std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
        box->setText("Problem w łączeniu z bazą");
        box->setModal(true);
        box->exec();
    }
}
