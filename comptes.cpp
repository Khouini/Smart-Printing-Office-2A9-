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
    query.prepare("insert into Comptes values (:Numero, :Nom, :Classe, :Type, :Caract, NULL, NULL)");
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
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("ID User"));

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

QSqlQueryModel * Comptes::trier(QString type_tri, QString tri_par){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes order by "+tri_par+" "+type_tri+" ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Caractéristiques"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("ID User"));
    return model;
}
QSqlQueryModel * Comptes::recherche(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes where  (N_COMPTE) LIKE '%"+rech+"%' OR (NOM_COMPTE) LIKE '%"+rech+"%' OR (CLASSE_COMPTE) LIKE '%"+rech+"%' OR (TYPE_COMPTE) LIKE '%"+rech+"%' OR (CARACT_COMPTE) LIKE '%"+rech+"%' ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Caractéristiques"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("ID User"));
    return model;
}
QSqlQueryModel * Comptes::rechercheID(QString rech){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from Comptes where (N_COMPTE) LIKE "+rech+" ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Numéro"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Classe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Caractéristiques"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Solde"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("ID User"));
    return model;
}
