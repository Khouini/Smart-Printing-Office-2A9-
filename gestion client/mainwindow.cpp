#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher())  ;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    // recuperation des info saisies
    int id_client=ui->lineEdit_id->text().toInt();
    int cinn=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email=ui->lineEdit_email->text();
    QString sexe;
    QString type_client;
    if (ui->radioButtonHomme->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_Femme->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIP->isChecked()){
        type_client = "VIP";
    }
    if (ui->radioButton_Fidel->isChecked()){
        type_client = "Fidéle";
    }
    if (ui->radioButton_passagee->isChecked()){
        type_client = "Passager";
    }
    // objet client
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    bool test= C.ajouterclient();
    if(test)   // si requete executée
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajouter effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("ajouter NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id =ui->lineEdit_supprimer_2->text().toInt() ;
    bool test= Etmp.supprimer(id);
    if(test)   // si requete executée
    {
        ui->tableView->setModel(Etmp.afficher());
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

void MainWindow::on_pushButton_modifier_clicked()
{
    // recuperation des info saisies
    int id_client=ui->lineEdit_id->text().toInt();
    int cinn=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email=ui->lineEdit_email->text();
    QString sexe;
    QString type_client;
    if (ui->radioButtonHomme->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_Femme->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIP->isChecked()){
        type_client = "VIP";
    }
    if (ui->radioButton_Fidel->isChecked()){
        type_client = "Fidéle";
    }
    if (ui->radioButton_passagee->isChecked()){
        type_client = "Passager";
    }
    // objet client
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    bool test= C.modifierclient();
    if(test)   // si requete executée
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("modification effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("modification NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

}
}
