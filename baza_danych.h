#ifndef BAZA_DANYCH_H
#define BAZA_DANYCH_H
#include <QSqlDatabase>
#include <QSqlQuery>
class Baza_danych
{
public:
    static Baza_danych getInstance();
    const QSqlDatabase& getDb() const;
    void open();
    void close();
private:
    Baza_danych();
    QSqlDatabase db;
};

#endif // BAZA_DANYCH_H
