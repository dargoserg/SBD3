#ifndef MYCLASSDIAGNOSISSELECTION_H
#define MYCLASSDIAGNOSISSELECTION_H

#include <QDialog>
#include <QTimer>
#include <myclasssslclient.h>
#include <myclasstablemodel.h>
#include <mcdatastore.h>
#include <struct.h>

namespace Ui {
class MyClassDiagnosisSelection;
}

class MyClassDiagnosisSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MyClassDiagnosisSelection(QWidget *parent = nullptr, MyClassSslClient *sslClient = nullptr,mcDataStore *dataStore=nullptr);
    ~MyClassDiagnosisSelection();

signals:
    void signalRequestTypeOfDiagnosisList();
    void signalReguestDiagnosisList(quint8 idTypeOfDiagnosis);
    void signalDiagnosisResponse(QString idDiagnosis, QString nameOfDiagnosis);

public slots:
    void slotTypeOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray);
    void slotDiagnosisListResponse(QVector<QVector<QString>> myVectorArray);

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void slotEnableComboBox();
private:
    Ui::MyClassDiagnosisSelection *ui;
    mcDataStore *dataStore;

};

#endif // MYCLASSDIAGNOSISSELECTION_H
