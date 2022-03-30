#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection(){
  QSqlDatabase  db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("Projet");
    db.setUserName("fahed");
    db.setPassword("esprit18");
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){
    db.close();
}
