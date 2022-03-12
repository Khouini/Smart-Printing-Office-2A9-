#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "produit.h"
#include <QMainWindow>

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

    void on_pushButton_10_clicked();




    void on_pushButton_supprimer_clicked();

    void on_pushButton_11_clicked();

    void on_radioButton_TRInProd_clicked();

    void on_radioButton_TRIqProd_clicked();





    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
     produit pro;

};
#endif // MAINWINDOW_H
