#include "myclasslocationofdiagnosisselection.h"
#include "ui_myclasslocationofdiagnosisselection.h"

MyClassLocationOfDiagnosisSelection::MyClassLocationOfDiagnosisSelection(QWidget *parent, MyClassSslClient *sslClient) :
    QDialog(parent),
    ui(new Ui::MyClassLocationOfDiagnosisSelection)
{
    ui->setupUi(this);
    this->setModal(1);
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );

    setWindowTitle("Выберите место выявления");

    connect(this, &MyClassLocationOfDiagnosisSelection::signalRequestLocationOfDiagnosisList,
            sslClient, &MyClassSslClient::slotRequestLocationOfDiagnosisList);
    connect(sslClient, &MyClassSslClient::signalLocationOfDiagnosisListResponse,
            this, &MyClassLocationOfDiagnosisSelection::slotLocationOfDiagnosisListResponse);

    emit signalRequestLocationOfDiagnosisList();
}

MyClassLocationOfDiagnosisSelection::~MyClassLocationOfDiagnosisSelection()
{
    ui->tableWidget->clear();
    delete ui;
}

void MyClassLocationOfDiagnosisSelection::slotLocationOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray)
{
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
}



void MyClassLocationOfDiagnosisSelection::on_pushButton_clicked()
{
    searchItemList =  ui->tableWidget->findItems(ui->lineEdit->text(),Qt::MatchFixedString|Qt::MatchContains);
    if (searchItemList.size() > 0)
    {
        currentSerchListPosition = 0;
        ui->tableWidget->setCurrentCell(searchItemList[ currentSerchListPosition ] -> row(),1);
        ui->pushButton_2->setEnabled(1);
    }
}

void MyClassLocationOfDiagnosisSelection::on_pushButton_2_clicked()
{
    currentSerchListPosition++;
    if (searchItemList.size() > currentSerchListPosition)
    {
        ui->tableWidget->setCurrentCell(searchItemList[ currentSerchListPosition ] -> row(),1);
    }
    else
    {

    }

}

void MyClassLocationOfDiagnosisSelection::on_buttonBox_accepted()
{
    QModelIndex indexOfIdLocationOfDiagnosisData;
    QModelIndex indexOfNameLocationOfDiagnosisData;

    indexOfIdLocationOfDiagnosisData = ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),0,QModelIndex());
    indexOfNameLocationOfDiagnosisData = ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),1,QModelIndex());

    QString idLocationOfDiagnosis = ui->tableWidget->model()->data(indexOfIdLocationOfDiagnosisData).toString();
    QString nameLocationOfDiagnosis = ui->tableWidget->model()->data(indexOfNameLocationOfDiagnosisData).toString();

    emit signalLocationOfDiagnosisResponse(idLocationOfDiagnosis, nameLocationOfDiagnosis);

    this->deleteLater();
}

void MyClassLocationOfDiagnosisSelection::on_buttonBox_rejected()
{
    this->deleteLater();
}
