// XlsxTab.h

#ifndef XLSXTAB_H
#define XLSXTAB_H

#include <QtGlobal>
#include <QWidget>
#include <QTableWidget>

#include "xlsx.h"

class XlsxTab : public QWidget
{
    Q_OBJECT
public:
    explicit XlsxTab(QWidget* parent = nullptr, QXlsx::AbstractSheet* ptrSheet = nullptr);
    virtual ~XlsxTab();

signals:

public slots:

protected:
    QTableWidget* table;

};

#endif // XLSXTAB_H
