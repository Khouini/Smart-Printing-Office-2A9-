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
#include"mailing.h"
#include "notifications.h"
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
        //Notification
        notifications N(0, Nom);
        N.notificationsComptes();
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
        //Notification
        notifications N(2, Nom);
        N.notificationsComptes();
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
        //Notification
        notifications N(1, Nom);
        N.notificationsComptes();
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
            ui->lineEdit_id_commande_email->setText(query.value(0).toString());
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
    QString Nom, Classe, Type;
    int Numero, solde;
    QString val = ui->comboBox_pdf_id->currentText();
    QSqlQuery query;
    query.prepare("select * from comptes where (n_compte) LIKE "+val+" ");
    if (query.exec()){

        while (query.next()){
            Numero = query.value(0).toInt();
            Nom = query.value(1).toString();
            Classe = query.value(2).toString();
            Type = query.value(3).toString();
            solde = query.value(4).toInt();
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
    Comptes C(Numero, Nom, Classe, Type, solde);
    C.printPDF_comptes() ;

}

void MainWindow::on_pushButton_afficher_pdf_clicked()
{
    QString link="file:///D:/Documents/GitHub/Gestion-Fiance-Qt/comptes.pdf";
            QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_envoyer_clicked()
{
    QString nickname = ui->lineEditidNickname->text();
    QString Conversation = ui->lineEdit_Conversation->text();
    QString message_sent = ui->lineEdit_massage->text();
    QSqlQuery query;
    query.prepare("insert into CHATBOX values ('"+nickname+"', "+Conversation+", CHATBOX_SEQ.nextval, '"+message_sent+"', sysdate); ");
    if (query.exec()){
            QString Conversation = ui->lineEdit_Conversation->text();
            QString nickname, msgForTextEdit, text;
            QSqlQuery querySelect;
            QString date;
            querySelect.prepare("select  nickname, msg, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+" order by date_sent;");
            if (querySelect.exec()){
                ui->textEdit->clear();
                while (querySelect.next()){
                    nickname = querySelect.value(0).toString();
                    msgForTextEdit = querySelect.value(1).toString();
                    date = querySelect.value(2).toString();
                    text = date + "    " +  nickname + ": " + msgForTextEdit;
                    ui->textEdit->append(text);
                }
            }else{
                QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
            }
        }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }

}

void MainWindow::on_pushButton_actualiser_chat_clicked()
{
    QString date;
    QString Conversation = ui->lineEdit_Conversation->text();
    QString nickname, msgForTextEdit, text;
    QSqlQuery querySelect;
    querySelect.prepare("select  nickname, msg, TO_CHAR(date_sent, 'dy HH24:MI') from CHATBOX where conversation like "+Conversation+" order by date_sent;");
    if (querySelect.exec()){
        ui->textEdit->clear();
        while (querySelect.next()){
            nickname = querySelect.value(0).toString();
            msgForTextEdit = querySelect.value(1).toString();
            date = querySelect.value(2).toString();
            text = date + "    " +  nickname + ": " + msgForTextEdit;
            ui->textEdit->append(text);
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), querySelect.lastError().text());
    }
}

void MainWindow::on_pushButton_send_mail_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("STMP is open"),
                          QObject::tr("Message envoyé"),
                          QMessageBox::Ok
                          );
    Mailing* mailing = new Mailing("testkhouini@gmail.com", "Trunks@2001", "smtp.gmail.com", 465);
    QString adresse = ui->lineEdit_adresse_dest->text();
    QString Subject = ui->lineEdit_subject->text();
    QString Message = ui->textEdit_message_email->toPlainText();
    mailing->sendMail("testkhouini@gmail.com", adresse, Subject ,Message);
}

void MainWindow::on_pushButton_mail_pj_clicked()
{
    QString txt;
    QString val = ui->lineEdit_id_commande_email->text();
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
                txt = in.readAll();

            }
        }
    }else{
        QMessageBox::critical(this, tr("Error::"), query.lastError().text());
    }
    Mailing* mailing = new Mailing("testkhouini@gmail.com", "Trunks@2001", "smtp.gmail.com", 465);
    QString adresse = ui->lineEditMailClient->text();
    mailing->sendMail("testkhouini@gmail.com", adresse, "PJ" , txt);
    QMessageBox::information(nullptr, QObject::tr("STMP is open"),
                          QObject::tr("mail envoyé"),
                          QMessageBox::Ok
                          );
}
