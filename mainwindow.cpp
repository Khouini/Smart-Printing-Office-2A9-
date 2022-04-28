#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "notificationclient.h"

#include <QMessageBox>
#include<QString>
#include<QSqlError>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QLabel>
#include <QtCharts>
#include <QPieSlice>
#include <QPieSeries>
#include "qrcode.h"



using namespace qrcodegen ;
using namespace std ;
#include "mailing.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPixmap pix("C:/Users/Wahch/Desktop/gestion_client_ssDialog/Picture2.png") ;
    //ui->label_4->setPixmap(pix);
    ui->lineEdit_prenomC->setValidator(new QRegExpValidator(QRegExp("[A-z]*"))) ;
    ui->lineEdit_nomC->setValidator(new QRegExpValidator(QRegExp("[A-z]*"))) ;
    ui->lineEdit_emailC->setValidator(new QRegExpValidator(QRegExp("[a-z]{1,10}@[a-z]{1,10}\\.[a-z]{1,4}"))) ;
    ui->lineEdit_idC->setValidator(new QIntValidator(0,9999,this));
    ui->lineEdit_cinC->setValidator(new QIntValidator(0,19999999,this));
    ui->tableViewC->setModel(Etmp.afficher())  ;
    ui->comboBoxSC->setModel(Etmp.afficherIdClientComboBox());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouterC_clicked()
{
    // recuperation des info saisies
    int id_client=ui->lineEdit_idC->text().toInt();
    int cinn=ui->lineEdit_cinC->text().toInt();
    QString nom=ui->lineEdit_nomC->text();
    QString prenom=ui->lineEdit_prenomC->text();
    QString email=ui->lineEdit_emailC->text();
    QString sexe;
    QString type_client;
    QString operation=" ajout";
    if (ui->radioButtonHommeC->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_FemmeC->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIPC->isChecked()){
        type_client = "VIP";
    }
    if (ui->radioButton_FidelC->isChecked()){
        type_client = "Fidéle";
    }
    if (ui->radioButton_passageeC->isChecked()){
        type_client = "Passager";
    }
    QString res1 = QString::number(id_client) ;
    QString res2 = QString::number(cinn) ;
    // objet client
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    C.save(res1, res2, nom, prenom, email, sexe, type_client,operation);
    notificationclient N(0, nom);
    N.notificationsClient();
    bool test= C.ajouterclient();
    // bool test2=C.controle_saisie_client(C) ;
    if(test)   // si requete executée
    {
        ui->tableViewC->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);
         }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("ajout NON effectué\n"
                                             "Click cancel to exit."),
                                QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_supprimerC_clicked()
{
    int id =ui->lineEdit_supprimer_C->text().toInt() ;
    bool test= Etmp.supprimer(id);
    int id_client=ui->lineEdit_idC->text().toInt();
    int cinn=ui->lineEdit_cinC->text().toInt();
    QString nom=ui->lineEdit_nomC->text();
    QString prenom=ui->lineEdit_prenomC->text();
    QString email=ui->lineEdit_emailC->text();
    QString sexe;
    QString type_client;
    QString operation=" Delete";
    QString res1 = QString::number(id_client) ;
    QString res2 = QString::number(cinn) ;
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    notificationclient N(2, nom);
    N.notificationsClient();
    C.save(res1, res2, nom, prenom, email, sexe, type_client,operation);

    if(test)   // si requete executée
    {
        ui->tableViewC->setModel(Etmp.afficher());
        ui->comboBoxSC->setModel(Etmp.afficherIdClientComboBox());
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

void MainWindow::on_pushButton_modifierC_clicked()
{
    // recuperation des info saisies
    int id_client=ui->lineEdit_idC->text().toInt();
    int cinn=ui->lineEdit_cinC->text().toInt();
    QString nom=ui->lineEdit_nomC->text();
    QString prenom=ui->lineEdit_prenomC->text();
    QString email=ui->lineEdit_emailC->text();
    QString sexe;
    QString type_client;
    QString operation=" modification";
    if (ui->radioButtonHommeC->isChecked()){
        sexe = "Homme";
    }
    if (ui->radioButton_FemmeC->isChecked()){
        sexe = "Femme";
    }
    if (ui->radioButton_VIPC->isChecked()){
        type_client = "VIP";
    }
    if (ui->radioButton_FidelC->isChecked()){
        type_client = "Fidéle";
    }
    if (ui->radioButton_passageeC->isChecked()){
        type_client = "Passager";
    }
    QString res1 = QString::number(id_client) ;
    QString res2 = QString::number(cinn) ;
    // objet client
    client C(nom,prenom,email,sexe,type_client,id_client,cinn);
    bool test= C.modifierclient();
    notificationclient N(1, nom);
    N.notificationsClient();
    C.save(res1, res2, nom, prenom, email, sexe, type_client , operation);
    if(test)   // si requete executée
    {
        ui->tableViewC->setModel(Etmp.afficher());
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

void MainWindow::on_pushButton_chercherC_clicked() //recherche
{
QString rech = ui->lineEdit_RC->text() ;
ui->tableViewC->setModel(Etmp.rechercher(rech)) ;
ui->comboBoxRC->setModel(Etmp.afficherIdClientComboBox());

}

void MainWindow::on_pushButton_triC_clicked()  //tri
{
    QString type ;
    QString attribut ;
    if (ui->radioButton_6AC->isChecked())
    {  type="asc" ; }
    if (ui->radioButton_6DC->isChecked())
    {  type="desc" ; }

    attribut = ui->comboBoxC->currentText();
    ui->tableViewC->setModel(Etmp.tri(type,attribut))  ;




}


/* void MainWindow::on_tableViewC_2_activated(const QModelIndex &index) //table commande
{

} */

void MainWindow::on_tableViewC_activated(const QModelIndex &index) // selection par id
{
    QString id=ui->tableViewC->model()->data(index).toString() ;


    QSqlQuery query  ;

    query.prepare("select * from CLIENTS where (ID_CLIENT LIKE '"+id+"')") ;
    if (query.exec())
    {
        while (query.next()) {

            ui->lineEdit_idC->setText(query.value(0).toString()) ;
            ui->lineEdit_nomC->setText(query.value(1).toString()) ;
            ui->lineEdit_prenomC->setText(query.value(2).toString()) ;
            ui->lineEdit_emailC->setText(query.value(3).toString()) ;
            ui->lineEdit_cinC->setText(query.value(4).toString()) ;
            if ((query.value(4).toString() == "homme"))
            { ui->radioButtonHommeC->setChecked(1) ;  }
            if ((query.value(4).toString() == "femme"))
            { ui->radioButton_FemmeC->setChecked(1) ;  }
            if ((query.value(5).toString() == "VIP"))
            { ui->radioButton_VIPC->setChecked(1) ;  }
            if ((query.value(5).toString() == "Fidéle"))
            { ui->radioButton_FidelC->setChecked(1) ;  }
            if ((query.value(5).toString() == "Passage"))
            { ui->radioButton_passageeC->setChecked(1) ;  }

        }
    }
        else {
             QMessageBox::critical(this,tr("error::"),query.lastError().text()) ;
               }

}

void MainWindow::on_pushButtonPDFC_clicked()  //button export pdf
{
   int cinn=ui->lineEdit_cinC->text().toInt();
   int id_client=ui->lineEdit_idC->text().toInt();
   QString email=ui->lineEdit_emailC->text();
   QString nom=ui->lineEdit_nomC->text();
   QString prenom=ui->lineEdit_prenomC->text();
   QString sexe;
   QString type_client;
   if (ui->radioButtonHommeC->isChecked()){
       sexe = "Homme";
   }
   if (ui->radioButton_FemmeC->isChecked()){
       sexe = "Femme";
   }
   if (ui->radioButton_VIPC->isChecked()){
       type_client = "VIP";
   }
   if (ui->radioButton_FidelC->isChecked()){
       type_client = "Fidéle";
   }
   if (ui->radioButton_passageeC->isChecked()){
       type_client = "Passager";
   }
   client Etmp(nom,prenom,email,sexe,type_client,id_client,cinn);
   Etmp.printPDF_client() ;

}

void MainWindow::on_pushButton_theme1C_clicked()
{

    QFile styleSheetFile("C:/Users/Wahch/Desktop/projetQT/template/Darkeum.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String (styleSheetFile.readAll());
    MainWindow::setStyleSheet(styleSheet);
}

void MainWindow::on_pushButton_theme2C_clicked()
{
    QFile styleSheetFile("C:/Users/Wahch/Desktop/projetQT/template/Toolery.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String (styleSheetFile.readAll());
    MainWindow::setStyleSheet(styleSheet);
}

void MainWindow::on_pushButton_historiqueC_clicked()
{
    QString link="file:///C:/Users/Wahch/Desktop/gestion_client_ssDialog/histo.txt";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_ouvrirPDFC_clicked()
{

    QString link="file:///C:/Users/Wahch/Desktop/gestion_client_ssDialog/client.pdf";
        QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_pushButton_mail_send_clicked()
{
    Mailing* mailing = new Mailing("mohamed.wahchi@esprit.tn", "191JMT3037", "smtp.gmail.com", 465);
    mailing->sendMail("mohamed.wahchi@esprit.tn", "mohamed.wahchi@esprit.tn", "Subject" ,"Message");
}

void MainWindow::on_pushButton_qrCode_clicked()
{



}

void MainWindow::on_qrCodeC_clicked()
{
    int tabeq=ui->tableViewC->currentIndex().row();
    QVariant idd=ui->tableViewC->model()->data(ui->tableViewC->model()->index(tabeq,0));
    QString id=idd.toString();
   // QString code=idd.toSTring();
    QSqlQuery qry;
    qry.prepare("select * from CLIENTS where ID_CLIENT=:id");
    qry.bindValue(":id",id);
    qry.exec();

     QString nom,prenom,email,idC;//attributs
     int cin ;



   while(qry.next()){

       idC=qry.value(1).toString();
       nom=qry.value(2).toString();
       prenom=qry.value(3).toInt();
       cin=qry.value(5).toInt();
       email=qry.value(8).toString();







    }
    id=QString(id);
  id="ID_CLIENT:\t" +id+ "NOM_CLIENT\t:" +nom+ "PRENOM_CLIENT:\t" +prenom+ "CIN_CLIENT:\t" +cin+ "EMAIL_CLIENT:\t" +email  ;
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
      ui->qr_codeC->setPixmap(QPixmap::fromImage(im));

}

void MainWindow::on_pushButton_statC_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                             model->setQuery("select * from CLIENTS where TYPE_CLIENT like 'VIP'  ");
                             float VIP=model->rowCount();
                             model->setQuery("select * from CLIENTS where TYPE_CLIENT like 'Fidele' ");
                             float Fidele=model->rowCount();
                             model->setQuery("select * from CLIENTS where TYPE_CLIENT like 'Passager' ");
                             float Passager=model->rowCount();
                             float total=VIP+Fidele+Passager;

                             QString a=QString("VIP  "+QString::number((VIP*100)/total,'f',2)+"%" );
                             QString b=QString("Fidele  "+QString::number((Fidele*100)/total,'f',2)+"%" );
                             QString c=QString("Passager  "+QString::number((Passager*100)/total,'f',2)+"%" );

                             QPieSeries *series = new QPieSeries();
                             series->append(a,VIP);
                             series->append(b,Fidele);
                             series->append(c,Passager);


                     if (VIP!=0)
                     {QPieSlice *slice = series->slices().at(0); //pourcentage de chaque slice
                      slice->setLabelVisible();
                      slice->setPen(QPen());}
                     if ( Fidele!=0)
                     {
                              // Add label, explode and define brush for 2nd slice
                              QPieSlice *slice1 = series->slices().at(1);
                              //slice1->setExploded();
                              slice1->setLabelVisible();
                     }
                     if ( Passager!=0)
                     {
                              // Add label, explode and define brush for 2nd slice
                              QPieSlice *slice2 = series->slices().at(2);
                              //slice2->setExploded();
                              slice2->setLabelVisible();
                     }


                             // Create the chart widget
                             QChart *chart = new QChart();
                             // Add data to chart with title and hide legend
                             chart->addSeries(series);
                             chart->setTitle("Pourcentage Par TYPE_CLIENT :Nombre clients "+ QString::number(total));
                             chart->legend()->hide();
                             // Used to display the chart
                             QChartView *chartView = new QChartView(chart);
                             chartView->setRenderHint(QPainter::Antialiasing);
                             chartView->resize(1000,500);
                             chartView->show();

}

void MainWindow::on_pushButton_verifC_clicked()
{
    bool test;
    QSqlQuery qry;
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT COUNT(ID_CLIENT) FROM CLIENTS ");
    float COUNT=model->rowCount();
    qry.prepare("SELECT COUNT(ID_CLIENT) FROM CLIENTS ");
    if (qry.exec()){

        while (qry.next()){
            if (COUNT > 10){
                        test = true;
                    }else{
                        test = false;
                    }
        }

        QMessageBox msgbox;
        if (test){

                QMessageBox::information(nullptr, QObject::tr("notification"),
                                      QObject::tr("nombre de client est superieur a 10"),
                                      QMessageBox::Ok
                                      );
            }else{
                QMessageBox::critical(nullptr, QObject::tr("notification"),
                                      QObject::tr("alerte : nombre de client est inferieur a 10"),
                                      QMessageBox::Cancel
                                      );
            }
} }
