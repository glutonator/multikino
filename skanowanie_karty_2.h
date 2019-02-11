#ifndef SKANOWANIE_KARTY_2_H
#define SKANOWANIE_KARTY_2_H

#include <QMainWindow>
#include <memory>
#include <rezerwacja.h>
#include <QCloseEvent>

namespace Ui {
class Skanowanie_Karty_2;
}

class Skanowanie_Karty_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Skanowanie_Karty_2(QWidget *parent = 0);
    ~Skanowanie_Karty_2();
    bool open();
    void close();
    void setRezerwacja(std::shared_ptr<Rezerwacja> ptr);

private:
    void reset();
    Ui::Skanowanie_Karty_2 *ui;
    std::shared_ptr<Rezerwacja> rezerwacja;
    bool zamknij;

signals:
    void closeWindow();
private slots:
    virtual void closeEvent(QCloseEvent *event);
    void on_okButton_clicked();
    void on_brak_kartyButton_clicked();
};

#endif // SKANOWANIE_KARTY_2_H
