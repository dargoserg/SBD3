#ifndef SSLTCPSERVER_H
#define SSLTCPSERVER_H


#include <QTcpServer>
#include <QSslSocket>

#include<QThreadPool>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QEventLoop>
#include <QTimer>
#include <QSqlError>

class sslTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    sslTcpServer();
private:

    void readMessage();

    void accountList();
    void login();


    void monthAndYear();








    void districtList();
    void locationOfDiagnosisList();
    void typeOfDiagnosisList();
    void diagnosisList();
    void workingPositionList();
    void socialGroupList();
    void PatientCategoryList();
    void CircumstancesOfTheDiagnosisList();
    void MedicsList();
    void LaboratoryConfirmationList();
    void typeLocationOfDiagnosisList();
    void typeOfSettlementList();



    void slotRequestWorkingPositionList();
    void slotRequestSocialGroupList();
    void slotReguestPatientCategoryList();
    void slotReguestDiagnosisCircumstancesList();
    void slotReguestMedicList();
    void slotReguestLaboratoryConfirmationList();



    void sendData(quint8 typeOfMessage, QByteArray data);

    bool waitForReadyRead(int milliseconds);

    qint64 readSizeOfMessage();
    quint8 readTypeOfMessage();

    QByteArray sqlResponseData(QString sqlReguest);
    QVector<QVector<QString>> sqlResponseToVector(QSqlQuery *sqlQuery);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void ready();
    void readyRead();

private:
    QTcpServer * server;
    QSslSocket * sslSocket;

};

#endif // SSLTCPSERVER_H
