#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"

QT_BEGIN_NAMESPACE
class QAction;
class QGroupBox;
class QLabel;
class QListWidget;
class QMenu;
class QRadioButton;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_2_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    employe em;
    void createGroupBox();

    QWidget *centralWidget;
    QLabel *label;
    QGroupBox *groupBox;
    QListWidget *listWidget;
    QRadioButton *perspectiveRadioButton;
    QRadioButton *isometricRadioButton;
    QRadioButton *obliqueRadioButton;
    QMenu *fileMenu;
    QAction *exitAction;
};
#endif // MAINWINDOW_H
