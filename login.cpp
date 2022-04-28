#include "login.h"

login::login()
{

}

bool login::sign_in(QString uname,QString current_pwd)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM USERS WHERE username=:username AND password=:password");
    qry.bindValue(":username",uname);
    qry.bindValue(":password",this->current_pwd);

    //current_user=uname;

    return qry.exec() && qry.next();

}

