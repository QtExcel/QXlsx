// CopycatTableModel.h
// QXlsx // MIT License // https://github.com/j2doll/QXlsx

#ifndef XLSX_MODEL_H
#define XLSX_MODEL_H

#include <cstdio>
#include <cstdlib>

#include <string>
#include <vector>
#include <sstream>

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include <QMap>
#include <QVariant>
#include <QAbstractTableModel>

typedef QList<QVariant> VLIST;

class CopycatTableModel : public QAbstractTableModel
{
    Q_OBJECT

public: // constrcutor
    CopycatTableModel(QList<QString> colTitle, QList<VLIST> data, QObject *parent = NULL);

public: // virtual function of parent object
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

protected:
    QList<VLIST> m_the_data; // table cell data
    QList<QString> m_colNames; // column name
    quint32 m_roleCount; // role count (same as column count)

    std::string convertFromNumberToExcelColumn(int n);
};

#endif
