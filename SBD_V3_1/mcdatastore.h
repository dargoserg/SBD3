#ifndef MCDATASTORE_H
#define MCDATASTORE_H

#include <QObject>
#include <myclasstablemodel.h>
#include <myclasssslclient.h>

class mcDataStore : public QObject
{
    Q_OBJECT
public:
    explicit mcDataStore(MyClassSslClient *sslClient,QObject *parent = nullptr);
    MyClassTableModel* getMedicsListModel();
    MyClassTableModel* getTypeOfSettlementListModel();
    MyClassTableModel* getTypeOfDiagnosisListModel();

public slots:
    void slotMedicsListResponse(QVector<QVector<QString>> myVectorArray);
    void slotTypeOfSettlementListResponse(QVector<QVector<QString>> myVectorArray);
    void slotTypeOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray);

signals:
    void signalRequestMedicsList();
    void signalRequestTypeOfSettlementList();
    void signalRequestTypeOfDiagnosisList();

private:

    void fillingStruct();
    struct structTableModel
    {
        MyClassTableModel *medicList;
        MyClassTableModel *typeOfSettlementList;
        MyClassTableModel *typeOfDiagnosisList;

    };

    structTableModel *modelStruct;
    MyClassSslClient *sslClient;
};



#endif // MCDATASTORE_H
