#ifndef MYCLASSAUTORIZACION_H
#define MYCLASSAUTORIZACION_H
#include <QDialog>
#include <QKeyEvent>
#include <QEvent>
#include <QCryptographicHash>
#include <QMessageBox>


#include <myclasssslclient.h>
#include <myclasstablemodel.h>

namespace Ui {
class MyClassAutorizacion;
}

class MyClassAutorizacion : public QDialog
{
    Q_OBJECT

public:
    explicit MyClassAutorizacion(QWidget *parent = nullptr, MyClassSslClient *sslClient = nullptr);
    ~MyClassAutorizacion();


public slots:
    void slotDisplayAccountList(QVector<QVector<QString>> myVectorArray);
    void slotTryLoginResponse(QVector<QVector<QString>> myVectorArray);

signals:
    void signalRequestAccountList();
    void signalTryLogin(qint64 accountNumber, QByteArray passwordHash);
    void signalAuthorization(qint64 idUser, QString userName);


private:
    Ui::MyClassAutorizacion *ui;

    qint64 idUser;
    QString userName;

protected:
    virtual bool eventFilter( QObject *, QEvent * );

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};
#endif // MYCLASSAUTORIZACION_H
