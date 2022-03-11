#include "techniciens.h"

Techniciens::Techniciens(int id,QString nom,QString prenom,int cin,int num,int idtache)
  {

    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->cin=cin;
    this->num=num;
    this->idtache=idtache;
}

bool Techniciens::ajouter()

{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("insert into techniciens values (:id,:nom,:prenom,:cin,:num,:idtache)");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":cin",cin);
    query.bindValue(":num",num);
    query.bindValue(":idtache",idtache);

    return query.exec();
}

QSqlQueryModel * Techniciens::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from techniciens");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("idtache"));

    return  model;

}

bool Techniciens::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("Delete from techniciens where ID= :id");
    query.bindValue(":id",res);
    return  query.exec();
}
bool Techniciens::modifier()

{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("update techniciens set nom = :nom, prenom = :prenom, cin = :cin, num = :num, idtache = :idtache where id = :id ");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":cin",cin);
    query.bindValue(":num",num);
    query.bindValue(":idtache",idtache);

    return query.exec();
}
QSqlQueryModel * Techniciens:: tri_id()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from Techniciens order by id" );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("idtache")) ;

    return model ;

}

QSqlQueryModel * Techniciens:: tri_nom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from Techniciens order by nom" );
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID")) ;
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom")) ;
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom")) ;
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("num")) ;
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("idtache")) ;

    return model ;

}


QSqlQueryModel * Techniciens::recherche(QString rech)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from TECHNICIENS where id LIKE '%"+rech+"%'");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("idtache"));
    return  model ;

 }
