#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("source_projet2A");
    db.setUserName("fahed");
    db.setPassword("esprit18");
    if (db.open()) test=true;
    return test;
}
void Connection::closeConnection(){
    db.close();
}
