// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx

// XlsxTableModel.cpp

#include "XlsxTableModel2.h"

#include <QDebug>
#include <QVariant>

#include <sstream>

XlsxTableModel2::XlsxTableModel2(QList<QString> colTitle, QList<VLIST> data, QObject *parent)
    : QAbstractTableModel(parent)
{
        // [1] set name of column

        for (int ic = 0; ic < colTitle.size() ; ic++ )
        {
            QString strCol = colTitle.at(ic);
            m_colNames.append( strCol );
        }
        m_roleCount = m_colNames.size();

        // [2]  set data

        for (int dc = 0; dc < data.size() ; dc++ )
        {
            VLIST vList = data.at(dc);
            m_the_data.append( vList );
        }
}

int XlsxTableModel2::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_the_data.size();
}

int XlsxTableModel2::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_roleCount;
}

QVariant XlsxTableModel2::data(const QModelIndex& index, int role) const
{
    // current column & row
    int col = index.column();
    int row = index.row();

    // check boudaries
    if ( col < 0 || columnCount() <= col ||
         row < 0 || rowCount()    <= row )
    {
        qDebug() << "[Warning]" << " col=" << col << ", row="  << row;
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
                if ( col == jc &&
                     row == ic )
                {

                    QVariant var = vList.at(jc);
                    if ( ! var.isValid() ) var.setValue( QString("") ) ;
                    if ( var.isNull() ) var.setValue( QString("") ) ;
                    ret = var;
                }
            }
        }
    }

    return ret;
}




