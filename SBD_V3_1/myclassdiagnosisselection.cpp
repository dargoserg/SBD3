#include "myclassdiagnosisselection.h"
#include "ui_myclassdiagnosisselection.h"



MyClassDiagnosisSelection::MyClassDiagnosisSelection(QWidget *parent, MyClassSslClient *sslClient,mcDataStore *dataStore) :
    QDialog(parent),
    ui(new Ui::MyClassDiagnosisSelection)
{
    ui->setupUi(this);

    this->setModal(1);

    //data

    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    setWindowTitle("Выберите диагноз");

/*
    connect(this, &MyClassDiagnosisSelection::signalRequestTypeOfDiagnosisList,
            sslClient, &MyClassSslClient::slotRequestTypeOfDiagnosisList);
    connect(sslClient, &MyClassSslClient::signalTypeOfDiagnosisListResponse,
            this, &MyClassDiagnosisSelection::slotTypeOfDiagnosisListResponse);
*/
    connect(this, &MyClassDiagnosisSelection::signalReguestDiagnosisList,
            sslClient, &MyClassSslClient::slotRequestDiagnosisList);
    connect(sslClient, &MyClassSslClient::signalDiagnosisListResponse,
            this, &MyClassDiagnosisSelection::slotDiagnosisListResponse);

//    emit signalRequestTypeOfDiagnosisList();
    ui->comboBox->setModel(dataStore->getTypeOfDiagnosisListModel());

}

MyClassDiagnosisSelection::~MyClassDiagnosisSelection()
{
    ui->tableWidget->clear();
    delete ui;
}

void MyClassDiagnosisSelection::on_comboBox_currentIndexChanged(int index)
{

    //ui->comboBox->setEnabled(false);
    //QTimer::singleShot( 1000, this, SLOT ( slotEnableComboBox() ) );

    QModelIndex indexOfIdTypeOfDiagnosis;
    indexOfIdTypeOfDiagnosis = ui->comboBox->model()->index(ui->comboBox->currentIndex(),1,QModelIndex());
    quint8 idTypeOfDiagnosis = ui->comboBox->model()->data(indexOfIdTypeOfDiagnosis).toInt();
    emit  signalReguestDiagnosisList(idTypeOfDiagnosis);
}

void MyClassDiagnosisSelection::slotTypeOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->comboBox->setModel(tableModel);
}

void MyClassDiagnosisSelection::slotDiagnosisListResponse(QVector<QVector<QString>> myVectorArray)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(myVectorArray.size());
    ui->tableWidget->setColumnCount(myVectorArray[0].size());

    for(int i = 0; i < myVectorArray.size(); i++)
    {
        for (int j = 0; j < myVectorArray[0].size(); j++)
        {
            QTableWidgetItem *itemPointer= new QTableWidgetItem(myVectorArray[i][j]);
            ui->tableWidget->setItem(i, j, itemPointer);
        }
    }

    ui->tableWidget->hideColumn(0);
    ui->tableWidget->resizeColumnToContents(1);
    ui->tableWidget->resizeColumnToContents(2);

}

void MyClassDiagnosisSelection::slotEnableComboBox()
{
    ui->comboBox->setEnabled(true);
}

void MyClassDiagnosisSelection::on_buttonBox_accepted()
{
    QModelIndex indexOfIdDiagnosis;
    indexOfIdDiagnosis = ui->tableWidget->model()->index(ui->tableWidget->currentRow(),0,QModelIndex());
    QString idDiagnosis = ui->tableWidget->model()->data(indexOfIdDiagnosis).toString();

    QModelIndex indexOfMKB10ofDiagnosis;
    indexOfMKB10ofDiagnosis = ui->tableWidget->model()->index(ui->tableWidget->currentRow(),1,QModelIndex());
    QString MKB10ofDiagnosis = ui->tableWidget->model()->data(indexOfMKB10ofDiagnosis).toString();

    QModelIndex indexOfNameOfDiagnosis;
    indexOfNameOfDiagnosis = ui->tableWidget->model()->index(ui->tableWidget->currentRow(),2,QModelIndex());
    QString nameOfDiagnosis = ui->tableWidget->model()->data(indexOfNameOfDiagnosis).toString();

    emit signalDiagnosisResponse(idDiagnosis, MKB10ofDiagnosis + " " + nameOfDiagnosis);
    this->deleteLater();
}

void MyClassDiagnosisSelection::on_buttonBox_rejected()
{
    this->deleteLater();
}


