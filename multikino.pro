#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T23:06:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multikino
TEMPLATE = app


SOURCES += main.cpp\
        panel_biletomat.cpp \
    kino.cpp \
    sala_kinowa.cpp \
    miejsce.cpp \
    skanowanie_karty.cpp \
    wybor_seansu.cpp \
    wybor_miejsc.cpp \
    baza_danych.cpp \
    sprzedaz.cpp \
    kategoria.cpp \
    film.cpp \
    wersja_filmu.cpp \
    seans.cpp \
    seans_miejsce.cpp \
    klient.cpp \
    rodzaj_znizki.cpp \
    czas_znizki.cpp \
    lista_film.cpp \
    lista_wersja_filmu.cpp \
    lista_seans.cpp \
    lista_seans_miejsce.cpp \
    numer_rezerwacji.cpp \
    numer_zamowienia.cpp \
    podsumowanie_tranzakcji.cpp \
    rezerwacja.cpp \
    skanowanie_karty_2.cpp \
    system_platnosci.cpp

HEADERS  += panel_biletomat.h \
    kino.h \
    sala_kinowa.h \
    miejsce.h \
    skanowanie_karty.h \
    wybor_seansu.h \
    wybor_miejsc.h \
    baza_danych.h \
    sprzedaz.h \
    kategoria.h \
    film.h \
    wersja_filmu.h \
    seans.h \
    seans_miejsce.h \
    klient.h \
    rodzaj_znizki.h \
    czas_znizki.h \
    lista_film.h \
    lista_wersja_filmu.h \
    lista_seans.h \
    lista_seans_miejsce.h \
    numer_rezerwacji.h \
    numer_zamowienia.h \
    podsumowanie_tranzakcji.h \
    rezerwacja.h \
    skanowanie_karty_2.h \
    system_platnosci.h

FORMS    += panel_biletomat.ui \
    skanowanie_karty.ui \
    wybor_seansu.ui \
    wybor_miejsc.ui \
    numer_rezerwacji.ui \
    numer_zamowienia.ui \
    podsumowanie_tranzakcji.ui \
    skanowanie_karty_2.ui \
    system_platnosci.ui
