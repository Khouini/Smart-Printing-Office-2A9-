#include "dialog_voir_pj.h"
#include "ui_dialog_voir_pj.h"

Dialog_Voir_PJ::Dialog_Voir_PJ(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Voir_PJ)
{
    ui->setupUi(this);
}

Dialog_Voir_PJ::~Dialog_Voir_PJ()
{
    delete ui;
}
