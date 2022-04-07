#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "employe.h"
#include <QTranslator>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999,this));
    ui->tableView->setModel(em.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_modifier_clicked()
{
    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_adresse->text();
    QString email=ui->lineEdit_email->text();
    QString type;
    if(ui->radioButton->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2->isChecked()){
        type = "technicien";
    }

    employe e(cin,nom,prenom,adresse,type,email);
    e.save(cin,nom,prenom,adresse,type,email);
    bool test;
    test=e.modifier();

    if(test)
    {
         ui->tableView->setModel(em.afficher());//ref
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
void MainWindow::on_pushButton_ajouter_clicked()
{
    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_adresse->text();
    QString email=ui->lineEdit_email->text();
    QString type;
    if(ui->radioButton->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2->isChecked()){
        type = "technicien";
    }
    employe e(cin,nom,prenom,adresse,type,email);
    e.save(cin,nom,prenom,adresse,type,email);
    bool test;
    test=e.ajouter();
    if(test)
    {
         ui->tableView->setModel(em.afficher());//ref
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

void MainWindow::on_pushButton_supprimer_clicked()
{
    int cin=ui->lineEdit_cins->text().toInt();

    bool test;
    test=em.supprimer(cin);

    if(test)
    {
         ui->tableView->setModel(em.afficher());//ref
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

void MainWindow::on_pushButton_2_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if(ui->radioButton_5->isChecked()){
        type_of_tri = "asc";
    }
    if(ui->radioButton_6->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox->currentText();
    ui->tableView->setModel(em.trier(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_4_clicked()
{
    QString rech = ui->lineEdit_2->text() ;
    ui->tableView->setModel(em.rechercher(rech)) ;
}

void MainWindow::on_pushButton_clicked()
{
    if ("CLIENT20"  == ui->lineEdit_cin_3->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 20% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);    }
    else if ("EMPLOYE50"  == ui->lineEdit_cin_3->text()){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("remise de 50% effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if ("ADMIN100"  == ui->lineEdit_cin_3->text()){
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

void MainWindow::on_pushButton_3_clicked()
{
    QString lang;
    if(ui->radioButton_7->isChecked()){
        lang = "english";
    }
    if(ui->radioButton_8->isChecked()){
        lang = "frensh";
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_adresse->text();
    QString email=ui->lineEdit_email->text();
    QString type;
    if(ui->radioButton->isChecked()){
        type = "standard";
    }
    if(ui->radioButton_2->isChecked()){
        type = "technicien";
    }
    employe e(cin,nom,prenom,adresse,type,email);
        e.printPDF_employe();
}

void MainWindow::on_pushButton_7_clicked()
{
    QString link="file:///C:/Users/souay/OneDrive/Documents/untitled/test.pdf";
            QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_5_clicked()
{
    QString link="file:///C:/Users/souay/OneDrive/Documents/untitled/histo.txt";
            QDesktopServices::openUrl(QUrl(link));
}
