#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sslClient = new MyClassSslClient("","","",1);
    MyClassAutorizacion *Autorization = new MyClassAutorizacion(this,sslClient);

    connect(Autorization, &MyClassAutorizacion::signalAuthorization,
            this, &MainWindow::slotAuthorization);

    Autorization->show();
    dataStore = new mcDataStore(sslClient,this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////Slots

void MainWindow::slotAuthorization(qint64 idUserIn, QString userNameIn)
{
    idUser = idUserIn;
    userName = userNameIn;
    this->setWindowTitle(version + " " + userName);

    connect(this, &MainWindow::signalRequestMonthAndYear,
            sslClient, &MyClassSslClient::slotReguestMonthAndYear);
    connect(sslClient, &MyClassSslClient::signalMonthAndYearResponse,
            this ,&MainWindow::slotMonthAndYearResponse);
    emit signalRequestMonthAndYear();
    ui->comboBox_2->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    comboBoxFilling();

    connect(this, &MainWindow::signalTrySave,
            sslClient, &MyClassSslClient::slotTrySave);



}

void MainWindow::slotMonthAndYearResponse(QVector<QVector<QString>> myVectorArray)
{
    ui->comboBox_2->setCurrentIndex(myVectorArray[0][0].toInt()-1);
    ui->label_21->setText(myVectorArray[0][1]);

    record.dateOfRecord = myVectorArray[0][1] + "-" + myVectorArray[0][0] + "-" + "01";
}

void MainWindow::slotAddress(structAddress address)
{
    record.house = address.house;
    record.street = address.street;
    record.building = address.building;
    record.apartment = address.apartment;
    record.settlement = address.settlement;
    record.idDistrict = address.districtId;

    QString addressString = address.settlement +
                            ", район - " + address.districtName +
                            ", ул." + address.street +
                            ", д." + address.house +
                            ", корпус " + address.building +
                            ", квартира " + address.apartment;
    ui->textBrowser_2->setText(addressString);
}

void MainWindow::slotLocationOfDiagnosis(QString idLocationOfDiagnosis, QString nameLocationOfDiagnosis)
{
    record.idLocationOfDiagnosis = idLocationOfDiagnosis;
    ui->textBrowser->setText(nameLocationOfDiagnosis);
}

void MainWindow::slotDiagnosis(QString idDiagnosis, QString nameOfDiagnosis)
{
    record.idDiagnosis = idDiagnosis;
    ui->textBrowser_3->setText(nameOfDiagnosis);
}

void MainWindow::slotTypeLocationOfDiagnosisListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->comboBox->setModel(tableModel);
}

void MainWindow::slotWorkingPositionListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->comboBox_3->setModel(tableModel);
}
/*
void MainWindow::slotTypeOfSettlementListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    //modelStruct->typeOfSettlementList = tableModel;
    ui->comboBox_4->setModel(tableModel);
}
*/
void MainWindow::slotSocialGroupListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->comboBox_5->setModel(tableModel);
}

void MainWindow::slotPatientCategoryListResponse(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->comboBox_6->setModel(tableModel);
}

void MainWindow::slotCircumstancesOfTheDiagnosisListResponse(QVector<QVector<QString>> myVectorArray)
 {
     MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
     ui->comboBox_7->setModel(tableModel);
 }
/*
 void MainWindow::slotMedicsListResponse(QVector<QVector<QString>> myVectorArray)
 {    
     MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
     modelStruct->medicList = tableModel;
     ui->comboBox_8->setModel(tableModel);
 }
*/
 void MainWindow::slotLaboratoryConfirmationListResponse(QVector<QVector<QString>> myVectorArray)
 {
     MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
     ui->comboBox_9->setModel(tableModel);
     //delete tableModel;
 }


//////////////////////////*Slots


//////////////////////////Button

void MainWindow::on_pushButton_clicked()
{
    MyClassLocationOfDiagnosisSelection *locationOfDiagnosisSelection = new MyClassLocationOfDiagnosisSelection(this, sslClient);
    connect(locationOfDiagnosisSelection, &MyClassLocationOfDiagnosisSelection::signalLocationOfDiagnosisResponse,
            this, &MainWindow::slotLocationOfDiagnosis);
    locationOfDiagnosisSelection->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    MyClassAddressInput *addressInput = new MyClassAddressInput(this, sslClient);
    connect(addressInput, &MyClassAddressInput::signalAddressResponse,
            this, &MainWindow::slotAddress);
    addressInput->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    MyClassDiagnosisSelection *diagnosisSelection = new MyClassDiagnosisSelection(this, sslClient, dataStore);
    connect(diagnosisSelection, &MyClassDiagnosisSelection::signalDiagnosisResponse,
            this, &MainWindow::slotDiagnosis);
    diagnosisSelection->show();
}

