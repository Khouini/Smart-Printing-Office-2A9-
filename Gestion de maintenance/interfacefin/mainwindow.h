#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "techniciens.h"
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
    void on_pushButton_clicked();

    void on_pushButton_9_clicked();


    void on_pushButton_Modifier_clicked();

private:
    Ui::MainWindow *ui;

    Techniciens Etmp ;

};
#endif // MAINWINDOW_H
