#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class employe
{
private:
    QString nom, prenom;
    int cin;
public:
    employe(){}
    employe(int,QString,QString);

    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getcin(){return cin;}

    void settnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setcin(int c){cin=c;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
};

#endif // EMPLOYE_H
