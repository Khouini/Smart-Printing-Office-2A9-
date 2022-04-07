#include "histo.h"
#include "techniciens.h"


#include <QSqlQuery>
#include <QtDebug>
#include<QSqlQueryModel>
#include <QString>

#include <QObject>
#include<QDate>

histo::histo()
{

}
histo::histo(QString b, int c)
 {
    operation=b;
    id=c;
 }

void histo::insert()
{
    QSqlQuery query;

    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");

    query.prepare("insert into HISTO(TYPE_OPERATION,ID_EMPLOYEE)" "values(sDate,:ID_EMPLOYEE)");
   query.bindValue(":operation",sDate);
   query.bindValue(":ID_EMPLOYEE",id);

 query.exec();
}
QSqlQueryModel * histo::Afficher( )
{
  QSqlQueryModel * model= new QSqlQueryModel();

       model->setQuery("select DATE_HISTO, TYPE_OPERATION, ID_EMPLOYEE from HISTO ;");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("date et heure"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Operation"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("ID_EMPLOYEE"));



 return model;
}
