#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comptes.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlError>
#include "gestioncommandes.h"
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QDesktopServices>

#include "historique.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewComptes->setModel(Cmpt.afficher());
    ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
    ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
    ui->comboBox_Commandes_id->setModel(GC1.afficherComboBoxCommandes());
    ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
    ui->comboBox_n_compte->setModel(GC1.afficherComboBoxCompte2());
    ui->comboBox_pdf_id->setModel(Cmpt.afficherIdPDFComboBox());
    ui->lineEdit_Numero_Compte->setValidator(new QIntValidator (0, 999, this));
    ui->lineEdit_Suppression_ID->setValidator(new QIntValidator (0, 999, this));
    ui->lineEdit_Nom_Compte->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->lineEdit_Classe_Compte->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->lineEdit_Recherche->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->tableViewHistorique->setModel(H.Afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Ajouter_clicked()
{
    QString Type;
    int Numero = ui->lineEdit_Numero_Compte->text().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    QString Classe = ui->lineEdit_Classe_Compte->text();
    float solde= ui->lineEdit_Solde->text().toFloat();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
        Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, solde);
    bool test = C.ajouter();

    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
        ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
        //Historique
        QString operation = "Ajout";
        Historique h(operation, Numero, Nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());
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
    QString Nom = ui->lineEdit_Nom_Compte->text();
    bool test = Cmpt.supprimer(id);
    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
        ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
        ui->tableViewHistorique->setModel(H.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
        //Historique
        QString operation = "Suppression";
        Historique h(operation, id, Nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());
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
    float solde= ui->lineEdit_Solde->text().toFloat();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
    Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, solde);
    bool test = C.modifier();

    if (test){
        ui->tableViewComptes->setModel(Cmpt.afficher());
        ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Modification effectué"),
                              QMessageBox::Ok
                              );
        //Historique
        QString operation = "Modification";
        Historique h(operation, Numero, Nom);
        h.Ajouter();
        ui->tableViewHistorique->setModel(H.Afficher());
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
            ui->comboBox_pdf_id->setCurrentText(query.value(0).toString());
            ui->lineEdit_Suppression_ID->setText(query.value(0).toString());
            ui->lineEdit_Nom_Compte->setText(query.value(1).toString());
            ui->lineEdit_Classe_Compte->setText(query.value(2).toString());
            ui->lineEdit_Solde->setText(query.value(4).toString());
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

void MainWindow::on_pushButton_actualier_2_clicked()
{
    ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
    ui->comboBox_Commandes_id->setModel(GC1.afficherComboBoxCommandes());
    ui->comboBox_compte_id->setModel(GC1.afficherComboBoxCompte());
    ui->comboBox_pdf_id->setModel(Cmpt.afficherIdPDFComboBox());
}

void MainWindow::on_pushButton_valider_etablissement_clicked()
{
    int id_compte = ui->comboBox_compte_id->currentText().toUInt();
    int id_commande = ui->comboBox_Commandes_id->currentText().toInt();
    GestionCommandes GC(id_compte, id_commande);
    bool test = GC.EtablirCompte();

    if (test){
        ui->tableViewCommande1->setModel(GC1.afficherCommandes1());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("etablir effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("etablir non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void MainWindow::on_pushButton_afficher_PJ_clicked()
{
    QString val = ui->lineEdit_id_commande->text();
    QSqlQuery query;
    query.prepare("select PJ from Commandes where (id_commande) LIKE "+val+" ");
    QString fichier_PJ;
    QString X;
    if (query.exec()){
        while (query.next()){
            fichier_PJ = query.value(0).toString();
            X = "D:\\Documents\\GitHub\\Gestion-Fiance-Qt\\PJ\\"+fichier_PJ ;
            QFile file (X);
            if(!file.open(QIODevice::ReadOnly)){
                QMessageBox::information(0, "info", file.errorString());
            }else{
                QTextStream in(&file);
                QMessageBox::about(this, tr("Piéce Justificative"), in.readAll());
            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_tableViewCommande1_activated(const QModelIndex &index)
{
    QString val = ui->tableViewCommande1->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select id_commande from commandes where (id_commande) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            ui->lineEdit_id_commande->setText(query.value(0).toString());
            ui->comboBox_Commandes_id->setCurrentText(query.value(0).toString());
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButton_Trier_2_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc_2->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc_2->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri_2->currentText();
    ui->tableViewCommande1->setModel(GC1.trierCommandes1(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_Chercher_3_clicked()
{
    QString rech_field = ui->lineEdit_Recherche_2->text();
    ui->tableViewCommande1->setModel(GC1.recherche1(rech_field));
}

void MainWindow::on_pushButton_Trier_3_clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc_3->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc_3->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri_3->currentText();
    ui->tableViewCommandes_2->setModel(GC1.trierCommandes2(type_of_tri, tri_par));
}

void MainWindow::on_pushButton_Chercher_4_clicked()
{
    QString rech_field = ui->lineEdit_Recherche_3->text();
    ui->tableViewCommandes_2->setModel(GC1.recherche2(rech_field));
}

void MainWindow::on_pushButton_actualier_3_clicked()
{
    ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
    ui->comboBox_n_compte->setModel(GC1.afficherComboBoxCompte2());
}

void MainWindow::on_pushButton_valider_compta_clicked()
{
    QString montant = ui->lineEdit_montant->text();
    QString nCompte = ui->comboBox_n_compte->currentText();
    QString compta_type;
    if (ui->radioButton_crediter->isChecked()){
        compta_type = "+";
    }
    if (ui->radioButton_debiter->isChecked()){
        compta_type = "-";
    }
    QSqlQuery query;
    query.prepare("update comptes set solde_compte = solde_compte "+compta_type+" "+montant+" where n_compte like "+nCompte+" ");
    if (query.exec()){
            ui->tableViewCommandes_2->setModel(GC1.afficherCommandes2());
            QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                  QObject::tr("Manipulation effectué"),
                                  QMessageBox::Ok
                                  );
        }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_tableViewCommandes_2_activated(const QModelIndex &index)
{
    QString val = ui->tableViewCommandes_2->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select n_compte from commandes where (n_compte) LIKE "+val+" ");
    if (query.exec()){
        while (query.next()){
            ui->comboBox_n_compte->setCurrentText(query.value(0).toString());
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
}

void MainWindow::on_pushButtonActualiserHistorique_clicked()
{
    ui->tableViewHistorique->setModel(H.Afficher());
}

void MainWindow::on_pushButton_clicked()
{
    QString Type;
    int Numero = ui->comboBox_pdf_id->currentText().toInt();
    QString Nom = ui->lineEdit_Nom_Compte->text();
    QString Classe = ui->lineEdit_Classe_Compte->text();
    float solde= ui->lineEdit_Solde->text().toFloat();
    if (ui->radioButton_Type_Actif->isChecked()){
        Type = "Actif";
    }
    if (ui->radioButton_Type_Passif->isChecked()){
        Type = "Passif";
    }
    Comptes C(Numero, Nom, Classe, Type, solde);
    C.printPDF_comptes() ;

}

void MainWindow::on_pushButton_afficher_pdf_clicked()
{
    QString link="file:///D:/Documents/GitHub/Gestion-Fiance-Qt/comptes.pdf";
            QDesktopServices::openUrl(QUrl(link));
}