void MainWindow::on_pushButton_4_clicked()
{

    record.fam = ui->lineEdit->text();
    record.name = ui->lineEdit_2->text();
    record.otch = ui->lineEdit_3->text();

    record.dateOfBirth = ui->dateEdit->dateTime().toString("yyyy-MM-dd");

    if (ui->checkBox_2->isChecked())
    {
        record.idSex = "1";
    }
    else
    {
        record.idSex = "2";
    }

    record.workPlace = ui->lineEdit_4->text();

    record.dateOfAppeal = ui->dateEdit_2->dateTime().toString("yyyy-MM-dd");

    QModelIndex indexIdWorkingPosition;
    indexIdWorkingPosition = ui->comboBox_3->model()->index(ui->comboBox_3->currentIndex(),1,QModelIndex());
    record.idWorkingPosition = ui->comboBox_3->model()->data(indexIdWorkingPosition).toString();


    QModelIndex indexIdTypeOfSettlement;
    indexIdTypeOfSettlement = ui->comboBox_4->model()->index(ui->comboBox_4->currentIndex(),1,QModelIndex());
    record.idTypeOfSettlement = ui->comboBox_4->model()->data(indexIdTypeOfSettlement).toString();

    QModelIndex indexIdSocialGroup;
    indexIdSocialGroup = ui->comboBox_5->model()->index(ui->comboBox_5->currentIndex(),1,QModelIndex());
    record.idSocialGroup = ui->comboBox_5->model()->data(indexIdSocialGroup).toString();

    QModelIndex indexIdPatientCategory;
    indexIdPatientCategory = ui->comboBox_6->model()->index(ui->comboBox_6->currentIndex(),1,QModelIndex());
    record.idPatientCategory = ui->comboBox_6->model()->data(indexIdPatientCategory).toString();

    QModelIndex indexIdCircumstancesOfTheDiagnosis;
    indexIdCircumstancesOfTheDiagnosis = ui->comboBox_7->model()->index(ui->comboBox_7->currentIndex(),1,QModelIndex());
    record.idCircumstancesOfTheDiagnosis = ui->comboBox_7->model()->data(indexIdCircumstancesOfTheDiagnosis).toString();

    record.dateOfDiagnosis  = ui->dateEdit_3->dateTime().toString("yyyy-MM-dd");

    if (ui->checkBox->isChecked())
    {
        record.idMedic = "64";
        // 64 Неизвестный медик

        record.medic = ui->lineEdit_5->text();
    }
    else
    {
        QModelIndex indexIdMedic;
        QModelIndex indexMedic;
        indexIdMedic = ui->comboBox_8->model()->index(ui->comboBox_8->currentIndex(),1,QModelIndex());
        indexMedic = ui->comboBox_8->model()->index(ui->comboBox_8->currentIndex(),0,QModelIndex());

        record.idMedic = ui->comboBox_8->model()->data(indexIdMedic).toString();
        record.medic = ui->comboBox_8->model()->data(indexMedic).toString();
    }

    if (ui->checkBox_2->isChecked())
    {
        record.idLaboratoryConfirmation = "13";
        // 13 Другое лаб подтверждение

        record.laboratoryConfirmation = ui->lineEdit_6->text();
    }
    else
    {
        QModelIndex indexIdLaboratoryConfirmation;
        QModelIndex indexLaboratoryConfirmation;
        indexIdLaboratoryConfirmation = ui->comboBox_9->model()->index(ui->comboBox_9->currentIndex(),1,QModelIndex());
        indexLaboratoryConfirmation = ui->comboBox_9->model()->index(ui->comboBox_9->currentIndex(),0,QModelIndex());

        record.idLaboratoryConfirmation = ui->comboBox_9->model()->data(indexIdLaboratoryConfirmation).toString();
        record.laboratoryConfirmation = ui->comboBox_9->model()->data(indexLaboratoryConfirmation).toString();
    }

    emit signalTrySave(record);

}


