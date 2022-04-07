#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include <QMessageBox>
#include "histo.h"
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableViewAffichage->setModel(FRN.afficher());
    ui->lineEdit_id->setValidator(new QIntValidator(0, 999999, this));
    ui->lineEdit_tel->setValidator(new QIntValidator(0, 99999999, this));
    ui->comboBoxSup->addItems(FRN.lister2());
    ui->lineEdit_email->setValidator(new QRegExpValidator(QRegExp("[a-z]{1,10}@[a-z]{1,10}\\.[a-z]{1,4}"))) ;
     ui->view_histo->setModel(H.Afficher());
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
    QString nom = ui->lineEdit_nom->text();
    Fournisseurs F(id, num, email, produit, date_arrivee, nom);
    bool test = F.ajouter();

    if (test){


        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
        QString operation="ajout";

              histo h(operation, id);
               h.Ajouter();
               ui->view_histo->setModel(H.Afficher()); // refrechi el tableau
      ui->tableViewAffichage->setModel(FRN.afficher());
      ui->lineEdit_id->clear();
      ui->lineEdit_nom->clear();
      ui->lineEdit_tel->clear();
      ui->lineEdit_email->clear();
      ui->lineEdit_email_2->clear();
      ui->lineEdit_produit->clear();
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_tel->clear();
        ui->lineEdit_email->clear();
        ui->lineEdit_email_2->clear();
        ui->lineEdit_produit->clear();
    }
}

void MainWindow::on_pushButton_Supprimer_clicked()
{
    int id =ui->comboBoxSup->currentText().toInt();
   // int id = ui->lineEdit_id_suppression->text().toInt();
    bool test = FRN.supprimer(id);
    ui->view_histo->setModel(H.Afficher());

    if (test){
        QString operation="suppression";
        histo h(operation, id);
                H.Ajouter();
                 ui->comboBoxSup->addItems(FRN.lister2());

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
    QString nom = ui->lineEdit_nom->text();
    Fournisseurs F(id, num, email, produit, date_arrivee, nom);
    bool test = F.modifier();

    if (test){
        QString operation="modification";
        histo h(operation, id);
                H.Ajouter();
                 ui->view_histo->setModel(H.Afficher());
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

void MainWindow::on_pushButton_clicked()
{
    ui->tableViewAffichage->setModel(FRN.trier());
}

void MainWindow::on_pushButton_Actualiser_clicked()
{
    ui->tableViewAffichage->setModel(FRN.afficher());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableViewAffichage->setModel(FRN.trierNom());
}


void MainWindow::on_pushButton_3_clicked()
{
        int id_fournisseur=ui->lineEdit_id->text().toInt();
        int tel=ui->lineEdit_tel->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString email=ui->lineEdit_email->text();
        QString produit=ui->lineEdit_produit->text();
        QString date=ui->lineEdit_email_2->text();
       Fournisseurs F(id_fournisseur,tel,nom,email,produit,date);

       F.printPDF_employe();
}

void MainWindow::on_pushButton_4_clicked()
{
    //ui->stackedWidget_2->setCurrentIndex(1);
            QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from fournisseurs where id_fournisseur < 19999 ");
            float taille=model->rowCount();
            model->setQuery("select * from fournisseurs where id_fournisseur  between 19999 and 29999 ");
            float taillee=model->rowCount();
            model->setQuery("select * from fournisseurs where id_fournisseur >29999 ");
            float tailleee=model->rowCount();
            float total=taille+taillee+tailleee;
            QString a=QString("fournisseurs fidele . "+QString::number((taille*100)/total,'f',2)+"%" );
            QString b=QString("fournisseur non fidele .  "+QString::number((taillee*100)/total,'f',2)+"%" );
            QString c=QString("fournisseur retsekour ."+QString::number((tailleee*100)/total,'f',2)+"%" );
            QPieSeries *series = new QPieSeries();
            series->append(a,taille);
            series->append(b,taillee);
            series->append(c,tailleee);
            if (taille!=0)
            {QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());}
            if ( taillee!=0)
            {
                // Add label, explode and define brush for 2nd slice
                QPieSlice *slice1 = series->slices().at(1);
                //slice1->setExploded();
                slice1->setLabelVisible();
            }
            if(tailleee!=0)
            {
                // Add labels to rest of slices
                QPieSlice *slice2 = series->slices().at(2);
                //slice1->setExploded();
                slice2->setLabelVisible();
            }
            // Create the chart widget
            QChart *chart = new QChart();
            // Add data to chart with title and hide legend
            chart->addSeries(series);
            chart->setTitle("distribution fournisseurs :Nombre Des fournisseurs "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}

void MainWindow::on_pushButton_ActualiserHistorique_clicked()
{
    ui->view_histo->setModel(H.Afficher());

}


void MainWindow::on_pushButton_chercher_clicked()
{
    QString rech_field = ui->lineEdit_nom_recherche->text();
    ui->tableViewAffichage->setModel(FRN.chercher(rech_field));

}


void MainWindow::on_pushButton_6_clicked()
{
    QString strStream;

                     QTextStream out(&strStream);

                     const int rowCount = ui->tableViewAffichage->model()->rowCount();
                     const int columnCount = ui->tableViewAffichage->model()->columnCount();
                     QString TT = QDateTime::currentDateTime().toString();
                     out <<"<html>\n"
                           "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         << "<title>ERP - COMmANDE LIST<title>\n "
                         << "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"
                            "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\maato\\Desktop\\Nouveau%20dossier\\fahed.pdf />"
                            "<h1 style=\"text-align: center;\"><strong> *****LISTE DES  licence commerciale ***** </strong></h1>"


                         "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                           "</br> </br>";
                     // headers
                     out << "<thead><tr bgcolor=#d6e5ff>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableViewAffichage->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableViewAffichage->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableViewAffichage->isColumnHidden(column)) {
                                 QString data =ui->tableViewAffichage->model()->data(ui->tableViewAffichage->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table>\n"
                         "</body>\n"
                         "</html>\n";

                     QTextDocument *document = new QTextDocument();
                     document->setHtml(strStream);

                     QPrinter printer;

                     QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                     if (dialog->exec() == QDialog::Accepted) {
                         document->print(&printer);
                     }

                     delete document;
}






void MainWindow::on_pb_image_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName =QFileDialog::getOpenFileName(this, tr("Open Images"), "C:/Users/maato/Desktop/Projet CRUD/ProjectFournisseurs", tr("Image Files (*.png *.jpg *.bmp)"));
//to select and show the picture
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
            ui->label_pic->setPixmap(QPixmap::fromImage(image));
    }
}




