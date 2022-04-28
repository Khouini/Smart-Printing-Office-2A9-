#include "commande.h"

commande::commande()
{

}
commande::commande(int id_commande ,int id_produit,int quantite,int prix,int id_client,int Num_compte)
{
   this->id_commande=id_commande;
   this->id_produit=id_produit;
   this->quantite=quantite;
   this->prix=prix;
   this->id_client=id_client;
   this->Num_compte=Num_compte;

}
bool commande::ajoutercommande()
{

    commande c ;
    QSqlQuery query ;
  //insertion
    query.prepare("insert into COMMANDES values (:ID_COMMANDE, :ID_PRODUIT, :QUANTITE_PRODUIT, null , :PRIX_PRODUIT,:ID_CLIENT , :N_COMPTE, NULL )");
    //creations des variables liee
    query.bindValue(":ID_COMMANDE",id_commande) ;
    query.bindValue(":ID_PRODUIT",id_produit) ;
    query.bindValue(":QUANTITE_PRODUIT",quantite) ;
    query.bindValue(":PRIX_PRODUIT",prix) ;
    query.bindValue(":ID_CLIENT ",id_client) ;
    query.bindValue(":N_COMPTE",Num_compte) ;




    //exec
    return query.exec() ;

}

