#include "mcdatastore.h"

mcDataStore::mcDataStore(MyClassSslClient *sslClient, QObject *parent) : QObject(parent)
{
    modelStruct = new structTableModel;
    mcDataStore::sslClient = sslClient;
    fillingStruct();
}


void mcDataStore::fillingStruct()
{
    //Medics List
    connect(this, &mcDataStore::signalRequestMedicsList,
            sslClient, &MyClassSslClient::slotRequestMedicsList);
    connect(sslClient, &MyClassSslClient::signalMedicsListResponse,
            this ,&mcDataStore::slotMedicsListResponse);
    emit signalRequestMedicsList();
    //*Medics List
    //Type Of Settlement
    connect(this, &mcDataStore::signalRequestTypeOfSettlementList,
            sslClient, &MyClassSslClient::slotRequestTypeOfSettlementList);
    connect(sslClient, &MyClassSslClient::signalTypeOfSettlementListResponse,
            this ,&mcDataStore::slotTypeOfSettlementListResponse);
    emit signalRequestTypeOfSettlementList();
    //*Type Of Settlement

    //Type Of Diagnosis
    connect(this, &mcDataStore::signalRequestTypeOfDiagnosisList,
            sslClient, &MyClassSslClient::slotRequestTypeOfDiagnosisList);
    connect(sslClient, &MyClassSslClient::signalTypeOfDiagnosisListResponse,
            this, &mcDataStore::slotTypeOfDiagnosisListResponse);
     emit signalRequestTypeOfDiagnosisList();
    //*Type Of Diagnosis

}

// Slots
void mcDataStore::slotMedicsListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    modelStruct->medicList = tableModel;
}

void mcDataStore::slotTypeOfSettlementListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    modelStruct->typeOfSettlementList = tableModel;
}

void mcDataStore::slotTypeOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    modelStruct->typeOfDiagnosisList = tableModel;
    //qDebug()<<myVectorArray;
}


//*Slots

// Gets
MyClassTableModel* mcDataStore::getMedicsListModel()
{
    return modelStruct->medicList;
}
MyClassTableModel* mcDataStore::getTypeOfSettlementListModel()
{
    return modelStruct->typeOfSettlementList;
}

MyClassTableModel* mcDataStore::getTypeOfDiagnosisListModel()
{
    return modelStruct->typeOfDiagnosisList;
}



//*Gets
