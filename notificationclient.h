#ifndef NOTIFICATIONCLIENT_H
#define NOTIFICATIONCLIENT_H
#include <QSystemTrayIcon>
#include <QString>


class notificationclient
{
public:
    notificationclient();
    notificationclient(int, QString);
    void notificationsClient();
    private:
    int operationInt;
    QString Nom;
};

#endif // NOTIFICATIONCLIENT_H
