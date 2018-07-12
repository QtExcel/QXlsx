// XlsxModel.h

#ifndef XLSX_MODEL_H
#define XLSX_MODEL_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include <QMap>
#include <QVariant>
#include <QAbstractTableModel>

#include <string>
#include <vector>
#include <cstdlib>

class XlsxModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList customRoleNames READ customRoleNames CONSTANT)

    typedef QList<QVariant> VLIST;

public:
    XlsxModel(QObject *parent = NULL);

// virtual function of parent object
public:
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

public:
    QStringList customRoleNames();

public:
    void setValues(QList<QString> colTitle, QList<VLIST> data);

protected:
    void initData();

protected:
    QList<VLIST> m_the_data;
    QList<QString> m_colNames;
    quint32 m_roleCount;

};

#endif
