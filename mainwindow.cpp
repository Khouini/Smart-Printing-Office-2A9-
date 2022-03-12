#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_voir_pj.h"
#include "comptes.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewComptes->setModel(Cmpt.afficher());
    ui->lineEdit_Numero_Compte->setValidator(new QIntValidator (0, 999, this));
    ui->lineEdit_Suppression_ID->setValidator(new QIntValidator (0, 999, this));
    ui->lineEdit_Nom_Compte->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->lineEdit_Classe_Compte->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->lineEdit_Recherche->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Dialog_Voir_PJ Voir_PJ;
    Voir_PJ.exec();
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    QString Type;
    int Numero = ui->lineEdit_Numero_Compte->text().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    QString Classe = ui->lineEdit_Classe_Compte->text();
    QString Caract = ui->plainTextEdit_Caracteristiques_Compte->toPlainText();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
        Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, Caract);
    bool test = C.ajouter();

    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
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
    int id = ui->lineEdit_Suppression_ID->text().toInt();
    bool test = Cmpt.supprimer(id);

    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
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
    QString Type;
    int Numero = ui->lineEdit_Numero_Compte->text().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    QString Classe = ui->lineEdit_Classe_Compte->text();
    QString Caract = ui->plainTextEdit_Caracteristiques_Compte->toPlainText();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
    Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, Caract);
    bool test = C.modifier();

    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
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

void MainWindow::on_pushButton_Chercher_clicked()
{
    QString rech_field = ui->lineEdit_Recherche->text();
    ui->tableViewComptes->setModel(Cmpt.recherche(rech_field));
}

void MainWindow::on_pushButton_Trier_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri->currentText();
    ui->tableViewComptes->setModel(Cmpt.trier(type_of_tri, tri_par));

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableViewComptes->setModel(Cmpt.afficher());

}

void MainWindow::on_pushButton_Chercher_2_clicked()
{
    QString rech_field = ui->lineEdit_ID_RECH_2->text();
    ui->tableViewComptes->setModel(Cmpt.recherche(rech_field));
}

void MainWindow::on_tableViewComptes_activated(const QModelIndex &index)
{
    QString val = ui->tableViewComptes->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from Comptes where (N_COMPTE) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            ui->lineEdit_Numero_Compte->setText(query.value(0).toString());
            ui->lineEdit_Suppression_ID->setText(query.value(0).toString());
            ui->lineEdit_Nom_Compte->setText(query.value(1).toString());
            ui->lineEdit_Classe_Compte->setText(query.value(2).toString());
            ui->plainTextEdit_Caracteristiques_Compte->setPlainText(query.value(4).toString());
            if ((query.value(3).toString()) == "Actif"){
                ui->radioButton_Type_Actif->setChecked(1);
            }
            if ((query.value(3).toString()) == "Passif"){
                ui->radioButton_Type_Passif->setChecked(1);
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}
