// XlsxModel.cpp

#include "XlsxModel.h"

#include <QDebug>
#include <QVariant>

#include <sstream>


XlsxModel::XlsxModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    initData();
}

void XlsxModel::initData()
{
    // test code

    // | 1     | 2  | 3     | col.count is 3.
    // |-------|----|-------|
    // | Alpha | 10 | 100.0 | row count is 4.
    // | Beta  | 20 | 200.0 |
    // | Gamma | 30 | 300.0 |
    // | Delta | 40 | 400.0 |

    // set name of column

    m_colNames.append( QString( "COL1" ) );
    m_colNames.append( QString( "COL2" ) );
    m_colNames.append( QString( "COL3" ) );

    m_roleCount = m_colNames.size();

    // set data

    VLIST list1;
    list1.append(QVariant("Alpha"));
    list1.append(QVariant(10));
    list1.append(QVariant(100.0));
    m_the_data.append( list1 );

    VLIST list2;
    list2.append(QVariant("Beta"));
    list2.append(QVariant(20));
    list2.append(QVariant(200.0));
    m_the_data.append( list2 );

    VLIST list3;
    list3.append(QVariant("Gamma"));
    list3.append(QVariant(30));
    list3.append(QVariant(300.0));
    m_the_data.append( list3 );

    VLIST list4;
    list4.append(QVariant("Delta"));
    list4.append(QVariant(40));
    list4.append(QVariant(400.0));
    m_the_data.append( list4 );

}

void XlsxModel::setValues(QList<QString> colTitle, QList<VLIST> data)
{
    // TODO: set xlsx data

    // m_colNames
    // m_roleCount
    // m_the_data
}

int XlsxModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_the_data.size();
}

int XlsxModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_roleCount;
}

QVariant XlsxModel::data(const QModelIndex& index, int role) const
{
    // current column & row
    int col = index.column();
    int row = index.row();

    // check boudaries
    if ( col < 0 || columnCount() <= col ||
         row < 0 || rowCount()    <= row )
    {
        qDebug() << "[Warning]"
                << " col=" << col
                << ", row="  << row;
        return QVariant();
    }

    // Nominal case

    QVariant ret;
    int cmpRole;

    for (int ic = 0; ic < m_the_data.size() ; ic++)
    {
        if ( row == ic )
        {
            QList<QVariant> vList = m_the_data.at(ic);
            for (int jc = 0; jc < vList.size() ; jc++ )
            {
                int plusOneRole = (int)(Qt::UserRole);
                plusOneRole = plusOneRole + 1;
                cmpRole = plusOneRole + jc;
                if ( role == cmpRole )
                {
                    QVariant var = vList.at(jc);
                    ret = var;
                }
            }
        }
    }

    qDebug()
    << "data: "
    << " col="    << col
    << ", row="   << row
    << ", role=" << role
    << ", cmpRole=" << cmpRole
    << ", value=" << ret.toString();

    return ret;
}

QHash<int, QByteArray> XlsxModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    for ( int ic = 0 ; ic < m_roleCount ; ic++)
    {
        QString strRole = m_colNames.at(ic);
        int roleNo = (Qt::UserRole+1) + ic;
        roles.insert( roleNo, strRole.toLatin1() );
    }

    return roles;
}

// Return ordered List of user-defined roles
QStringList XlsxModel::customRoleNames()
{
    QMap<int, QString> res;
    QHashIterator<int, QByteArray> i(roleNames());

    while ( i.hasNext() )
    {
        i.next();
        if ( i.key() > Qt::UserRole )
        {
            res[ i.key() ] = i.value();
        }
    }

    return res.values();
}


