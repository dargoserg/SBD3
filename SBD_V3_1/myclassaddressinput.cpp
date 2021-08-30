#include "myclassaddressinput.h"
#include "ui_myclassaddressinput.h"

MyClassAddressInput::MyClassAddressInput(QWidget *parent, MyClassSslClient *sslClient) :
    QDialog(parent),
    ui(new Ui::MyClassAddressInput)
{
    ui->setupUi(this);

    this->setModal(1);

    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    setWindowTitle("Введите адрес");

    //Костыль
    qint32 widthForLabels = 130;

    ui->label->setMinimumWidth(widthForLabels);
    ui->label_2->setMinimumWidth(widthForLabels);
    ui->label_3->setMinimumWidth(widthForLabels);
    ui->label_4->setMinimumWidth(widthForLabels);
    ui->label_5->setMinimumWidth(widthForLabels);
    ui->label_6->setMinimumWidth(widthForLabels);


    connect(this, &MyClassAddressInput::signalRequestDistrictList, sslClient, &MyClassSslClient::slotRequestDistrictList);
    connect(sslClient, &MyClassSslClient::signalDistrictListResponse, this, &MyClassAddressInput::slotDistrictListResponse);

    emit signalRequestDistrictList();
}

MyClassAddressInput::~MyClassAddressInput()
{
    delete ui;
}

void MyClassAddressInput::slotDistrictListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->comboBox->setModel(tableModel);
}

void MyClassAddressInput::on_buttonBox_accepted()
{
    structAddress address;

    address.settlement = ui->lineEdit->text();
    address.street = ui->lineEdit_3->text();
    address.house = ui->lineEdit_4->text();
    address.building = ui->lineEdit_5->text();
    address.apartment = ui->lineEdit_6->text();

    QModelIndex indexOfIdDistrictColumData;
    QModelIndex indexOfNameDistrictColumData;

    indexOfIdDistrictColumData = ui->comboBox->model()->index(ui->comboBox->currentIndex(),1,QModelIndex());
    indexOfNameDistrictColumData = ui->comboBox->model()->index(ui->comboBox->currentIndex(),0,QModelIndex());

    address.districtName = ui->comboBox->model()->data(indexOfNameDistrictColumData).toString();
    address.districtId = ui->comboBox->model()->data(indexOfIdDistrictColumData).toString();

    emit signalAddressResponse(address);
    this->deleteLater();
}

void MyClassAddressInput::on_buttonBox_rejected()
{

    //this->close();
    this->deleteLater();

}
