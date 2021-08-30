#include "myclassautorizacion.h"
#include "ui_myclassautorizacion.h"

MyClassAutorizacion::MyClassAutorizacion(QWidget *parent, MyClassSslClient *sslClient) :
    QDialog(parent),
    ui(new Ui::MyClassAutorizacion)
{

    ui->setupUi(this);

    ui->tableView->installEventFilter(this);

    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    setWindowTitle("Выберите пользователя");

    connect(this, &MyClassAutorizacion::signalRequestAccountList, sslClient, &MyClassSslClient::slotRequestAccountList);
    connect(this, &MyClassAutorizacion::signalTryLogin, sslClient, &MyClassSslClient::slotTryLogin);

    connect(sslClient, &MyClassSslClient::signalAccountListResponse, this, &MyClassAutorizacion::slotDisplayAccountList);
    connect(sslClient, &MyClassSslClient::signalTryLoginResponse, this, &MyClassAutorizacion::slotTryLoginResponse);

    emit signalRequestAccountList();


    //Костыль, удалить
    ui->lineEdit->setText("Test");

}

MyClassAutorizacion::~MyClassAutorizacion()
{
    delete ui;
}


void MyClassAutorizacion::slotDisplayAccountList(QVector<QVector<QString>> myVectorArray)
{
    MyClassTableModel *tableModel = new MyClassTableModel(myVectorArray);
    ui->tableView->setModel(tableModel);

    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->hideColumn(0);
    ui->tableView->setFocus();

}

bool MyClassAutorizacion::eventFilter( QObject *obj, QEvent *evt )
{


    if( evt->type() == QEvent::KeyPress)

    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(evt);
        if ( (ui->tableView->hasFocus()) and (keyEvent->key() == Qt::Key_Return or keyEvent->key() == Qt::Key_Enter) )
        {
            ui->lineEdit->setFocus();
        }

    }
    return QWidget::eventFilter( obj, evt );
}

void MyClassAutorizacion::on_pushButton_2_clicked()
{

    QModelIndex indexOfIdUserColumnData;
    indexOfIdUserColumnData = ui->tableView->model()->index(ui->tableView->currentIndex().row(),0,QModelIndex());
    idUser= ui->tableView->model()->data(indexOfIdUserColumnData).toInt();

    QModelIndex indexOfIdUserNameColumnData;
    indexOfIdUserNameColumnData = ui->tableView->model()->index(ui->tableView->currentIndex().row(),1,QModelIndex());
    userName = ui->tableView->model()->data(indexOfIdUserNameColumnData).toString();

    QString  passwordString = ui->lineEdit->text();
    QByteArray passwordByteArray = passwordString.toUtf8();
    QByteArray hashByteArray = QCryptographicHash::hash(passwordByteArray, QCryptographicHash::Sha256);

    emit signalTryLogin(idUser, hashByteArray);

}

void MyClassAutorizacion::slotTryLoginResponse(QVector<QVector<QString>> myVectorArray)
{
    if (myVectorArray[0][0] == "0")
    {
        qDebug() << "Login FAIL";
        QMessageBox messageLoginError;
        messageLoginError.setIcon(QMessageBox::Warning);
        messageLoginError.setText("Неверная пара пользователь/пароль. Попытайтесь еще раз.");
        messageLoginError.exec();
    }
    else
    {
    //Костыль, доработать

        emit signalAuthorization(idUser,userName);

        this->close();
        this->deleteLater();

    }
}

void MyClassAutorizacion::on_pushButton_clicked()
{
    qApp->quit();
}
