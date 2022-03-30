#include "employe.h"

employe::employe(int cin,QString nom,QString prenom,QString email,QString type,QString adresse)
{
      this->cin=cin;
      this->prenom=prenom;
      this->nom=nom;
      this->email=email;
    this->type=type;
    this->adresse=adresse;
}
bool employe::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("insert into EMPLOYE (CIN, NOM, PRENOM, EMAIL, TYPE, ADRESSE)" "values(:cin, :nom, :prenom, :email, :type, :adresse)");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":type",type);
    query.bindValue(":adresse",adresse);

    return query.exec();
}
QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe");


    return model;
}
bool employe::supprimer(int cin)
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("Delete from EMPLOYE where CIN= :cin");
    query.bindValue(":cin",res);

    return query.exec();
}
bool employe::modifier()
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("update  EMPLOYE set CIN = :cin, NOM = :nom, PRENOM = :prenom, EMAIL = :email, TYPE = :type, ADRESSE = :adresse where CIN =:cin");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":type",type);
    query.bindValue(":adresse",adresse);
    return query.exec();
}
QSqlQueryModel * employe::trier(QString type_tri, QString tri_par)
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe order by "+tri_par+" "+type_tri+"");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse"));

    return model;
}

QSqlQueryModel * employe::rechercher(QString cin )
{

     QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("select * from employe where (CIN LIKE '"+cin+"')  ") ;
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("type"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("adresse"));

      return model;
}
