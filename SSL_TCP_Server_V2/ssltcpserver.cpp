#include "ssltcpserver.h"

#include <QDataStream>


sslTcpServer::sslTcpServer()
{
    qDebug()<<"Support SSL "<<sslSocket->supportsSsl();
    qDebug()<<"Version Build" << sslSocket->sslLibraryBuildVersionString();
    qDebug()<<"Version " << sslSocket->sslLibraryVersionString();
}

void sslTcpServer::incomingConnection(qintptr socketDescriptor)
{
   //qDebug()<<"Support SSL"<<sslSocket->supportsSsl();


    qDebug()<<"Try to connect";
    sslSocket = new QSslSocket(this);
    //sslSocket->addCaCertificate("C:/Cert/new/CA/CA_KVD.crt");
    sslSocket->setPrivateKey("C:/Cert/new/server/server_key.pem");
    sslSocket->setLocalCertificate("C:/Cert/new/server/KVD_server.crt");
    //sslSocket->setPeerVerifyMode(QSslSocket::VerifyPeer);

    if (sslSocket->setSocketDescriptor(socketDescriptor)) qDebug()<< "Set Socket Descriptor " << socketDescriptor << " Done";
    this->addPendingConnection(sslSocket);

    connect(sslSocket, &QSslSocket::encrypted, this, &sslTcpServer::ready);
    sslSocket->startServerEncryption();
    if ( sslSocket->waitForEncrypted(5000) )
    {
        qDebug()<<"Encrypted -> Done";
    }
    else
    {
        qDebug()<<"Encrypted -> Fail";
        qDebug()<<sslSocket->errorString();
        qDebug()<<sslSocket->sslHandshakeErrors();
        delete sslSocket;
    }


}

void sslTcpServer::ready()
{
    connect(sslSocket, &QSslSocket::readyRead, this, &sslTcpServer::readyRead);
    qDebug()<<"Ready";

}

void sslTcpServer::readyRead()
{
    //Qt буферизирует данные перед отправкой, вероятность того что придет меньше 8 байт - ничтожна
    //Раскомментируй следующий while если ты думаешь иначе
    /*
    while (socket->bytesAvailable()<8)
    {
        if (!socket->waitForReadyRead(10000))
        {
            qDebug()<<"Превышен интервал ожидания следующего пакета";
        }
    }
    */

    if (sslSocket->bytesAvailable()>=8) readMessage();
}

//////////////////////////MessageFunction

void sslTcpServer::readMessage()
{
    qint64 sizeOfMessage = readSizeOfMessage();

    while (sslSocket->bytesAvailable()<sizeOfMessage)
    {
        qDebug() <<  "available " << sslSocket->bytesAvailable() << " on " << sizeOfMessage << " bytes";
        if (!sslSocket->waitForReadyRead(10000))
        {
            qDebug()<<"Wait for ready Read 10 sec";
        }
    }

    quint8 typeOfMessage = readTypeOfMessage();


    // Размер сообщения уменьшается т.к прочитали переменную typeOfMessage размером в 1 байт из него.
    // sizeof(typeOfMessage) = sizeof(quint8) = 1;
    sizeOfMessage = sizeOfMessage - 1;

    switch (typeOfMessage)
    {    
//Login
        case 1:
        {
            accountList();
            break;
        }
        case 2:
        {
            login();
            break;
        }

//*Login

//System
        case 20:
        {
            monthAndYear();
            break;
        }
//*System

//Lists
        case 101:
        {
            districtList();
            break;
        }
        case 102:
        {
            locationOfDiagnosisList();
            break;
        }
        case 103:
        {
            typeOfDiagnosisList();
            break;
        }
        case 104:
        {
            diagnosisList();
            break;
        }
        case 105:
        {
            typeLocationOfDiagnosisList();
            break;
        }
        case 106:
        {
            workingPositionList();
            break;
        }
        case 107:
        {
            socialGroupList();
            break;
        }
        case 108:
        {
            PatientCategoryList();
            break;
        }
        case 109:
        {
            CircumstancesOfTheDiagnosisList();
            break;
        }
        case 110:
        {
            MedicsList();
            break;
        }
        case 111:
        {
            LaboratoryConfirmationList();
            break;
        }
        case 112:
        {
            typeOfSettlementList();
            break;
        }  
//*Lists






    }
    if (sslSocket->bytesAvailable() > 0)
    {
        qDebug() << "Bytes available " << sslSocket->bytesAvailable();
        readMessage();
    }
}


