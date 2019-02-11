#ifndef WYBOR_MIEJSC_H
#define WYBOR_MIEJSC_H

#include <QMainWindow>
#include <QPushButton>
#include "sprzedaz.h"
#include "lista_seans_miejsce.h"
#include <map>
#include <QSignalMapper>

namespace Ui {
class Wybor_miejsc;
}

class Wybor_miejsc : public QMainWindow
{
    Q_OBJECT

public:
    explicit Wybor_miejsc(QWidget *parent = 0);
    ~Wybor_miejsc();
    bool open();
    void close();
    void setSprzedaz(std::shared_ptr<Sprzedaz> ptr);


signals:
    void closeWindow();
    void miejsceClicked(int miejsce);

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void wybierzMiejsce(int id_sm);

private:
    void zmien_status_seans_miejsce(std::shared_ptr<Seans_miejsce> aktualny_ptr, int dodaj);
    Ui::Wybor_miejsc *ui;
    int lb_biletow;
    std::shared_ptr<Sprzedaz> sprzedaz;
    std::shared_ptr<Lista_seans_miejsce> lista_seans_miejsce;
    std::shared_ptr<Lista_seans_miejsce> wybrane_miejsca;
    std::vector<std::shared_ptr<QPushButton>> przyciski;
    std::shared_ptr<QSignalMapper> signalMapper;
    bool zamknij;
    void reset();
    void generujModel();
    void updateLista_biletow();
};

#endif // WYBOR_MIEJSC_H
