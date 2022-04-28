#ifndef COLORSELECT_H
#define COLORSELECT_H

#include <QWidget>

class colorselect : public QWidget
{
    Q_OBJECT
public:
    explicit colorselect(QWidget *parent = nullptr);
private slots:
    void onColorchanged() ;

signals:

};

#endif // COLORSELECT_H