bool sslTcpServer::waitForReadyRead(int milliseconds)
{
    QEventLoop eventLoop;
    QTimer timer;

    connect(sslSocket, &QSslSocket::readyRead, &eventLoop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);

    timer.setSingleShot(true);
    timer.start(milliseconds);

    eventLoop.exec();
    return timer.isActive();
}

qint64 sslTcpServer::readSizeOfMessage()
{
    QByteArray sizeOfMessageByteArray = sslSocket->read(8);
    QDataStream sizeOfMessageDataStream(&sizeOfMessageByteArray,QIODevice::ReadOnly);

    qint64 sizeOfMessage;
    sizeOfMessageDataStream >> sizeOfMessage;

    return sizeOfMessage;
}

quint8 sslTcpServer::readTypeOfMessage()
{
    QByteArray typeOfMessageByteArray = sslSocket->read(1);
    QDataStream typeOfMessageDataStream(&typeOfMessageByteArray,QIODevice::ReadOnly);

    quint8 typeOfMessage;
    typeOfMessageDataStream >> typeOfMessage;

    return typeOfMessage;
}

//////////////////////////*MessageFunction


//////////////////////////DataFunction

void sslTcpServer::sendData(quint8 typeOfMessage, QByteArray data)
{
    qint64 sizeOfMessage;
    sizeOfMessage = data.size() + 1;
    // sizeof(typeOfMessage) = sizeof(quint8) = 1;

    qDebug() << "Size of message =" << data.size();

    QByteArray sizeOfMessageAndTypeByteArray;
    QDataStream steamSerializer(&sizeOfMessageAndTypeByteArray, QIODevice::WriteOnly);
    steamSerializer << sizeOfMessage;
    steamSerializer << typeOfMessage;

    sslSocket->write(sizeOfMessageAndTypeByteArray);
    qDebug() << "Sucsesfully sent data bytes" << sslSocket->write(data);



    //qDebug() << sslSocket->errorString();
    //qDebug() << sslSocket->error();
    //qDebug() << sslSocket->bytesToWrite();
}

QByteArray sslTcpServer::sqlResponseData(QString sqlReguest)
{
    QSqlQuery *query = new QSqlQuery(sqlReguest);

    QByteArray sqlResponseDataByteArray;

    QDataStream steamSerializer(&sqlResponseDataByteArray, QIODevice::WriteOnly);
    steamSerializer << sqlResponseToVector(query);

    return sqlResponseDataByteArray;
}

QVector<QVector<QString>> sslTcpServer::sqlResponseToVector(QSqlQuery *sqlQuery)
{
    QVector<QVector<QString>> tableVector;
    QVector<QString> recordVector;

    if (!sqlQuery->next())
    {
        recordVector.append( "Empty query answer" );
        recordVector.append( "0" );
        tableVector.append(recordVector);
        /*
        recordVector.clear();
        recordVector.append("0");
        tableVector.append(recordVector);
        */
    }
    else
    {
        do
        {
            for ( int i = 0; i < sqlQuery->record().count(); i++ )
            {

                recordVector.append( sqlQuery->value(i).toString() );
            }
            tableVector.append(recordVector);
            recordVector.clear();
        }
        while (sqlQuery->next());
    }

    qDebug() << tableVector;
    return tableVector;
}

//////////////////////////*DataFunction


//////////////////////////CALL

