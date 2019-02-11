#include "wybor_seansu.h"
#include "ui_wybor_seansu.h"
#include <QDate>
#include <QMessageBox>

Wybor_seansu::Wybor_seansu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Wybor_seansu),
    lista_film(nullptr),
    lista_wersja_filmu(nullptr),
    lista_seans(nullptr),
    sprzedaz(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
}

Wybor_seansu::~Wybor_seansu()
{
    delete ui;
}

void Wybor_seansu::repertuar(){
    lista_film = std::make_shared<Lista_film>();
    lista_film->select(QDate::currentDate());
    auto temp = lista_film->getLista_film();
    for (auto elem : temp){
        ui->filmBox->addItem(elem->getTytul());
    }
}

bool Wybor_seansu::open(){
    this->show();
    repertuar();
    QEventLoop petla;
    connect(this, SIGNAL(closeWindow()), &petla, SLOT(quit()));
    petla.exec();
    return zamknij;
}

void Wybor_seansu::reset(){
    ui->filmBox->clear();
    lista_film = nullptr;
    lista_wersja_filmu = nullptr;
    lista_seans = nullptr;
    lista_seans_miejsce = nullptr;
    sprzedaz = nullptr;
    zamknij = false;
}

void Wybor_seansu::close(){
    reset();
    this->hide();
    return;
}

void Wybor_seansu::setSprzedaz(std::shared_ptr<Sprzedaz> ptr){
    sprzedaz = ptr;
    return;
}

void Wybor_seansu::on_cancelButton_clicked()
{
    zamknij = true;
    emit closeWindow();
}

void Wybor_seansu::on_okButton_clicked(){
    auto wybranySeans = lista_seans->find(QDate::fromString(ui->dataBox->currentText()), QTime::fromString(ui->godzinaBox->currentText()));
    lista_seans_miejsce = std::make_shared<Lista_seans_miejsce>();
    lista_seans_miejsce->select(wybranySeans);

    sprzedaz->setLista_seans_miejsce(lista_seans_miejsce);
    zamknij = false;
    emit closeWindow();
}

void Wybor_seansu::on_filmBox_currentIndexChanged(const QString &arg1)
{
    ui->wersjaBox->clear();
    if (arg1 != ""){
        auto temp = lista_film->find(ui->filmBox->currentText());
        //bez tworzenia
        lista_wersja_filmu = std::make_shared<Lista_wersja_filmu>();
        lista_wersja_filmu->select(temp);
        auto temp_lista = lista_wersja_filmu->getLista_wersja_filmu();
        for (auto elem : temp_lista){
            ui->wersjaBox->addItem(elem->getWersja());
        }
    }
}

void Wybor_seansu::on_dataBox_currentIndexChanged(const QString &arg1)
{
    ui->godzinaBox->clear();
    if (arg1 != ""){
        auto temp_lista = lista_seans->getLista_seans(QDate::fromString(ui->dataBox->currentText()));
        for (auto elem : temp_lista){
            ui->godzinaBox->addItem(elem->getGodz().toString());
        }
    }
}

void Wybor_seansu::on_godzinaBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == ""){
        ui->okButton->setEnabled(false);
    } else ui->okButton->setEnabled(true);
}

void Wybor_seansu::on_wersjaBox_currentIndexChanged(int index)
{
    ui->dataBox->clear();
    QString text = ui->wersjaBox->currentText();
    if (text != ""){
        auto temp = lista_wersja_filmu->find(text);
        //bez tworzenia
        lista_seans = std::make_shared<Lista_seans>();
        lista_seans->select(temp);
        auto temp_lista = lista_seans->getLista_data();
        for (auto elem : temp_lista){
            ui->dataBox->addItem(elem.toString());
        }
    }
}
