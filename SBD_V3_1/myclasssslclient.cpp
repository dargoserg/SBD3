#include "myclasssslclient.h"

MyClassSslClient::MyClassSslClient(QString pathToPrivateKey, QString pathToLocalCertificate,QString serverAddress, int port)
{
    sslSocket = new QSslSocket(this);


    //sslSocket->setProtocol(QSsl::TlsV1_2OrLater);


    qDebug()<<"Support SSL "<<sslSocket->supportsSsl();
    qDebug()<<"Version Build" << sslSocket->sslLibraryBuildVersionString();
    qDebug()<<"Version " << sslSocket->sslLibraryVersionString();


    //sslSocket->setPrivateKey("C:/Cert/new/client/client_key.pem");
    //sslSocket->setLocalCertificate("C:/Cert/new/client/KVD_client.crt");

    sizeOfReceivedMessage = 0;

    connect(sslSocket, &QSslSocket::encrypted, this, &MyClassSslClient::slotEncrypted);

    sslSocket->connectToHostEncrypted("myserver.kvd", 3366);
    //sslSocket->connectToHost("myserver.kvd", 3366);
    //sslSocket->connectToHostEncrypted("127.0.0.1", 3366);

    if (sslSocket->waitForEncrypted(5000))
    {
        qDebug()<<"Encript";
    }
    else
    {
        qDebug()<<"NOT Encript";
        qDebug()<<sslSocket->errorString();
        qDebug()<<sslSocket->sslHandshakeErrors();
        qDebug()<<sslSocket->supportsSsl();
    }


}

void MyClassSslClient::slotEncrypted()
{
    //qDebug()<<"Socket Encrypted";
    connect(sslSocket, &QSslSocket::readyRead, this, &MyClassSslClient::slotReadyRead);
}

void MyClassSslClient::slotReadyRead()
{


    verificationMessage();


    /*
    while (sslSocket->bytesAvailable() < sizeOfReceivedMessage)
    {

        if (!sslSocket->waitForReadyRead(5000))
        {
            qDebug()<<"Превышен интервал ожидания следующего пакета";
            qDebug() << "sizeOfMessage =" << sizeOfMessage << " sslSocket->bytesAvailable() = " << sslSocket->bytesAvailable() ;
            qDebug() << sslSocket->error();
            qDebug() << sslSocket->errorString();
            qDebug() << sslSocket->readBufferSize();
        }
    }
    */

}

void MyClassSslClient::verificationMessage()
{

    //qDebug()<<"ReadyRead";
    //sizeof(sizeOfReceivedMessage) = sizeof(qint64) = 8
    if ((sizeOfReceivedMessage == 0) and (sslSocket->bytesAvailable( ) >= 8))
    {
        sizeOfReceivedMessage = readSizeOfMessage();
        qDebug() << "sizeOfMessage =" << sizeOfReceivedMessage << " sslSocket->bytesAvailable() = " << sslSocket->bytesAvailable() ;

        if (sslSocket->bytesAvailable() ==  sizeOfReceivedMessage)
        {
            logicSwitch(sizeOfReceivedMessage);
            sizeOfReceivedMessage = 0;
            qDebug() << "This message end";
        }

        if (sslSocket->bytesAvailable() >  sizeOfReceivedMessage)
        {
            logicSwitch(sizeOfReceivedMessage);
            sizeOfReceivedMessage = 0;
            qDebug() << "Messages not end";
            verificationMessage();
        }

        if (sslSocket->bytesAvailable() <  sizeOfReceivedMessage)
        {
            qDebug() << "This message not end";
        }
    }


    if ((sizeOfReceivedMessage != 0) and (sslSocket->bytesAvailable() >= sizeOfReceivedMessage))
    {
         qDebug() << "sizeOfMessage =" << sizeOfReceivedMessage << " sslSocket->bytesAvailable() = " << sslSocket->bytesAvailable() ;
        if (sslSocket->bytesAvailable() ==  sizeOfReceivedMessage)
        {
            logicSwitch(sizeOfReceivedMessage);
            sizeOfReceivedMessage = 0;
            qDebug() << "This message end";
        }

        if (sslSocket->bytesAvailable() >  sizeOfReceivedMessage)
        {
            logicSwitch(sizeOfReceivedMessage);
            sizeOfReceivedMessage = 0;
            qDebug() << "Messages not end";
            verificationMessage();
        }

    }
}

