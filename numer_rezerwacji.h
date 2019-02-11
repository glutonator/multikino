#ifndef NUMER_REZERWACJI_H
#define NUMER_REZERWACJI_H

#include <QMainWindow>
#include <memory>
#include <rezerwacja.h>

namespace Ui {
class Numer_Rezerwacji;
}

class Numer_Rezerwacji : public QMainWindow
{
    Q_OBJECT

public:
    explicit Numer_Rezerwacji(QWidget *parent = 0);
    ~Numer_Rezerwacji();
    bool open();
    void close();
    void setRezerwacja(std::shared_ptr<Rezerwacja> ptr);

private:
    void reset();
    Ui::Numer_Rezerwacji *ui;
    std::shared_ptr<Rezerwacja> rezerwacja;
    bool zamknij;

signals:
    void closeWindow();
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // NUMER_REZERWACJI_H
