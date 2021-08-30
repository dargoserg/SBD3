#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <mcdatastore.h>
#include <myclasssslclient.h>
#include <myclassautorizacion.h>
#include <myclassaddressinput.h>
#include <myclasslocationofdiagnosisselection.h>
#include <myclassdiagnosisselection.h>
#include <struct.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotAuthorization(qint64 idUser, QString userName);
    void slotAddress(structAddress address);
    void slotLocationOfDiagnosis(QString idLocationOfDiagnosis, QString nameLocationOfDiagnosis);
    void slotDiagnosis(QString idDiagnosis, QString nameOfDiagnosis);
    void slotTypeLocationOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray);
    void slotWorkingPositionListResponse(QVector<QVector<QString>> myVectorArray);
    //void slotTypeOfSettlementListResponse(QVector<QVector<QString>> myVectorArray);
    void slotPatientCategoryListResponse(QVector<QVector<QString>> myVectorArray);
    void slotCircumstancesOfTheDiagnosisListResponse(QVector<QVector<QString>> myVectorArray);
    //void slotMedicsListResponse(QVector<QVector<QString>> myVectorArray);
    void slotLaboratoryConfirmationListResponse(QVector<QVector<QString>> myVectorArray);
    void slotSocialGroupListResponse(QVector<QVector<QString>> myVectorArray);
    void slotMonthAndYearResponse(QVector<QVector<QString>> myVectorArray);


signals:
    void signalRequestMonthAndYear();
    void signalRequestTypeLocationOfDiagnosisList();
    void signalRequestWorkingPositionList();
    //void signalRequestTypeOfSettlementList();
    void signalReguestSocialGroupList();
    void signalRequestPatientCategoryList();
    void signalRequestCircumstancesOfTheDiagnosisList();
    //void signalRequestMedicsList();
    void signalRequestLaboratoryConfirmationList();

    void signalTrySave(structRecord);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    void comboBoxFilling();

    MyClassSslClient *sslClient;
    mcDataStore *dataStore;


    qint64 idUser;
    QString userName;

    QString dateToSQLString(QString date);

    structRecord record;
    const QString version = "SBD V3.0";

};

#endif // MAINWINDOW_H