//////////////////////////*Button

void MainWindow::comboBoxFilling()
{
    //Type Location Of Diagnosis ComboBox
    connect(this, &MainWindow::signalRequestTypeLocationOfDiagnosisList,
            sslClient, &MyClassSslClient::slotRequestTypeLocationOfDiagnosisList);
    connect(sslClient, &MyClassSslClient::signalTypeLocationOfDiagnosisListResponse,
            this ,&MainWindow::slotTypeLocationOfDiagnosisListResponse);
    emit signalRequestTypeLocationOfDiagnosisList();
    ui->comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Type Location Of Diagnosis ComboBox

    //Working Position ComboBox
    connect(this, &MainWindow::signalRequestWorkingPositionList,
            sslClient, &MyClassSslClient::slotRequestWorkingPositionList);
    connect(sslClient, &MyClassSslClient::signalWorkingPositionListResponse,
            this ,&MainWindow::slotWorkingPositionListResponse);
    emit signalRequestWorkingPositionList();
    ui->comboBox_3->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Working Position ComboBox

    //Type Of Settlement ComboBox
    ui->comboBox_4->setModel(dataStore->getTypeOfSettlementListModel());
    ui->comboBox_4->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Type Of Settlement ComboBox

    //Social Group ComboBox
    connect(this, &MainWindow::signalReguestSocialGroupList,
            sslClient, &MyClassSslClient::slotRequestSocialGroupList);
    connect(sslClient, &MyClassSslClient::signalSocialGroupListResponse,
            this ,&MainWindow::slotSocialGroupListResponse);
    emit signalReguestSocialGroupList();
    ui->comboBox_5->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Social Group ComboBox

    //Patient Category ComboBox
    connect(this, &MainWindow::signalRequestPatientCategoryList,
            sslClient, &MyClassSslClient::slotRequestPatientCategoryList);
    connect(sslClient, &MyClassSslClient::signalPatientCategoryListResponse,
            this ,&MainWindow::slotPatientCategoryListResponse);
    emit signalRequestPatientCategoryList();
    ui->comboBox_6->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Patient Category ComboBox

    //Circumstances Of The Diagnosis ComboBox
    connect(this, &MainWindow::signalRequestCircumstancesOfTheDiagnosisList,
            sslClient, &MyClassSslClient::slotRequestCircumstancesOfTheDiagnosisList);
    connect(sslClient, &MyClassSslClient::signalCircumstancesOfTheDiagnosisListResponse,
            this ,&MainWindow::slotCircumstancesOfTheDiagnosisListResponse);
    emit signalRequestCircumstancesOfTheDiagnosisList();
    ui->comboBox_7->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Circumstances Of The Diagnosis ComboBox

    //Medics ComboBox

    ui->comboBox_8->setModel(dataStore->getMedicsListModel());

/*
    connect(this, &MainWindow::signalRequestMedicsList,
            sslClient, &MyClassSslClient::slotRequestMedicsList);
    connect(sslClient, &MyClassSslClient::signalMedicsListResponse,
            this ,&MainWindow::slotMedicsListResponse);
    emit signalRequestMedicsList();
    */
    ui->comboBox_8->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Medics ComboBox

    //Laboratory Confirmation ComboBox
    connect(this, &MainWindow::signalRequestLaboratoryConfirmationList,
            sslClient, &MyClassSslClient::slotRequestLaboratoryConfirmationList);
    connect(sslClient, &MyClassSslClient::signalLaboratoryConfirmationListResponse,
            this ,&MainWindow::slotLaboratoryConfirmationListResponse);
    emit signalRequestLaboratoryConfirmationList();
    ui->comboBox_9->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //*Laboratory Confirmation ComboBox

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        ui->comboBox_8->setDisabled(true);
        ui->lineEdit_5->setEnabled(true);
    }
    if (arg1 == 0)
    {
        ui->comboBox_8->setEnabled(true);
        ui->lineEdit_5->setDisabled(true);
        ui->lineEdit_5->setText("");
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1 == 2)
    {
        ui->comboBox_9->setDisabled(true);
        ui->lineEdit_6->setEnabled(true);
    }
    if (arg1 == 0)
    {
        ui->comboBox_9->setEnabled(true);
        ui->lineEdit_6->setDisabled(true);
        ui->lineEdit_6->setText("");
    }
}
