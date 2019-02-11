#include "system_platnosci.h"
#include "ui_system_platnosci.h"
#include <QMessageBox>

System_platnosci::System_platnosci(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::System_platnosci),
    sprzedaz(nullptr),
    wybrane_miejsca(nullptr),
    zamknij(false)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

System_platnosci::~System_platnosci()
{
    delete ui;
}

bool System_platnosci::open(){
    this->show();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void System_platnosci::reset(){
    sprzedaz = nullptr;
    wybrane_miejsca = nullptr;
    rezerwacja = nullptr;
    zamknij = false;
}

void System_platnosci::close(){
    reset();
    this->hide();
}

void System_platnosci::setSprzedaz(std::shared_ptr<Sprzedaz> ptr){
    sprzedaz = ptr;
}

void System_platnosci::setRezerwacja(std::shared_ptr<Rezerwacja> ptr){
    rezerwacja = ptr;
}

void System_platnosci::on_platnosc_udanaButton_clicked()
{
    zamknij = false;
    emit closeWindow();
}

void System_platnosci::on_platnosc_nieudanaButton_clicked()
{
    zamknij = true;
    emit closeWindow();
}
