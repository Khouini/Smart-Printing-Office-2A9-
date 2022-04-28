#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"

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
    void on_pushButton_ajouterA_clicked();
    void on_pushButton_supprimerA_clicked();
    void on_pushButton_modifierA_clicked();
    void on_pushButton_2A_clicked();


    void on_pushButton_4A_clicked();

    void on_pushButtonA_clicked();

    void on_pushButton_3A_clicked();

    void on_pushButton_6A_clicked();

    void on_pushButton_7A_clicked();

    void on_pushButton_5A_clicked();

private:
    Ui::MainWindow *ui;
    employe em;

};
#endif // MAINWINDOW_H
