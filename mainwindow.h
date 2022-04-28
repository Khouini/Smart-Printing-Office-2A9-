#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"

#include <QMainWindow>
#include <QWidget>
#include "mailing.h"

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
    void on_pushButton_ajouterC_clicked();

    void on_pushButton_supprimerC_clicked();

    void on_pushButton_modifierC_clicked();

    void on_pushButton_chercherC_clicked();

    void on_pushButton_triC_clicked();

    void on_tableViewC_activated(const QModelIndex &index);

    void on_pushButtonPDFC_clicked();

    void on_pushButton_theme1C_clicked();

    void on_pushButton_theme2C_clicked();

    void on_pushButton_historiqueC_clicked();

    void on_pushButton_ouvrirPDFC_clicked();

    void on_pushButton_mail_send_clicked();

    void on_pushButton_qrCode_clicked();

    void on_qrCodeC_clicked();

    void on_pushButton_statC_clicked();

    void on_pushButton_verifC_clicked();

private:
    Ui::MainWindow *ui;
    client Etmp ;
};
#endif // MAINWINDOW_H
