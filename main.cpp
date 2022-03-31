#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QLocale>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator t;
    QStringList languages;
    languages <<"french" << "english";

    QString lang = QInputDialog::getItem(NULL,"select language","Language",languages);

    if ( lang == "english")
    {
        t.load(":/lang_eng.qm");
    }

    if( lang != "french")
    {
        a.installTranslator(&t);
    }
    Connection c;
    bool test=c.createconnection();
     MainWindow w;
    if(test)
    {w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
