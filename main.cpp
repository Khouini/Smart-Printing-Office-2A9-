#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QLocale>
#include "languagechooser.h"



int main(int argc, char *argv[])
{

    Q_INIT_RESOURCE(i18n);

    QApplication a(argc, argv);
    LanguageChooser chooser(QLocale::system().name());
    chooser.show();



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
