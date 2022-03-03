#include "comptes.h"

Comptes::Comptes()
{

}
Comptes::Comptes(int Numero, QString Nom, QString Classe, QString Type,  QString Caract){
    this->Numero=Numero;
    this->Nom=Nom;
    this->Classe=Classe;
    this->Type=Type;
    this->Caract=Caract;
}
bool Comptes::ajouter(){
    QSqlQuery query;
    query.prepare("insert into Comptes values (:Numero, :Nom, :Classe, :Type, :Caract)");
    query.bindValue(":Numero", Numero);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Classe", Classe);
    query.bindValue(":Caract", Caract);
    query.bindValue(":Type", Type);
    return query.exec();
}
QSqlQueryModel * Comptes::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Caractéristiques"));
    return model;
}
bool Comptes::supprimer(int num){
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("delete from Comptes where N_COMPTE = :num");
    query.bindValue(":num", res);
    return query.exec();
}
bool Comptes::modifier(){
    QSqlQuery query;
    query.prepare("UPDATE Comptes set NOM_COMPTE = :Nom, CLASSE_COMPTE = :Classe, TYPE_COMPTE = :Type, CARACT_COMPTE = :Caract  WHERE N_COMPTE = :Numero");
    query.bindValue(":Numero", Numero);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Classe", Classe);
    query.bindValue(":Caract", Caract);
    query.bindValue(":Type", Type);
    return query.exec();
}
QSqlQueryModel * Comptes::trier(QString type){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes order by");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Caractéristiques"));
    QSqlQuery query;
    query.bindValue(":type", type);
    return model;
}
