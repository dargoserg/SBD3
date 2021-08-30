#ifndef MYCLASSREPORTCREATOR_H
#define MYCLASSREPORTCREATOR_H

#include <QDialog>

namespace Ui {
class myClassReportCreator;
}

class myClassReportCreator : public QDialog
{
    Q_OBJECT

public:
    explicit myClassReportCreator(QWidget *parent = nullptr);
    ~myClassReportCreator();

private:
    Ui::myClassReportCreator *ui;
};

#endif // MYCLASSREPORTCREATOR_H
