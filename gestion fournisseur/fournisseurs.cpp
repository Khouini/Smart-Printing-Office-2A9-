#include "fournisseurs.h"

Fournisseurs::Fournisseurs()
{

}
Fournisseurs::Fournisseurs(int ID, int Num, QString Email, QString Produit, QString Date_Arrivee){
    this->ID=ID;
    this->Num=Num;
    this->Email=Email;
    this->Produit=Produit;
    this->Date_Arrivee=Date_Arrivee;
}
bool Fournisseurs::ajouter(){
    QSqlQuery query;
    QString res1 = QString::number(ID);
    QString res2 = QString::number(Num);
    query.prepare("insert into Fournisseurs values (:id, :num, :produit, :date_arrivee, :email)");
    query.bindValue(":id", res1);
    query.bindValue(":num", res2);
    query.bindValue(":email", Email);
    query.bindValue(":produit", Produit);
    query.bindValue(":date_arrivee", Date_Arrivee);
    return query.exec();
}
QSqlQueryModel* Fournisseurs::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from fournisseurs");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Numéro de téléphone"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Produit"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Date d'arrivée"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Email"));
    return model;
}
bool Fournisseurs::supprimer(int id){
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("delete from FOURNISSEURS where ID = :id");
    query.bindValue(":id", res);
    return query.exec();
}
bool Fournisseurs::modifier(){
    QSqlQuery query;
    QString res1 = QString::number(ID);
    QString res2 = QString::number(Num);
    query.prepare("update fournisseurs SET num_tel = :num, produit = :produit , date_arrivee = :date_arrivee, email = :email where id = :id");
    query.bindValue(":id", res1);
    query.bindValue(":num", res2);
    query.bindValue(":email", Email);
    query.bindValue(":produit", Produit);
    query.bindValue(":date_arrivee", Date_Arrivee);
    return query.exec();
}
