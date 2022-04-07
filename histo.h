#ifndef HISTO_H
#define HISTO_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class histo
{
private:
    QString operation;
    int id;


public:
    histo();
    histo(QString, int);
    QSqlQueryModel * Afficher( );


};
#endif // HISTO_H
