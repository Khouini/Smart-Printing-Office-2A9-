#include "employe.h"

employe::employe(int cin,QString nom,QString prenom)
{
      this->cin=cin;
      this->prenom=prenom;
      this->nom=nom;
}
bool employe::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(cin);
    query.prepare("insert into EMPLOYE (CIN, NOM, PRENOM)" "values(:cin, :nom, :prenom)");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);

    return query.exec();
}
QSqlQueryModel * employe::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from employe");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));

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
    query.prepare("update  EMPLOYE set CIN = :cin, NOM = :nom, PRENOM = :prenom where CIN =:cin");
    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);

    return query.exec();
}
