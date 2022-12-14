// XlsxTableModel.h

// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx

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

typedef QList<QVariant> VLIST;

class XlsxTableModel : public QAbstractTableModel
{
    Q_OBJECT

    // method that is called by QML script
    Q_PROPERTY(QStringList customRoleNames READ customRoleNames CONSTANT)
public: QStringList customRoleNames();

public: // constrcutor
    XlsxTableModel(const QList<QString> &colTitle, QList<VLIST> data, QObject *parent = NULL);

public: // virtual function of parent object
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

protected:
    void testData(); // test function.

protected:
    QList<VLIST> m_the_data; // table cell data
    QList<QString> m_colNames; // column name
    quint32 m_roleCount; // role count (same as column count)

};

#endif
