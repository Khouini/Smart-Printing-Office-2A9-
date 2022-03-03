#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "techniciens.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    int id=ui->lineEdit_idT->text().toInt();
    QString nom=ui->lineEdit_nomT->text();
    QString prenom=ui->lineEdit_prenomT->text();
    int cin=ui->lineEdit_cinT->text().toInt();
    int num=ui->lineEdit_numT->text().toInt();
    int idtache=ui->lineEdit_idtacheT->text().toInt();

    Techniciens T(id,nom,prenom,cin,num,idtache);

    bool test=T.ajouter();

    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_9_clicked()
{
   int id =ui->lineEdit_supp->text().toInt();
   bool test=Etmp.supprimer(id);

   if(test)
   {
       ui->tableView->setModel(Etmp.afficher());

       QMessageBox::information(nullptr,QObject::tr("OK"),
                                QObject::tr("Suppression effectuée\n"
                                            "Click cancel to exit."), QMessageBox::Cancel);
   }
   else
   {
       QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click cancel to exit."), QMessageBox::Cancel);
   }

}


void MainWindow::on_pushButton_Modifier_clicked()
{
    int id=ui->lineEdit_idT->text().toInt();
    QString nom=ui->lineEdit_nomT->text();
    QString prenom=ui->lineEdit_prenomT->text();
    int cin=ui->lineEdit_cinT->text().toInt();
    int num=ui->lineEdit_numT->text().toInt();
    int idtache=ui->lineEdit_idtacheT->text().toInt();

    Techniciens T(id,nom,prenom,cin,num,idtache);

    bool test=T.modifier();

    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("modification non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
    }


}