void sslTcpServer::accountList()
{
    //qDebug()<<"accountList";

    quint8 typeOfMessage = 1;

    QString sqlRequest("CALL `users`.`getAccountList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::login()
{
    //qDebug()<<"Login";

    QByteArray accountNumberByteArray = sslSocket->read(8);
    QDataStream myDataStream1(&accountNumberByteArray,QIODevice::ReadOnly);

    qint64 idUser;
    myDataStream1>>idUser;

    QByteArray passwordHash = sslSocket->read(32);

    QString queryString;
    queryString = "CALL `users`.`loginReguest`(" + QString::number( idUser ) +", '" + passwordHash.toHex() + "' )";
    QSqlQuery *query = new QSqlQuery(queryString);

    QByteArray dataByteArray;
    QDataStream myDataStream(&dataByteArray, QIODevice::WriteOnly);
    myDataStream << sqlResponseToVector(query);

    sendData(2,dataByteArray);
}

void sslTcpServer::monthAndYear()
{

    quint8 typeOfMessage = 20;

    QString sqlRequest("CALL `mydb`.`getMonthAndYear`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::districtList()
{
    //qDebug()<<"DistrictList";

    quint8 typeOfMessage = 101;

    QString sqlRequest("CALL `mydb`.`getDistrictList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::locationOfDiagnosisList()
{
    //qDebug()<<"LocationOfDiagnosisList";

    quint8 typeOfMessage = 102;

    QString sqlRequest("CALL `mydb`.`getLocationOfDiagnosisList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::typeOfDiagnosisList()
{
    qDebug() << "TypeOfDiagnosisList";

    quint8 typeOfMessage = 103;

    QString sqlRequest("CALL `mydb`.`getTypeOfDiagnosisList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::diagnosisList()
{
    //qDebug() << "DiagnosisList";

    quint8 typeOfMessage = 104;

    QByteArray idDiagnosisTypeByteArray = sslSocket->read(8);
    QDataStream myDataStream1(&idDiagnosisTypeByteArray,QIODevice::ReadOnly);

    quint8 idDiagnosisType;
    myDataStream1>>idDiagnosisType;

    QString queryString;
    queryString = "CALL `mydb`.`getDiagnosisList`(" + QString::number( idDiagnosisType ) + ")";
    QSqlQuery *query = new QSqlQuery(queryString);

    QByteArray dataByteArray;
    QDataStream myDataStream(&dataByteArray, QIODevice::WriteOnly);
    myDataStream << sqlResponseToVector(query);

    sendData(typeOfMessage,dataByteArray);

}

void sslTcpServer::typeLocationOfDiagnosisList()
{
    qDebug() << "typeLocationOfDiagnosisList";

    quint8 typeOfMessage = 105;

    QString sqlRequest("CALL `mydb`.`getTypeLocationOfDiagnosisList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::workingPositionList()
{
    qDebug() << "Working Position List";
    quint8 typeOfMessage = 106;

    QString sqlRequest("CALL `mydb`.`getWorkingPositionList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::socialGroupList()
{
    qDebug() << "Social Group List";
    quint8 typeOfMessage = 107;

    QString sqlRequest("CALL `mydb`.`getSocialGroupList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);
}

void sslTcpServer::PatientCategoryList()
{
    qDebug() << "Patient Category List";
    quint8 typeOfMessage = 108;

    QString sqlRequest("CALL `mydb`.`getPatientCategoryList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);

}

void sslTcpServer::CircumstancesOfTheDiagnosisList()
{
    qDebug() << "Circumstances Of The Diagnosis List";
    quint8 typeOfMessage = 109;

    QString sqlRequest("CALL `mydb`.`getCircumstancesOfTheDiagnosisList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);

}

void sslTcpServer::MedicsList()
{
    qDebug() << "Medics List";
    quint8 typeOfMessage = 110;

    QString sqlRequest("CALL `mydb`.`getMedicsList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);

}

void sslTcpServer::LaboratoryConfirmationList()
{
    qDebug() << "Laboratory Confirmation List";
    quint8 typeOfMessage = 111;

    QString sqlRequest("CALL `mydb`.`getLaboratoryConfirmationList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);

}

void sslTcpServer::typeOfSettlementList()
{
    qDebug() << "Type Of Settlement List";
    quint8 typeOfMessage = 112;

    QString sqlRequest("CALL `mydb`.`getTypeOfSettlementList`()");
    QByteArray dataByteArray = sqlResponseData(sqlRequest);

    sendData(typeOfMessage,dataByteArray);

}

//////////////////////////*CALL
