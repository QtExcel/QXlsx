// XlsxTab.h

#ifndef XLSXTAB_H
#define XLSXTAB_H

#include <cstdio>

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QWidget>
#include <QTableWidget>

#include "xlsx.h"
#include "XlsxTableWidget.h"

/**
 * @brief xlsx sub-tab widget
 */
class XlsxTab : public QWidget
{
    Q_OBJECT
public:
    explicit XlsxTab(QWidget* parent = NULL,
                     QXlsx::Document* ptrDoc = NULL,
                     QXlsx::AbstractSheet* ptrSheet = NULL,
                     int SheetIndex = -1);
    virtual ~XlsxTab();

public slots:
signals:

protected:
    XlsxTableWidget* table;
    QXlsx::Document* document;
    QXlsx::AbstractSheet* sheet;
    int sheetIndex;

protected:
    bool setSheet();

};

#endif // XLSXTAB_H
