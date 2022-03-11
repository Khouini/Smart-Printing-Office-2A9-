#ifndef TECHNICIENS_H
#define TECHNICIENS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class Techniciens
{
    QString nom, prenom;
    int id,cin,num,idtache;
public:
    Techniciens(){}
    Techniciens(int,QString,QString,int,int,int);

    int getid(){return id;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    int getcin(){return cin;}
    int getnum(){return num;}
    int getidtache(){return idtache;}


    void setid(int id ){this->id=id;}
    void setnom(QString n){nom=n;}
    void setprenom(QString p){prenom=p;}
    void setcin(int cin){this->cin=cin;}
    void setnum(int num){this->num=num;}
    void setidtache(int idtache){this->idtache=idtache;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tri_id();
    QSqlQueryModel * tri_nom();

    QSqlQueryModel * recherche(QString);

};

#endif // TECHNICIENS_H
