#include "myclasstablemodel.h"
#include "QDebug"

MyClassTableModel::MyClassTableModel(QVector<QVector<QString>> myVectorArray)
{
    myPrivateVectorArray = myVectorArray;
    /*
    for (int i=0;i < myPrivateVectorArray[0].size(); i++)
    {
        myHorizontalHeaders.append("1");
    }
    */

}

int MyClassTableModel::rowCount(const QModelIndex &parent) const
{
    return myPrivateVectorArray.size();
}

int MyClassTableModel::columnCount(const QModelIndex &parent) const
{
    return myPrivateVectorArray[0].size();
}

QVariant MyClassTableModel::data(const QModelIndex &index, int role) const
{
   if (role == Qt::DisplayRole)
   {
       QString answer = myPrivateVectorArray[index.row()][index.column()];
       return QVariant(answer);
   }

   return QVariant();
}
/*
QVariant MyClassTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (myHorizontalHeaders.size()>section)
    {
        QString unswer = myHorizontalHeaders[section];
        return  QVariant(unswer);
    }
    return  QVariant();
}
*/
/*
bool MyClassTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{

    qDebug()<<"Set" << section;

    int i;
    i = myHorizontalHeaders.size();

    qDebug()<<i;


    if (myHorizontalHeaders.size()>section)
    {
        myHorizontalHeaders[section] = value.toString();
        return true;
    }
    return false;

}
*/
