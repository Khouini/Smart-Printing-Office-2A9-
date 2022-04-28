#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "techniciens.h"
#include <QMessageBox>
#include <QFile>
#include <qrcode.h>
#include <QPixmap>
#include "techniciens.h"
#include <QDesktopServices>
#include <QUrl>

using namespace qrcodegen;
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



//controle de saisie

    ui->lineEdit_id_maint->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_cin_maint->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_num_maint->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_idtache_maint->setValidator(new QIntValidator(0,9999,this));

    ui->lineEdit_nom_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));
    ui->lineEdit_prenom_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));
    ui->lineEdit_email_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));
    ui->lineEdit_Ps_maint->setValidator(new QRegExpValidator ( QRegExp("[A-z]*") ));

    ui->tableView_maint->setModel(Etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


//ajout

void MainWindow::on_pushButton_ajouter_maint_clicked()
{
    int id=ui->lineEdit_id_maint->text().toInt();
    QString nom=ui->lineEdit_nom_maint->text();
    QString prenom=ui->lineEdit_prenom_maint->text();
    int cin=ui->lineEdit_cin_maint->text().toInt();
    int num=ui->lineEdit_num_maint->text().toInt();
    int idtache=ui->lineEdit_idtache_maint->text().toInt();
    QString EMAIL_EMPLOYEE=ui->lineEdit_email_maint->text();
    QString PASSWORD_EMPLOYEE=ui->lineEdit_Ps_maint->text();


    Techniciens T(id,nom,prenom,cin,num,idtache,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE);
    T.save(id,nom,prenom,cin,num,idtache,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE);
    bool test=T.ajouter();

    if(test)
    {
        ui->tableView_maint->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);



}


//suppression

void MainWindow::on_pushButton_supp_maint_clicked()
{
    int id =ui->lineEdit_supp_maint->text().toInt();
    bool test=Etmp.supprimer(id);

    if(test)
    {
        ui->tableView_maint->setModel(Etmp.afficher());

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




//modifier

void MainWindow::on_pushButton_Modifier_maint_clicked()
{
    int id=ui->lineEdit_id_maint->text().toInt();
    QString nom=ui->lineEdit_nom_maint->text();
    QString prenom=ui->lineEdit_prenom_maint->text();
    int cin=ui->lineEdit_cin_maint->text().toInt();
    int num=ui->lineEdit_num_maint->text().toInt();
    int idtache=ui->lineEdit_idtache_maint->text().toInt();
    QString EMAIL_EMPLOYEE=ui->lineEdit_email_maint->text();
    QString PASSWORD_EMPLOYEE=ui->lineEdit_Ps_maint->text();

    Techniciens T(id,nom,prenom,cin,num,idtache,EMAIL_EMPLOYEE,PASSWORD_EMPLOYEE);

    bool test=T.modifier();

    if(test)
    {
        ui->tableView_maint->setModel(Etmp.afficher());

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






//TRI ID
void MainWindow::on_radioButton_idTri_maint_clicked()
{
    ui->tableView_maint->setModel(Etmp.tri_id());

}
//TRI NOM

void MainWindow::on_radioButton_nomTri_maint_clicked()
{
    ui->tableView_maint->setModel(Etmp.tri_nom());

}

//recherche


void MainWindow::on_pushButton_rech_maint_clicked()
{

    QString rech= ui->lineEdit_rech_maint->text();
    ui->tableView_maint->setModel(Etmp.recherche(rech));

}


//theme

void MainWindow::on_pushButton_sombre_maint_clicked()
{
    QFile styleSheetFile("C:/Users/Majd Tabessi/Desktop/ESPRIT2-2/projet c++/Darkeum/Darkeum.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String (styleSheetFile.readAll());
        MainWindow::setStyleSheet(styleSheet);
}

void MainWindow::on_pushButton_blanc_maint_clicked()
{
    QFile styleSheetFile("C:/Users/Majd Tabessi/Desktop/ESPRIT2-2/projet c++/BLANC/Integrid.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String (styleSheetFile.readAll());
        MainWindow::setStyleSheet(styleSheet);
}





//generer pdf


void MainWindow::on_pushButton_pdf_maint_clicked()
{
    int id=ui->lineEdit_id_maint->text().toInt();
    QString nom=ui->lineEdit_nom_maint->text();
    QString prenom=ui->lineEdit_prenom_maint->text();
    int cin=ui->lineEdit_cin_maint->text().toInt();
    int num=ui->lineEdit_num_maint->text().toInt();
    int idtache=ui->lineEdit_idtache_maint->text().toInt();
    QString PASSWORD_EMPLOYEE=ui->lineEdit_Ps_maint->text();
    QString EMAIL_EMPLOYEE=ui->lineEdit_email_maint->text();



    Techniciens T(id,nom,prenom,cin,num,idtache,PASSWORD_EMPLOYEE,EMAIL_EMPLOYEE);
    T.printPDF();
}





//qr code


void MainWindow::on_qrCode_clicked()
{
    int tabeq=ui->tableView_maint->currentIndex().row();
                   QVariant idd=ui->tableView_maint->model()->data(ui->tableView_maint->model()->index(tabeq,0));
                   QString id=idd.toString();
                  // QString code=idd.toSTring();
                   QSqlQuery qry;
                   qry.prepare("select * from EMPLOYEES where id_employee=:id");
                   qry.bindValue(":id",id);
                   qry.exec();

                   int num,cin,idtache;
                    QString idA, nom,prenom,password,email;//attributs


                  while(qry.next()){

                      idA=qry.value(0).toString();
                       nom=qry.value(1).toString();
                        prenom=qry.value(2).toString();
                       cin=qry.value(3).toInt();
                       num=qry.value(13).toInt();
                       idtache=qry.value(10).toInt();
                       password=qry.value(5).toString();
                       email=qry.value(4).toString();

                   }
                   id=QString(id);
                          id="ID_EMPLOYEE:\t" +idA+ "NOM_EMPLOYEE\t:" +nom+ "PRENOM_EMPLOYEE:\t" +prenom+ "CIN_EMPLOYEE:\t" +cin+ "TEL_EMPLOYEE:\t" +num+ "ID_TACHE:\t" +idtache+ "EMAIL_EMPLOYEE:\t" +email+ "PASSWORD_EMPLOYEE:\t" +password ;
                   QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

                   // Read the black & white pixels
                   QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                   for (int y = 0; y < qr.getSize(); y++) {
                       for (int x = 0; x < qr.getSize(); x++) {
                           int color = qr.getModule(x, y);  // 0 for white, 1 for black

                           // You need to modify this part
                           if(color==0)
                               im.setPixel(x, y,qRgb(254, 254, 254));
                           else
                               im.setPixel(x, y,qRgb(0, 0, 0));
                       }
                   }
                   im=im.scaled(200,200);
                  ui->qr_code->setPixmap(QPixmap::fromImage(im));
}



//historique

void MainWindow::on_pushButton_historique_maint_clicked()
{
    QString link="file:///C:/Users/Majd Tabessi/Desktop/ESPRIT2-2/projet c++/interfacefin MRIGEL/histo.txt";
        QDesktopServices::openUrl(QUrl(link));

}




void MainWindow::on_QUITTER_maint_clicked()
{
    close();
}
