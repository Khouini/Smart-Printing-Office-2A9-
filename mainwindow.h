#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "comptes.h"
#include <QMainWindow>
#include "gestioncommandes.h"
#include "historique.h"
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

    void on_pushButton_Chercher_clicked();

    void on_pushButton_Trier_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Chercher_2_clicked();

    void on_tableViewComptes_activated(const QModelIndex &index);

    void on_pushButton_actualier_2_clicked();

    void on_pushButton_valider_etablissement_clicked();

    void on_pushButton_afficher_PJ_clicked();


    void on_tableViewCommande1_activated(const QModelIndex &index);

    void on_pushButton_Trier_2_clicked();

    void on_pushButton_Chercher_3_clicked();

    void on_pushButton_Trier_3_clicked();

    void on_pushButton_Chercher_4_clicked();

    void on_pushButton_actualier_3_clicked();

    void on_pushButton_valider_compta_clicked();

    void on_tableViewCommandes_2_activated(const QModelIndex &index);

    void on_pushButtonActualiserHistorique_clicked();

    void on_pushButton_clicked();

    void on_pushButton_afficher_pdf_clicked();

private:
    Ui::MainWindow *ui;
    Comptes Cmpt;
    GestionCommandes GC1;
    Historique H;

};
#endif // MAINWINDOW_H
