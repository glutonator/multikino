#ifndef PANEL_BILETOMAT_H
#define PANEL_BILETOMAT_H

#include <QMainWindow>
#include "sprzedaz.h"
#include <memory>
#include "skanowanie_karty.h"
#include "wybor_seansu.h"
#include "wybor_miejsc.h"
#include "rezerwacja.h"
#include "numer_rezerwacji.h"
#include "skanowanie_karty_2.h"
#include "podsumowanie_tranzakcji.h"
#include "numer_zamowienia.h"
#include "system_platnosci.h"

namespace Ui {
class Panel_Biletomat;
}

class Panel_Biletomat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Panel_Biletomat(QWidget *parent = 0);
    ~Panel_Biletomat();

private slots:
    void on_sprzedazButton_clicked();

    void on_rezerwacjaButton_clicked();

    void on_drukowanieButton_clicked();

private:
    Ui::Panel_Biletomat *ui;

    std::shared_ptr<Sprzedaz> sprzedaz_ptr;
    Skanowanie_Karty skanowanie_karty;
    Wybor_seansu wybor_seansu;
    Wybor_miejsc wybor_miejsc;
    System_platnosci system_platnosci;

    void sprzedaz();
    void drukuj_bilety();
    //rezerwacja
    std::shared_ptr<Rezerwacja> rezerwacja_ptr;
    Numer_Rezerwacji numer_rezerwacji;
    Skanowanie_Karty_2 skanowanie_karty_2;
    Podsumowanie_Tranzakcji podsumowanie_tranzakcji;
    void rezerwacja();

    //drukowanie
    Numer_zamowienia numer_zamowienia;
    void drukuj();
};

#endif // PANEL_BILETOMAT_H
