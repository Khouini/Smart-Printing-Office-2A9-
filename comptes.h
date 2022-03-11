#ifndef COMPTES_H
#define COMPTES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Comptes
{
    int Numero;
    QString Nom, Classe, Type ,  Caract;
public:
    Comptes();
    Comptes(int, QString, QString, QString,  QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * trier(QString, QString);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * rechercheID(QString);
};

#endif // COMPTES_H
