#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include<QString>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[A-z]*"))) ;
    ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[A-z]*"))) ;
    ui->lineEdit_email->setValidator(new QRegExpValidator(QRegExp("[a-z]{1,10}@[a-z]{1,10}\\.[a-z]{1,4}"))) ;
    ui->lineEdit_id->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_cin->setValidator(new QIntValidator(0,19999999,this));
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
    // bool test2=C.controle_saisie_client(C) ;
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

void MainWindow::on_pushButton_2_clicked()
{
QString rech = ui->lineEdit_6->text() ;
ui->tableView->setModel(Etmp.rechercher(rech)) ;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString type ;
    QString attribut ;
    if (ui->radioButton_6->isChecked())
    {  type="asc" ; }
    if (ui->radioButton_7->isChecked())
    {  type="desc" ; }

    attribut = ui->comboBox->currentText();
    ui->tableView->setModel(Etmp.tri(type,attribut))  ;



}

