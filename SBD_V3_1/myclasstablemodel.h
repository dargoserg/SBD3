#ifndef MYCLASSTABLEMODEL_H
#define MYCLASSTABLEMODEL_H

#include <QAbstractTableModel>


class MyClassTableModel : public QAbstractTableModel
{
public:
    MyClassTableModel(QVector<QVector<QString>> myVectorArray);
    //bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;


private:
    //QVariant headerData(const int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVector<QVector<QString>> myPrivateVectorArray;
    QVector<QString> myHorizontalHeaders;
};

#endif // MYCLASSTABLEMODEL_H
