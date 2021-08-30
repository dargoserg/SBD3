#include "myclassreportcreator.h"
#include "ui_myclassreportcreator.h"

myClassReportCreator::myClassReportCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myClassReportCreator)
{
    ui->setupUi(this);
}

myClassReportCreator::~myClassReportCreator()
{
    delete ui;
}
