#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "employe.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(em.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_modifier_clicked()
{
    int cin=ui->lineEdit_5->text().toInt();
    QString nom=ui->lineEdit_6->text();
    QString prenom=ui->lineEdit_7->text();

    employe e(cin,nom,prenom);
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

    employe e(cin,nom,prenom);
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

