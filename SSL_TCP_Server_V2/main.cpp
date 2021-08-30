#include <QCoreApplication>
#include <ssltcpserver.h>


#include <QtSql>
#include <QCryptographicHash>

#include <QSqlQuery>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    QSqlDatabase db;
    db=QSqlDatabase::addDatabase("QMYSQL");
    //CreateConnection(ip,"Connect","SsY%MIo=}>8](3ZT<K7hfj*Us{f~zr5f",db);
    //db.setConnectOptions("CLIENT_SSL=1;CLIENT_IGNORE_SPACE=1");


    //db.setConnectOptions("CLIENT_IGNORE_SPACE=1");
    db.setUserName("Connect");
    db.setPassword("SsY%MIo=}>8](3ZT<K7hfj*Us{f~zr5f");
    db.setHostName("192.168.0.25");
    db.setPort(3306);
    //db.setPort(4466);
    //if (!db.open()) QMessageBox::information(0,"Ошибка","Ошибка соединения с сервером");
    if (!db.open()) qDebug() << db.lastError();

    //qDebug()<<db.lastError();

    qDebug() << "Connect to database -" << db.isOpen();
    if (db.open())
    {
        sslTcpServer *MySslServer = new sslTcpServer;
        if ( !MySslServer->listen(QHostAddress::Any ,3366)) qDebug()<<"Server is not started";
        else qDebug() << "Server start";

    }

    return a.exec();
}
