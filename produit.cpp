#include "produit.h"
#include<QSqlQueryModel>
#include <QRegExpValidator>
#include <QDesktopServices>
#define NOM_RX "^([a-z]+[,.]?[ ]?|[a-z]+['-]?)+$"

produit::produit(int id_produit,QString nom_produit,QString reference_produit,QString type,QString marque  )
{


    this ->id_produit=id_produit;
    this->nom_produit=nom_produit;
    this->reference_produit=reference_produit;
     this ->type=type;
     this ->marque=marque;



}
bool produit::ajouter()
{QSqlQuery query;
    QString res = QString::number(id_produit);
    //prepare() prend la requete en parametre pour la preparer a léxéxution
    query.prepare("insert into produit(id_produit,nom_produit,reference_produit,type,marque)""values(:id_produit, :nom_produit, :reference,:type,:marque)");
//Creation des variables liees
    query.bindValue(":id_produit",res);
    query.bindValue(":nom_produit",nom_produit);
    query.bindValue(":reference",reference_produit);
    query.bindValue(":type",type);
    query.bindValue(":marque",marque);
    return query.exec();//exec() envoie la requéte pour léxecuter
}

QSqlQueryModel * produit::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from produit ") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_produit")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("reference_produit")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("type")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("marque")) ;
    return model ;

}
bool produit::supprimer(int id_produit)
{
    QSqlQuery query ;
    QString res = QString::number(id_produit) ;
    query.prepare("Delete from produit where id_produit=:id_produit") ;
    query.bindValue(":id_produit",res) ;
    return query.exec() ;

}
bool produit::modifier(int id_produit)
{
QSqlQuery query;
QString res= QString::number(id_produit);
query.prepare("Update produit set id_produit = :id_produit , nom_produit = :nom_produit , reference_produit = :reference_produit , type = :type , marque = :marque  where id_produit = :id_produit ");
query.bindValue(":id_produit",res);
query.bindValue(":nom_produit",nom_produit);
query.bindValue(":reference_produit",reference_produit);
query.bindValue(":type",type);
query.bindValue(":marque",marque);
return    query.exec();
}

QSqlQueryModel * produit :: trie_produitN()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from produit order by nom_produit DESC" );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_produit")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("reference_produit")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("type")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("marque")) ;
    return model ;


}

QSqlQueryModel * produit:: trie_produitQ()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from produit order by id_produit" );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_produit")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_produit")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("reference_produit")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("type")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("marque")) ;
    return model ;

}

QSqlQueryModel * produit::recherche(QString rech)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from produit where id_produit LIKE '%"+rech+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("id_produit"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom_produit"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("reference_produit"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("marque"));

    return  model ;

 }

