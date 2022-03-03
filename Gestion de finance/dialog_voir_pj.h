#ifndef DIALOG_VOIR_PJ_H
#define DIALOG_VOIR_PJ_H

#include <QDialog>

namespace Ui {
class Dialog_Voir_PJ;
}

class Dialog_Voir_PJ : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Voir_PJ(QWidget *parent = nullptr);
    ~Dialog_Voir_PJ();

private:
    Ui::Dialog_Voir_PJ *ui;
};

#endif // DIALOG_VOIR_PJ_H
