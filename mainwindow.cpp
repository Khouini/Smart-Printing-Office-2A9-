#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include "ajout.h"
#include <QtWidgets/QMessageBox>
#define NOM_RX "^([a-z]*|[A-Z]*)+$"
QRegExp rxNom(NOM_RX);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_id->setValidator(new QIntValidator(0,99999,this));
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);
    ui->lineEdit_nom->setValidator(valiNom);//nomajoutproduit//

    ui->marque->setValidator(valiNom);
    ui->lineEdit_reference->setValidator(valiNom);
    ui->qte->setValidator(valiNom);
    ui->type->setValidator(valiNom);




    ui->tableView->setModel(pro.afficher())  ;//afficher


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
produit p(id_produit,nom_produit,reference_produit,type,marque);
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






void MainWindow::on_pushButton_supprimer_clicked()
{
    int id =ui->lineEdit_supprimer_2->text().toInt() ;
    bool test= pro.supprimer(id);
    if(test)   // si requete executée
    {
        ui->tableView->setModel(pro.afficher());
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
          produit p(id_produit,nom_produit,reference_produit,type,marque);



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
    QString rech= ui->lineEdit_id->text();
    ui->tableView->setModel(pro.recherche(rech));
}
