#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewAffichage->setModel(FRN.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    int num = ui->lineEdit_tel->text().toInt();
    QString email = ui->lineEdit_email->text();
    QString produit = ui->lineEdit_produit->text();
    QString date_arrivee = ui->lineEdit_email_2->text();
    Fournisseurs F(id, num, email, produit, date_arrivee);
    bool test = F.ajouter();

    if (test){
        ui->tableViewAffichage->setModel(FRN.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    int id = ui->lineEdit_id_suppression->text().toInt();
    bool test = FRN.supprimer(id);

    if (test){
        ui->tableViewAffichage->setModel(FRN.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    int num = ui->lineEdit_tel->text().toInt();
    QString email = ui->lineEdit_email->text();
    QString produit = ui->lineEdit_produit->text();
    QString date_arrivee = ui->lineEdit_email_2->text();
    Fournisseurs F(id, num, email, produit, date_arrivee);
    bool test = F.modifier();

    if (test){
        ui->tableViewAffichage->setModel(FRN.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Modification effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}
