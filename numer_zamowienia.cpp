#include "numer_zamowienia.h"
#include "ui_numer_zamowienia.h"
#include <QEventLoop>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>

Numer_zamowienia::Numer_zamowienia(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Numer_zamowienia)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Numer_zamowienia::~Numer_zamowienia()
{
    delete ui;
}

bool Numer_zamowienia::open()
{
    this->show();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Numer_zamowienia::close()
{
    reset();
    this->hide();
    return;
}

void Numer_zamowienia::reset(){
    sprzedaz = nullptr;
    zamknij = false;
}

void Numer_zamowienia::setSprzedaz(std::shared_ptr<Sprzedaz> ptr)
{
    sprzedaz = ptr;
}

void Numer_zamowienia::on_okButton_clicked()
{
    qDebug() << ui->spinBox->value();
    if (sprzedaz->select(ui->spinBox->value())){
        zamknij = false;
        emit closeWindow();
    } else {
        std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
        box->setText("Niepoprawny nr rezerwacji");
        box->setModal(true);
        box->exec();
    }
}

void Numer_zamowienia::on_cancelButton_clicked()
{
    zamknij = true;
    emit closeWindow();
}
