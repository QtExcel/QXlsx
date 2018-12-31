// CopycatTableModel.cpp
// QXlsx // MIT License // https://github.com/j2doll/QXlsx

#include "CopycatTableModel.h"

#include <QDebug>
#include <QVariant>

CopycatTableModel::CopycatTableModel(QList<QString> colTitle, QList<VLIST> data, QObject *parent)
    : QAbstractTableModel(parent)
{
        // [1] set name of column

        for ( int ic = 0; ic < colTitle.size() ; ic++ )
        {
            std::string colString = convertFromNumberToExcelColumn( ic );
            // QString strCol = colTitle.at(ic);
            QString strCol = QString::fromStdString( colString );
            m_colNames.append( strCol );
        }
        m_roleCount = m_colNames.size();

        // [2]  set data

        for ( int dc = 0; dc < data.size() ; dc++ )
        {
            VLIST vList = data.at(dc);
            m_the_data.append( vList );
        }
}

int CopycatTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_the_data.size();
}

int CopycatTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_roleCount;
}

QVariant CopycatTableModel::data(const QModelIndex& index, int role) const
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
                    if ( ! var.isValid() )
                        var.setValue( QString("") ) ;
                    if ( var.isNull() )
                        var.setValue( QString("") ) ;
                    ret = var;
                }
            }
        }
    }

    return ret;
}

std::string CopycatTableModel::convertFromNumberToExcelColumn(int n)
{
    // main code from https://www.geeksforgeeks.org/find-excel-column-name-given-number/
    // Function to print Excel column name for a given column number

    std::string stdString;

    char str[1000]; // To store result (Excel column name)
    int i = 0; // To store current index in str which is result

    while ( n > 0 )
    {
        // Find remainder
        int rem = n % 26;

        // If remainder is 0, then a 'Z' must be there in output
        if ( rem == 0 )
        {
            str[i++] = 'Z';
            n = (n/26) - 1;
        }
        else // If remainder is non-zero
        {
            str[i++] = (rem-1) + 'A';
            n = n / 26;
        }
    }
    str[i] = '\0';

    // Reverse the string and print result
    std::reverse( str, str + strlen(str) );

    stdString = str;
    return stdString;
}

