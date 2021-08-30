#ifndef myClassSslClient_H
#define myClassSslClient_H
#include <QSslSocket>
#include <QDataStream>

#include <QEventLoop>
#include <QTimer>

#include <struct.h>



class MyClassSslClient : public QSslSocket
{
    Q_OBJECT
public:
    MyClassSslClient(QString pathToPrivateKey, QString pathToLocalCertificate,QString serverAddress, int port);

public slots:
    void slotRequestAccountList();
    void slotTryLogin(qint64 accountNumber, QByteArray passwordHash);

    void slotRequestDistrictList();
    void slotRequestLocationOfDiagnosisList();
    void slotRequestTypeOfDiagnosisList();
    void slotRequestDiagnosisList(quint8 idTypeOfDiagnosis);
    void slotRequestTypeLocationOfDiagnosisList();
    void slotRequestWorkingPositionList();
    void slotRequestTypeOfSettlementList();
    void slotRequestPatientCategoryList();
    void slotRequestCircumstancesOfTheDiagnosisList();
    void slotRequestMedicsList();
    void slotRequestLaboratoryConfirmationList();
    void slotRequestSocialGroupList();
    void slotReguestMonthAndYear();

    void slotTrySave(structRecord);


signals:
    void signalAccountListResponse(QVector<QVector<QString>> Vec);
    void signalTryLoginResponse(QVector<QVector<QString>> Vec);

    void signalDistrictListResponse(QVector<QVector<QString>> Vec);
    void signalLocationOfDiagnosisListResponse(QVector<QVector<QString>> Vec);
    void signalTypeOfDiagnosisListResponse(QVector<QVector<QString>> Vec);
    void signalDiagnosisListResponse(QVector<QVector<QString>> Vec);
    void signalTypeLocationOfDiagnosisListResponse(QVector<QVector<QString>> Vec);
    void signalWorkingPositionListResponse(QVector<QVector<QString>> Vec);
    void signalTypeOfSettlementListResponse(QVector<QVector<QString>> Vec);
    void signalPatientCategoryListResponse(QVector<QVector<QString>> Vec);
    void signalCircumstancesOfTheDiagnosisListResponse(QVector<QVector<QString>> Vec);
    void signalMedicsListResponse(QVector<QVector<QString>> Vec);
    void signalLaboratoryConfirmationListResponse(QVector<QVector<QString>> Vec);
    void signalSocialGroupListResponse(QVector<QVector<QString>> Vec);
    void signalMonthAndYearResponse(QVector<QVector<QString>> Vec);



private:


    bool waitForReadyRead(int milliseconds);


    void verificationMessage();

    void logicSwitch(qint64 sizeOfMessage);

    qint64 readSizeOfMessage();
    quint8 readTypeOfMessage();

    void accountListResponse(qint64 sizeOfMessage);
    void tryLoginResponse(qint64 sizeOfMessage);

    void districtListResponse(qint64 sizeOfMessage);
    void locationOfDiagnosisListResponse(qint64 sizeOfMessage);
    void typeOfDiagnosisResponse(qint64 sizeOfMessage);
    void diagnosisResponse(qint64 sizeOfMessage);
    void typeLocationOfDiagnosisResponse(qint64 sizeOfMessage);
    void workingPositionListResponse(qint64 sizeOfMessage);
    void typeOfSettlementListResponse(qint64 sizeOfMessage);
    void patientCategoryListResponse(qint64 sizeOfMessage);
    void circumstancesOfTheDiagnosisListResponse(qint64 sizeOfMessage);
    void medicsListResponse(qint64 sizeOfMessage);
    void laboratoryConfirmationListResponse(qint64 sizeOfMessage);
    void socialGroupListResponse(qint64 sizeOfMessage);
    void monthAndYearResponse(qint64 sizeOfMessage);

    void save();

    void sendData(quint8 typeOfMessage);
    void sendData(quint8 typeOfMessage, QByteArray data);
    QVector<QVector<QString>> read2dVector(qint64 sizeOfMessage);


    structRecord record;

    QSslSocket *sslSocket;
    qint64 sizeOfReceivedMessage;
private slots:
        void slotEncrypted();
        void slotReadyRead();

};

#endif // myClassSslClient_H
