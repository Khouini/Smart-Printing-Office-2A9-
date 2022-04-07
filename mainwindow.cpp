#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include "ajout.h"
#include <QtWidgets/QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include<QSqlError>
#define NOM_RX "^([a-z]*|[A-Z]*)+$"
#include "camera.h"
#include <QQuickItem>


QRegExp rxNom(NOM_RX);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    //map***************
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
    connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

    emit setCenter(25.000, 50.000);
    emit addMarker(25.000, 50.000);
  ui->tableView->setModel(pro.afficher())  ;//afficher
    ui->lineEdit_id->setValidator(new QIntValidator(0,99999,this));
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);
    ui->lineEdit_nom->setValidator(valiNom);//nomajoutproduit//

    ui->marque->setValidator(valiNom);
    ui->lineEdit_reference->setValidator(valiNom);

    ui->type->setValidator(valiNom);

    }

MainWindow::~MainWindow()
{
    delete ui;

}



void MainWindow::on_pushButton_10_clicked()
{


    int id_produit=ui->lineEdit_id->text().toInt();
    QString nom_produit=ui->lineEdit_nom->text();
    QString reference_produit =ui ->lineEdit_reference->text();
     QString type =ui ->type->text();
      QString marque =ui ->marque->text();
       QString qte =ui ->qte->text();
produit p(id_produit,nom_produit,reference_produit,type,marque,qte);
// fel fonction ajoutt
p.save(id_produit,nom_produit,reference_produit,type,marque,qte);
bool test= p.ajouter();


if (test)
{
 //   QMessageBox msg;
 //   msg.setWindowTitle("Error");
 //   msg.setIcon(QMessageBox::Critical);
 //   msg.setText("Error: Something went wrong!");
 //   msg.exec();
    ui->tableView->setModel(pro.afficher());

QMessageBox::information(nullptr,QObject::tr("ok"),
                         QObject::tr("ajouter effectué\n"
                                     "Click cancel to exit."),
                        QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("ajouter NON effectué\n"
                                         "Click cancel to exit."),
                            QMessageBox::Cancel);




}

void MainWindow::on_stock_clicked()
{

        produit p;
     QString qnt=ui->qte->text();
   //int qnt;
    bool test;
    QSqlQuery qry;

    qry.prepare("select qte from produit  where  qte = "+qnt+" ");
    if (qry.exec()){
        while (qry.next()){
            qnt = (qry.value(0).toInt());
            if (qnt > 10){
                test = true;
            }else{
                test = false;
            }
        }
    }
        QMessageBox msgbox;
        if (test){
                ui->tableView->setModel(pro.afficher());
                QMessageBox::information(nullptr, QObject::tr("***alert stock***"),
                                      QObject::tr("Ce Produit est encore en stock"),
                                      QMessageBox::Ok
                                      );
            }else{
                QMessageBox::critical(nullptr, QObject::tr("***alert stock***"),
                                      QObject::tr("Ce Produit nest plus en stock (stock<10)"),
                                      QMessageBox::Cancel
                                      );
            }
    }









/*

    //QString test2="55";
     //int id_produit=ui->lineEdit_id->text().toInt();
    produit p;
      bool test= p.alert();
    if (test)
    {
        QMessageBox msg;
      // msg.setWindowTitle("Error");
       // msg.setIcon(QMessageBox::Critical);
       // msg.setText("Error: Something went wrong!");
       //msg.exec();
        ui->tableView->setModel(pro.afficher());
    QMessageBox::information(nullptr,QObject::tr("ok"),
                             QObject::tr("stock effectué\n"
                                         "Click cancel to exit."),
                            QMessageBox::Cancel);



}
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("stock NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
                                */







void MainWindow::on_pushButton_supprimer_clicked()
{
    int id =ui->lineEdit_supprimer_3->text().toInt() ;
    bool test= pro.supprimer(id);
    if(test)   // si requete executée
    {
        ui->tableView->setModel(pro.afficher());

        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("suppression effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else  {

        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("suppression NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

          }
}



void MainWindow::on_pushButton_11_clicked()
{
    {

        //

        int id_produit=ui->lineEdit_id->text().toInt();
        QString nom_produit=ui->lineEdit_nom->text();
        QString reference_produit =ui ->lineEdit_reference->text();
         QString type =ui ->type->text();
          QString marque =ui ->marque->text();
          QString qte =ui ->qte->text();
          produit p(id_produit,nom_produit,reference_produit,type,marque,qte);



      bool test=p.modifier(id_produit);
      if(test)
    {
         ui->tableView->setModel(pro.afficher());
      //refresh
    QMessageBox::information(nullptr, QObject::tr("modifier une agence"),
                      QObject::tr("Agence modifié.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("modifier une agence"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

void MainWindow::on_radioButton_TRInProd_clicked()
{

         ui->tableView->setModel((pro.trie_produitN()));

}

void MainWindow::on_radioButton_TRIqProd_clicked()
{
  ui->tableView->setModel(pro.trie_produitQ());
}




void MainWindow::on_pushButton_3_clicked()
{
    QString rech= ui->lineEdit_7->text();
    ui->tableView->setModel(pro.recherche(rech));

}

void MainWindow::on_pushButton_clicked()
{
    QString link="file:///C:/Users/dell/Desktop/stock/histo.txt";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_4_clicked()
{


        int id_produit=ui->lineEdit_id->text().toInt();
        QString nom_produit=ui->lineEdit_nom->text();
        QString reference_produit =ui ->lineEdit_reference->text();
         QString type =ui ->type->text();
          QString marque =ui ->marque->text();
           QString qte =ui ->qte->text();
       produit p(id_produit,nom_produit,reference_produit,type,marque,qte);
    p.printPDF_produit();
}



void MainWindow::on_tableView_activated(const QModelIndex &index)
{



        QSqlQuery query  ;
       QString id_produit=ui->tableView->model()->data(index).toString() ;
        query.prepare("select * from produit where (id_produit LIKE '"+id_produit+"')") ;
        if (query.exec())
        {
            while (query.next()) {

                ui->lineEdit_id->setText(query.value(0).toString()) ;
                ui->lineEdit_nom->setText(query.value(1).toString()) ;
                ui->lineEdit_reference->setText(query.value(2).toString()) ;
                ui->type->setText(query.value(3).toString()) ;
                ui->marque->setText(query.value(4).toString()) ;
                ui->qte->setText(query.value(5).toString()) ;
            }
        }
            else {
                 QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
                   }

}

void MainWindow::on_cam_clicked()
{

}

void MainWindow::on_pushButton_5_clicked()
{

        QString link="file:///C:/Users/dell/Desktop/stock/produit.pdf";
        QDesktopServices::openUrl(QUrl(link));

}
