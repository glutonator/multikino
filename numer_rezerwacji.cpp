#include "numer_rezerwacji.h"
#include "ui_numer_rezerwacji.h"
#include <QEventLoop>
#include <QDebug>
#include <QMessageBox>
#include <QErrorMessage>

Numer_Rezerwacji::Numer_Rezerwacji(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Numer_Rezerwacji)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Numer_Rezerwacji::~Numer_Rezerwacji()
{
    delete ui;
}

bool Numer_Rezerwacji::open()
{
    this->show();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Numer_Rezerwacji::close()
{
    reset();
    this->hide();
    return;
}

void Numer_Rezerwacji::reset(){
    rezerwacja = nullptr;
    zamknij = false;
}

void Numer_Rezerwacji::setRezerwacja(std::shared_ptr<Rezerwacja> ptr)
{
    rezerwacja=ptr;
}

void Numer_Rezerwacji::on_okButton_clicked()
{
    qDebug() << ui->spinBox->value();
    if (rezerwacja->select(ui->spinBox->value())){
        zamknij = false;
        emit closeWindow();
    } else {
        std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>();
        box->setText("Niepoprawny nr rezerwacji");
        box->setModal(true);
        box->exec();
    }
}

void Numer_Rezerwacji::on_cancelButton_clicked()
{
    zamknij = true;
    emit closeWindow();
}
