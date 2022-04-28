#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include <QMainWindow>
#include"histo.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Ajouter_F_clicked();

    void on_pushButton_Supprimer_F_clicked();

    void on_pushButton_Modifier_F_clicked();


    void on_pushButton_F_clicked();

    void on_pushButton_2_F_clicked();

    void on_pushButton_chercher_F_clicked();

    void on_pushButton_3_F_clicked();

    void on_pushButton_4_F_clicked();
void on_pushButton_Actualiser_F_clicked();

    void on_pushButton_6_F_clicked();

    void on_pb_image_F_clicked();


private:
    Ui::MainWindow *ui;
    Fournisseurs FRN;
    histo HF;
    QByteArray data;
};
#endif // MAINWINDOW_H
