#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "employe.h"

#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cinA->setValidator(new QIntValidator(0,99999,this));
    ui->tableViewA->setModel(em.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_modifierA_clicked()
{
    int cin=ui->lineEdit_cinA->text().toInt();
    QString nom=ui->lineEdit_nomA->text();
    QString prenom=ui->lineEdit_prenomA->text();
    QString adresse=ui->lineEdit_adresseA->text();
    QString email=ui->lineEdit_emailA->text();
    QString type;
    if(ui->radioButtonA->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2A->isChecked()){
        type = "technicien";
    }

    employe e(cin,nom,prenom,adresse,type,email);
    e.save(cin,nom,prenom,adresse,type,email);
    bool test;
    test=e.modifier();

    if(test)
    {
         ui->tableViewA->setModel(em.afficher());//ref
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("modification effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("modification non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pushButton_ajouterA_clicked()
{
    int cin=ui->lineEdit_cinA->text().toInt();
    QString nom=ui->lineEdit_nomA->text();
    QString prenom=ui->lineEdit_prenomA->text();
    QString adresse=ui->lineEdit_adresseA->text();
    QString email=ui->lineEdit_emailA->text();
    QString type;
    if(ui->radioButtonA->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2A->isChecked()){
        type = "technicien";
    }
    employe e(cin,nom,prenom,adresse,type,email);
    e.save(cin,nom,prenom,adresse,type,email);
    bool test;
    test=e.ajouter();
    if(test)
    {
         ui->tableViewA->setModel(em.afficher());//ref
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimerA_clicked()
{
    int cin=ui->lineEdit_cinsA->text().toInt();

    bool test;
    test=em.supprimer(cin);

    if(test)
    {
         ui->tableViewA->setModel(em.afficher());//ref
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Supression effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Supression non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_2A_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if(ui->radioButton_5A->isChecked()){
        type_of_tri = "asc";
    }
    if(ui->radioButton_6A->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBoxA->currentText();
    ui->tableViewA->setModel(em.trier(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_4A_clicked()
{
    QString rech = ui->lineEdit_2A->text() ;
    ui->tableViewA->setModel(em.rechercher(rech)) ;
}

void MainWindow::on_pushButtonA_clicked()
{
    if ("CLIENT20"  == ui->lineEdit_cin_3A->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 20% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);    }
    else if ("EMPLOYE50"  == ui->lineEdit_cin_3A->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 50% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if ("ADMIN100"  == ui->lineEdit_cin_3A->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 100% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("remise non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}



void MainWindow::on_pushButton_6A_clicked()
{
    int cin=ui->lineEdit_cinA->text().toInt();
    QString nom=ui->lineEdit_nomA->text();
    QString prenom=ui->lineEdit_prenomA->text();
    QString adresse=ui->lineEdit_adresseA->text();
    QString email=ui->lineEdit_emailA->text();
    QString type;
    if(ui->radioButtonA->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2A->isChecked()){
        type = "technicien";
    }
    employe e(cin,nom,prenom,adresse,type,email);
        e.printPDF_employe();
}

void MainWindow::on_pushButton_7A_clicked()
{
    QString link="file:///C:/Users/souay/OneDrive/Documents/untitled/test.pdf";
            QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_5A_clicked()
{
    QString link="file:///C:/Users/souay/OneDrive/Documents/untitled/histo.txt";
            QDesktopServices::openUrl(QUrl(link));
}
