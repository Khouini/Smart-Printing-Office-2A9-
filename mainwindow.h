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
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Supprimer_clicked();

    void on_pushButton_Modifier_clicked();



    void on_pushButton_clicked();

    void on_pushButton_Actualiser_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_chercher_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Fournisseurs FRN;
    histo H;
};
#endif // MAINWINDOW_H
