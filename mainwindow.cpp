#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "employe.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    createGroupBox();
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999,this));
    ui->tableView->setModel(em.afficher());
}
void MainWindow::createGroupBox()
{
    groupBox = new QGroupBox(tr("Liste des employees"));
    perspectiveRadioButton = new QRadioButton(tr("Perspective"));
    isometricRadioButton = new QRadioButton(tr("Isometric"));
    obliqueRadioButton = new QRadioButton(tr("Oblique"));
    perspectiveRadioButton->setChecked(true);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(perspectiveRadioButton);
    groupBoxLayout->addWidget(isometricRadioButton);
    groupBoxLayout->addWidget(obliqueRadioButton);
    groupBox->setLayout(groupBoxLayout);
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
    QString rech = ui->lineEdit_cin_3->text() ;
    em.rechercher(rech) ;
}

void MainWindow::on_pushButton_3_clicked()
{


}
