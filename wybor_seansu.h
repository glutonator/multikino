#ifndef WYBOR_SEANSU_H
#define WYBOR_SEANSU_H

#include <QMainWindow>
#include "sprzedaz.h"
#include "lista_film.h"
#include "lista_seans.h"
#include "lista_wersja_filmu.h"
#include "lista_seans_miejsce.h"

namespace Ui {
class Wybor_seansu;
}

class Wybor_seansu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Wybor_seansu(QWidget *parent = 0);
    ~Wybor_seansu();
    bool open();
    void close();
    void setSprzedaz(std::shared_ptr<Sprzedaz> ptr);

signals:
    void closeWindow();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_filmBox_currentIndexChanged(const QString &arg1);

    void on_dataBox_currentIndexChanged(const QString &arg1);

    void on_godzinaBox_currentIndexChanged(const QString &arg1);

    void on_wersjaBox_currentIndexChanged(int index);

private:
    Ui::Wybor_seansu *ui;
    std::shared_ptr<Lista_film> lista_film;
    std::shared_ptr<Lista_wersja_filmu> lista_wersja_filmu;
    std::shared_ptr<Lista_seans> lista_seans;
    std::shared_ptr<Lista_seans_miejsce> lista_seans_miejsce;
    std::shared_ptr<Sprzedaz> sprzedaz;
    bool zamknij;
    void repertuar();
    void reset();
};

#endif // WYBOR_SEANSU_H