//////////////////////////Logic
void MyClassSslClient::logicSwitch(qint64 sizeOfMessage)
{
    quint8 typeOfMessage = readTypeOfMessage();


    // Размер сообщения уменьшается т.к прочитали переменную typeOfMessage размером в 1 байт из него.
    // sizeof(typeOfMessage) = sizeof(quint8) = 1;
    sizeOfMessage = sizeOfMessage - 1;

    qDebug()<< "Type of message = " <<typeOfMessage;

    switch (typeOfMessage)
    {
        case 1:
        {
            accountListResponse(sizeOfMessage);
            break;
        }
        case 2:
        {
            tryLoginResponse(sizeOfMessage);
            break;
        }

        case 20:
        {
            monthAndYearResponse(sizeOfMessage);
            break;
        }

        case 101:
        {
            districtListResponse(sizeOfMessage);
            break;
        }
        case 102:
        {
            locationOfDiagnosisListResponse(sizeOfMessage);
            break;
        }
        case 103:
        {
            typeOfDiagnosisResponse(sizeOfMessage);
            break;
        }
        case 104:
        {
            diagnosisResponse(sizeOfMessage);
            break;
        }
        case 105:
        {
            typeLocationOfDiagnosisResponse(sizeOfMessage);
            break;
        }
        case 106:
        {
            workingPositionListResponse(sizeOfMessage);
            break;
        }
        case 107:
        {
            socialGroupListResponse(sizeOfMessage);
            break;
        }
        case 108:
        {
            patientCategoryListResponse(sizeOfMessage);
            break;
        }
        case 109:
        {
            circumstancesOfTheDiagnosisListResponse(sizeOfMessage);
            break;
        }
        case 110:
        {
            medicsListResponse(sizeOfMessage);
            break;
        }
        case 111:
        {
            laboratoryConfirmationListResponse(sizeOfMessage);
            break;
        }

        case 112:
        {
            typeOfSettlementListResponse(sizeOfMessage);
            break;
        }








    }

}
//////////////////////////*Logic

//////////////////////////MessageFunction
qint64 MyClassSslClient::readSizeOfMessage()
{
    QByteArray sizeOfMessageByteArray = sslSocket->read(8);
    QDataStream sizeOfMessageDataStream(&sizeOfMessageByteArray,QIODevice::ReadOnly);

    qint64 sizeOfMessage;
    sizeOfMessageDataStream >> sizeOfMessage;

    return sizeOfMessage;
}


bool MyClassSslClient::waitForReadyRead(int milliseconds)
{
    QEventLoop eventLoop;
    QTimer timer;

    connect(sslSocket, &QSslSocket::readyRead , &eventLoop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);

    timer.setSingleShot(true);
    timer.start(milliseconds);

    eventLoop.exec();
    return timer.isActive();
}


quint8 MyClassSslClient::readTypeOfMessage()
{
    QByteArray typeOfMessageByteArray = sslSocket->read(1);
    QDataStream typeOfMessageDataStream(&typeOfMessageByteArray,QIODevice::ReadOnly);

    quint8 typeOfMessage;
    typeOfMessageDataStream >> typeOfMessage;

    return typeOfMessage;
}

//////////////////////////*MessageFunction


//////////////////////////Response

void MyClassSslClient::accountListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> accountListVectorArray  = read2dVector(sizeOfMessage);
    emit signalAccountListResponse(accountListVectorArray);
}

void MyClassSslClient::tryLoginResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> tryLoginAnswerVectorArray  = read2dVector(sizeOfMessage);
    emit signalTryLoginResponse(tryLoginAnswerVectorArray);
}

void MyClassSslClient::monthAndYearResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> monthAndYearVectorArray  = read2dVector(sizeOfMessage);
    emit signalMonthAndYearResponse(monthAndYearVectorArray);
}

void MyClassSslClient::districtListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> districtListVectorArray = read2dVector(sizeOfMessage);
    emit signalDistrictListResponse(districtListVectorArray);
}

void MyClassSslClient::locationOfDiagnosisListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> locationOfDiagnosisListVectorArray = read2dVector(sizeOfMessage);
    emit signalLocationOfDiagnosisListResponse(locationOfDiagnosisListVectorArray);
}

