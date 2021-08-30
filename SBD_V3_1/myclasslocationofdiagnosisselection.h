#ifndef MYCLASSLOCATIONOFDIAGNOSISSELECTION_H
#define MYCLASSLOCATIONOFDIAGNOSISSELECTION_H

#include <QDialog>
#include <QTableWidget>
#include <myclasssslclient.h>
#include <myclasstablemodel.h>


namespace Ui {
class MyClassLocationOfDiagnosisSelection;
}

class MyClassLocationOfDiagnosisSelection : public QDialog
{
    Q_OBJECT

public:
    explicit MyClassLocationOfDiagnosisSelection(QWidget *parent = nullptr, MyClassSslClient *sslClient = nullptr);
    ~MyClassLocationOfDiagnosisSelection();

signals:
    void signalRequestLocationOfDiagnosisList();
    void signalLocationOfDiagnosisResponse(QString idLocationOfDiagnosis, QString nameLocationOfDiagnosis);

public slots:
    void slotLocationOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::MyClassLocationOfDiagnosisSelection *ui;
    QList<QTableWidgetItem*> searchItemList;
    int currentSerchListPosition;
};

#endif // MYCLASSLOCATIONOFDIAGNOSISSELECTION_H
