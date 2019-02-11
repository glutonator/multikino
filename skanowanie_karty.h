#ifndef SKANOWANIE_KARTY_H
#define SKANOWANIE_KARTY_H

#include <QMainWindow>
#include <sprzedaz.h>
#include <memory>
#include <QCloseEvent>

namespace Ui {
class Skanowanie_Karty;
}

class Skanowanie_Karty : public QMainWindow
{
    Q_OBJECT

public:
    explicit Skanowanie_Karty(QWidget *parent = 0);
    ~Skanowanie_Karty();
    bool open();
    void close();
    void setSprzedaz(std::shared_ptr<Sprzedaz> ptr);

private slots:
    virtual void closeEvent(QCloseEvent *event);

    void on_okButton_clicked();

    void on_brak_kartyButton_clicked();

private:
    void reset();
    Ui::Skanowanie_Karty *ui;
    std::shared_ptr<Sprzedaz> sprzedaz;
    bool zamknij;

signals:
    void closeWindow();

};

#endif // SKANOWANIE_KARTY_H
