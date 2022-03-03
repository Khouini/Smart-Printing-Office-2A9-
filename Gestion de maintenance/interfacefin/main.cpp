#include "mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include "connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test=c.createconnection();
    MainWindow w;

    if(test)
    {
        w.show();
        QMessageBox::information(nullptr ,QObject::tr("data base is open"),
        QObject::tr("connection successful. \n"
                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("data base is not open"),
                    QObject::tr("connection failed. \n"
                                "Click cancel to exit."),QMessageBox::Cancel);

    return a.exec();
}
