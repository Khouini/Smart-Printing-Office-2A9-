#ifndef COMMANDE_H
#define COMMANDE_H

#include<QSqlQuery>
#include<QSqlQueryModel>

class commande
{
    int   id_commande , id_produit  , quantite , prix , id_client , Num_compte  ;

public:
    commande();
    commande(int,int,int,int,int,int) ;
    bool ajoutercommande() ;
    QSqlQueryModel * afficher() ;
    QSqlQueryModel * tri(QString,QString) ;
    QSqlQueryModel * rechercher(QString) ;
    bool supprimer(int) ;
    bool modifierclient() ;
    void printPDF_commande() ;
    void save_commande(QString ,QString ) ;
    QString load_commande() ;

};

#endif // COMMANDE_H
