#ifndef MYCLASSADDRESSINPUT_H
#define MYCLASSADDRESSINPUT_H

#include <QDialog>
#include <myclasssslclient.h>
#include <myclasstablemodel.h>
#include <struct.h>

namespace Ui {
class MyClassAddressInput;
}

class MyClassAddressInput : public QDialog
{
    Q_OBJECT

public:
    explicit MyClassAddressInput(QWidget *parent = nullptr, MyClassSslClient *sslClient = nullptr);
    ~MyClassAddressInput();

signals:
    void signalRequestDistrictList();
    void signalAddressResponse(structAddress address);

public slots:
    void slotDistrictListResponse(QVector<QVector<QString>> myVectorArray);


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::MyClassAddressInput *ui;
};

#endif // MYCLASSADDRESSINPUT_H


