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


    void on_qrCode_clicked();


    void on_pushButton_ajouter_maint_clicked();

    void on_pushButton_Modifier_maint_clicked();

    void on_pushButton_rech_maint_clicked();

    void on_pushButton_supp_maint_clicked();

    void on_pushButton_sombre_maint_clicked();

    void on_pushButton_blanc_maint_clicked();

    void on_pushButton_pdf_maint_clicked();

    void on_pushButton_historique_maint_clicked();

    void on_radioButton_idTri_maint_clicked();

    void on_radioButton_nomTri_maint_clicked();

    void on_QUITTER_maint_clicked();

private:
    Ui::MainWindow *ui;

    Techniciens Etmp ;

};
#endif // MAINWINDOW_H
