#ifndef SYSTEM_PLATNOSCI_H
#define SYSTEM_PLATNOSCI_H

#include <QMainWindow>
#include "lista_seans_miejsce.h"
#include "sprzedaz.h"
#include "rezerwacja.h"


namespace Ui {
class System_platnosci;
}

class System_platnosci : public QMainWindow
{
    Q_OBJECT

public:
    explicit System_platnosci(QWidget *parent = 0);
    ~System_platnosci();
    bool open();
    void close();
    void setSprzedaz(std::shared_ptr<Sprzedaz> ptr);
    void setRezerwacja(std::shared_ptr<Rezerwacja> ptr);

signals:
    void closeWindow();

private slots:
    void on_platnosc_udanaButton_clicked();

    void on_platnosc_nieudanaButton_clicked();

private:
    void reset();
    Ui::System_platnosci *ui;
    std::shared_ptr<Sprzedaz> sprzedaz;
    std::shared_ptr<Lista_seans_miejsce> wybrane_miejsca;
    std::shared_ptr<Rezerwacja> rezerwacja;
    bool zamknij;
};

#endif // SYSTEM_PLATNOSCI_H
