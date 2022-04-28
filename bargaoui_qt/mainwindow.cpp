#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlQuery>
#include "arduino.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data=A.read_from_arduino();
    ui->textEditb->append(data);


}

void MainWindow::on_pushButtonb_clicked()
{
    QString var;
    QString nom = ui->lineEditb->text();
    qDebug() << nom;

QSqlQuery querry;
querry.prepare("Select ID_E from EMPLOYE where NOM like '"+nom+"' ");
if (querry.exec()){
    while (querry.next()){
        qDebug() << "fonded " << querry.value(0).toString();
        var = querry.value(0).toString();

    }
}else{
    qDebug() << "Error";
}
if(var=="2A D6 26 48")
{
A.write_to_arduino("2");

}
else if (var=="60 98 DE 2C")
{
    A.write_to_arduino("1");
}
else if (var=="4695489")
{
    A.write_to_arduino("1");
}
else
{
    A.write_to_arduino("3");
}
}

void MainWindow::on_pushButtonb_2_clicked()
{
    QString var;
    QString nom = ui->lineEditb->text();
    qDebug() << nom;

QSqlQuery querry;
querry.prepare("Select ID_E from EMPLOYE where NOM like '"+nom+"' ");
if (querry.exec()){
    while (querry.next()){
        qDebug() << "fonded " << querry.value(0).toString();
        var = querry.value(0).toString();

    }
}else{
    qDebug() << "Error";
}
    if(var=="86 ED 2A 21")
    {
    A.write_to_arduino("2");
    }
    else if (var=="60 98 DE 2C")
    {
        A.write_to_arduino("2");
    }
    else if (var=="4695489")
    {
        A.write_to_arduino("2");
    }
    else
    {
        A.write_to_arduino("3");
    }
}
