// XlsxTab.h

#ifndef XLSXTAB_H
#define XLSXTAB_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QWidget>
#include <QTableWidget>

#include "xlsx.h"

/**
 * @brief xlsx sub-tab widget
 */
class XlsxTab : public QWidget
{
    Q_OBJECT
public:
    explicit XlsxTab(QWidget* parent = nullptr,
                     QXlsx::Document* ptrDoc = nullptr,
                     QXlsx::AbstractSheet* ptrSheet = nullptr,
                     int SheetIndex = -1);
    virtual ~XlsxTab();

signals:

public slots:

private:
    QTableWidget* table;
    QXlsx::Document* document;
    QXlsx::AbstractSheet* sheet;
    int sheetIndex;
private:
    bool setSheet();

};

#endif // XLSXTAB_H
