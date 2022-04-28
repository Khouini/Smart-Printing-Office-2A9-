#include "notificationclient.h"

notificationclient::notificationclient()
{

}
notificationclient::notificationclient(int operationInt, QString Nom)
{
    this->operationInt=operationInt;
    this->Nom=Nom;
}
void notificationclient::notificationsClient(){
    QString text;
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    switch (operationInt) {
    case 0:  //ajout
        notifyIcon->setIcon(QIcon("C:/Users/Wahch/Desktop/projetQT/IntegrationQt-main/img/valider.png"));
        notifyIcon->show();
        text = "Nouveau client " + Nom + " Ajouté";
        notifyIcon->showMessage("Gestion des Comptes", text,QSystemTrayIcon::Information,15000);
    break;
    case 1: //Modification
        notifyIcon->setIcon(QIcon("C:/Users/Wahch/Desktop/projetQT/IntegrationQt-main/img/modifier.png"));
        notifyIcon->show();
        text = "Client " + Nom + " modifié";
        notifyIcon->showMessage("Gestion des Clients", text,QSystemTrayIcon::Information,15000);
    break;
    case 2: //Suppression
        notifyIcon->setIcon(QIcon("C:/Users/Wahch/Desktop/projetQT/IntegrationQt-main/img/supprimer.png"));
        notifyIcon->show();
        text = "Client " + Nom + " supprimé";
        notifyIcon->showMessage("Gestion des Clients", text,QSystemTrayIcon::Information,15000);
    break;

    }

}
