#ifndef PODSUMOWANIE_TRANZAKCJI_H
#define PODSUMOWANIE_TRANZAKCJI_H

#include <QMainWindow>
#include <memory>
#include <rezerwacja.h>

namespace Ui {
class Podsumowanie_Tranzakcji;
}

class Podsumowanie_Tranzakcji : public QMainWindow
{
    Q_OBJECT

public:
    explicit Podsumowanie_Tranzakcji(QWidget *parent = 0);
    ~Podsumowanie_Tranzakcji();
    bool open();
    void close();
    void setRezerwacja(std::shared_ptr<Rezerwacja> ptr);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    void reset();
    Ui::Podsumowanie_Tranzakcji *ui;
    std::shared_ptr<Rezerwacja> rezerwacja;
    std::shared_ptr<Lista_seans_miejsce> wybrane_miejsca;
    bool zamknij;
    void updateTabela();

signals:
    void closeWindow();
};

#endif // PODSUMOWANIE_TRANZAKCJI_H
