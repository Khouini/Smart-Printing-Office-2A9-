#include "client.h"
#include "mainwindow.h"

client::client()
{

}
client::client(QString nom ,QString prenom ,QString email,QString sexe,QString type_client,int idclient,int cinn)
{
   this->nom=nom;
   this->prenom=prenom;
   this->email=email;
   this->sexe=sexe;
   this->type_client=type_client;
   this->idclient=idclient;
   this->cinn=cinn;

}
bool client::ajouterclient()
{
    client c ;
    QSqlQuery query ;
    QString res1 = QString::number(idclient) ;
    QString res2 = QString::number(cinn) ;

    //insertion
    query.prepare("insert into CLIENTS values (:idclient, :nom , :prenom, :email, :cinn,:sexe , :type_client, NULL )");
    //creations des variables liee
    query.bindValue(":idclient",res1) ;
    query.bindValue(":nom",nom) ;
    query.bindValue(":prenom",prenom) ;
    query.bindValue(":email",email) ;
    query.bindValue(":cinn",res2) ;
    query.bindValue(":type_client",type_client) ;
    query.bindValue(":sexe",sexe) ;



    //exec
    return query.exec() ;


    }
QSqlQueryModel * client::tri(QString type , QString attribut)
{
   QSqlQueryModel * model=new QSqlQueryModel() ;
   model->setQuery("select * from CLIENTS order by "+attribut+" "+type+" ") ;
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Client")) ;
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom")) ;
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom")) ;
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email")) ;
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cin")) ;
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe")) ;
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type")) ;
   return model ;

}
QSqlQueryModel *client::rechercher(QString id )
{

     QSqlQueryModel *model=new QSqlQueryModel();
     model->setQuery("select * from CLIENTS where (ID_CLIENT LIKE '"+id+"')  ") ;
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Client")) ;
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom")) ;
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom")) ;
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email")) ;
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cin")) ;
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe")) ;
     model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type")) ;

      return model;
}


bool client::controle_saisie_client(client c)
{
    if ((c.getcinn()==0) || (c.getidclient()==0) || (c.getnom()=="") || (c.getprenom()==""))
        return true ;
    else return  false ;

}
QSqlQueryModel * client::afficher()
{
   QSqlQueryModel * model=new QSqlQueryModel() ;
   model->setQuery("select * from CLIENTS ") ;
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_Client")) ;
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom")) ;
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom")) ;
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email")) ;
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cin")) ;
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("Sexe")) ;
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("Type")) ;
   return model ;

}

bool client::supprimer(int idclient)
{
    QSqlQuery query ;
    QString res = QString::number(idclient) ;
    query.prepare("Delete from CLIENTS where ID_CLIENT=:idclient") ;
    query.bindValue(":idclient",res) ;
    return  query.exec() ;


}
bool client::modifierclient(){
    QSqlQuery query ;
    QString res1 = QString::number(idclient) ;
    QString res2 = QString::number(cinn) ;
    //insertion
    query.prepare("update CLIENTS set nom_client = :nom, prenom_client = :prenom, email_client = :email, cin_client = :cinn, sexe_client = :sexe , type_client =  :type_client where id_client = :idclient;");
    //creations des variables liee
    query.bindValue(":idclient",res1) ;
    query.bindValue(":nom",nom) ;
    query.bindValue(":prenom",prenom) ;
    query.bindValue(":email",email) ;
    query.bindValue(":cinn",res2) ;
    query.bindValue(":type_client",type_client) ;
    query.bindValue(":sexe",sexe) ;


    //exec
    return query.exec() ;
}




