#ifndef NUMER_ZAMOWIENIA_H
#define NUMER_ZAMOWIENIA_H

#include <QMainWindow>
#include "sprzedaz.h"

namespace Ui {
class Numer_zamowienia;
}

class Numer_zamowienia : public QMainWindow
{
    Q_OBJECT

public:
    explicit Numer_zamowienia(QWidget *parent = 0);
    ~Numer_zamowienia();
    bool open();
    void close();
    void setSprzedaz(std::shared_ptr<Sprzedaz> ptr);

private:
    void reset();
    Ui::Numer_zamowienia *ui;
    std::shared_ptr<Sprzedaz> sprzedaz;
    bool zamknij;
signals:
    void closeWindow();
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // NUMER_ZAMOWIENIA_H
