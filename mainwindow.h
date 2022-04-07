#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "produit.h"
#include <QMainWindow>
#include <QVariant>
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

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_stock_clicked();

    void on_cam_clicked();

    void on_cam_released();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    produit pro;
signals:
void setCenter(QVariant, QVariant);
void addMarker(QVariant, QVariant);



};
#endif // MAINWINDOW_H
