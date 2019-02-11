#include "panel_biletomat.h"
#include <QApplication>
#include <QSqlQuery>
#include <QDebug>
#include "baza_danych.h"
#include "kino.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Panel_Biletomat w;
    w.show();

    return a.exec();
}