void MyClassSslClient::typeOfDiagnosisResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> typeOfDiagnosisListVectorArray = read2dVector(sizeOfMessage);
    emit signalTypeOfDiagnosisListResponse(typeOfDiagnosisListVectorArray);
}

void MyClassSslClient::diagnosisResponse(qint64 sizeOfMessage)
{

    QVector<QVector<QString>> diagnosisListVectorArray = read2dVector(sizeOfMessage);
    emit signalDiagnosisListResponse(diagnosisListVectorArray);
}

void MyClassSslClient::typeLocationOfDiagnosisResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> typeLocationOfDiagnosisListVectorArray = read2dVector(sizeOfMessage);
    emit signalTypeLocationOfDiagnosisListResponse(typeLocationOfDiagnosisListVectorArray);
}

void MyClassSslClient::workingPositionListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> workingPositionListVectorArray = read2dVector(sizeOfMessage);
    emit signalWorkingPositionListResponse(workingPositionListVectorArray);
}

void MyClassSslClient::socialGroupListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> socialGroupListVectorArray = read2dVector(sizeOfMessage);
    emit signalSocialGroupListResponse(socialGroupListVectorArray);
}

void MyClassSslClient::patientCategoryListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> patientCategoryListVectorArray = read2dVector(sizeOfMessage);
    emit signalPatientCategoryListResponse(patientCategoryListVectorArray);
}

void MyClassSslClient::circumstancesOfTheDiagnosisListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> circumstancesOfTheDiagnosisListVectorArray = read2dVector(sizeOfMessage);
    emit signalCircumstancesOfTheDiagnosisListResponse(circumstancesOfTheDiagnosisListVectorArray);
}

void MyClassSslClient::medicsListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> medicsListVectorArray = read2dVector(sizeOfMessage);
    emit signalMedicsListResponse(medicsListVectorArray);
}

void MyClassSslClient::laboratoryConfirmationListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> LaboratoryConfirmationListVectorArray = read2dVector(sizeOfMessage);
    emit signalLaboratoryConfirmationListResponse(LaboratoryConfirmationListVectorArray);
}

void MyClassSslClient::typeOfSettlementListResponse(qint64 sizeOfMessage)
{
    QVector<QVector<QString>> typeOfSettlementListVectorArray = read2dVector(sizeOfMessage);
    emit signalTypeOfSettlementListResponse(typeOfSettlementListVectorArray);
}

//////////////////////////*Response


//////////////////////////Slot

