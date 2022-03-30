#include "mainwindow.h"
#include "QApplication"
#include "connection.h"
#include "fournisseurs.h"
#include "histo.h"
#include <QMessageBox>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // theme
        QFile styleSheetFile("C:\\Users\\maato\\Desktop\\Projet CRUD\\ProjectFournisseurs\\Darkeum.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = ( styleSheetFile.readAll() );
        a.setStyleSheet(styleSheet);
        //end theme
    Connection c;

    bool test = c.createconnection();
    MainWindow w;
    if (test){
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Connection successful"),
                              QMessageBox::Ok
                              );


    }else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed"),
                              QMessageBox::Cancel
                              );
    }
    return a.exec();
}