void MyClassSslClient::slotRequestAccountList()
{
    quint8 typeOfMessage;
    typeOfMessage = 1;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotTryLogin(qint64 accountNumber, QByteArray passwordHash)
{

    quint8 typeOfMessage;
    typeOfMessage = 2;

    QByteArray dataByteArray;
    QDataStream myDataStream(&dataByteArray, QIODevice::WriteOnly);
    myDataStream << accountNumber;

    myDataStream.writeRawData(passwordHash,passwordHash.size());

    sendData(typeOfMessage,dataByteArray);
}

void MyClassSslClient::slotReguestMonthAndYear()
{
    quint8 typeOfMessage;
    typeOfMessage = 20;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestDistrictList()
{
    quint8 typeOfMessage;
    typeOfMessage = 101;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestLocationOfDiagnosisList()
{
    quint8 typeOfMessage;
    typeOfMessage = 102;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestTypeOfDiagnosisList()
{
    quint8 typeOfMessage;
    typeOfMessage = 103;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestDiagnosisList(quint8 idTypeOfDiagnosis)
{
    quint8 typeOfMessage;
    typeOfMessage = 104;

    QByteArray dataByteArray;
    QDataStream myDataStream(&dataByteArray, QIODevice::WriteOnly);
    myDataStream << idTypeOfDiagnosis;

    sendData(typeOfMessage, dataByteArray);
}

void MyClassSslClient::slotRequestTypeLocationOfDiagnosisList()
{
    qDebug()<<"slotRequestTypeLocationOfDiagnosisList";
    quint8 typeOfMessage;
    typeOfMessage = 105;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestWorkingPositionList()
{
    qDebug()<<"slotRequestWorkingPositionList";
    quint8 typeOfMessage;
    typeOfMessage = 106;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestSocialGroupList()
{
    qDebug()<<"slotRequestSocialGroupList";
    quint8 typeOfMessage;
    typeOfMessage = 107;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestPatientCategoryList()
{
     qDebug()<<"slotRequestPatientCategoryList";
    quint8 typeOfMessage;
    typeOfMessage = 108;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestCircumstancesOfTheDiagnosisList()
{
    qDebug()<<"slotRequestCircumstancesOfTheDiagnosisList";
    quint8 typeOfMessage;
    typeOfMessage = 109;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestMedicsList()
{
    qDebug()<<"slotRequestMedicsList";
    quint8 typeOfMessage;
    typeOfMessage = 110;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestLaboratoryConfirmationList()
{
    qDebug()<<"slotRequestLaboratoryConfirmationList";
    quint8 typeOfMessage;
    typeOfMessage = 111;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotRequestTypeOfSettlementList()
{
    qDebug()<<"slotRequestTypeOfSettlementList";
    quint8 typeOfMessage;
    typeOfMessage = 112;

    sendData(typeOfMessage);
}

void MyClassSslClient::slotTrySave(structRecord record)
{
    QVector <QString> recordVector;
    recordVector.append(record.fam);
    recordVector.append(record.name);
    recordVector.append(record.otch);
    recordVector.append(record.dateOfBirth);
    recordVector.append(record.dateOfRecord);
    recordVector.append(record.idSex);
    recordVector.append(record.settlement);
    recordVector.append(record.workPlace);
    recordVector.append(record.dateOfAppeal);
    recordVector.append(record.idWorkingPosition);
    recordVector.append(record.idDistrict);
    recordVector.append(record.street);
    recordVector.append(record.house);
    recordVector.append(record.building);
    recordVector.append(record.apartment);
    recordVector.append(record.idTypeOfSettlement);
    recordVector.append(record.idSocialGroup);
    recordVector.append(record.idPatientCategory);
    recordVector.append(record.idDiagnosis);
    recordVector.append(record.idLocationOfDiagnosis);
    recordVector.append(record.idCircumstancesOfTheDiagnosis);
    recordVector.append(record.dateOfDiagnosis);
    recordVector.append(record.idMedic);
    recordVector.append(record.medic);
    recordVector.append(record.idLaboratoryConfirmation);
    recordVector.append(record.laboratoryConfirmation);
    qDebug()<< recordVector;

}


//////////////////////////*Slot


//////////////////////////DataFunction

void MyClassSslClient::sendData(quint8 typeOfMessage)
{
    qint64 sizeOfMessage = 1;
    // sizeof(typeOfMessage) = sizeof(quint8) = 1;

    QByteArray sizeOfMessageAndTypeByteArray;
    QDataStream myDataStream2(&sizeOfMessageAndTypeByteArray, QIODevice::WriteOnly);
    myDataStream2 << sizeOfMessage;
    myDataStream2 << typeOfMessage;

    sslSocket->write(sizeOfMessageAndTypeByteArray);
}

void MyClassSslClient::sendData(quint8 typeOfMessage, QByteArray data)
{
    qint64 sizeOfMessage;
    sizeOfMessage = data.size() + 1;
    // sizeof(typeOfMessage) = sizeof(quint8) = 1;

    QByteArray sizeOfMessageAndTypeByteArray;
    QDataStream myDataStream2(&sizeOfMessageAndTypeByteArray, QIODevice::WriteOnly);
    myDataStream2 << sizeOfMessage;
    myDataStream2 << typeOfMessage;

    sslSocket->write(sizeOfMessageAndTypeByteArray);
    sslSocket->write(data);
}

QVector<QVector<QString>> MyClassSslClient::read2dVector(qint64 sizeOfMessage)
{
    //sslSocket->openMode()


    QByteArray my2dVectorByteArray = sslSocket->read(sizeOfMessage);
    QDataStream my2dVectorDataStream(&my2dVectorByteArray,QIODevice::ReadOnly);

    QVector<QVector<QString>> my2dVector;
    my2dVectorDataStream >> my2dVector;

    return my2dVector;
}

//////////////////////////*DataFunction


void MyClassSslClient::save()
{

}





















