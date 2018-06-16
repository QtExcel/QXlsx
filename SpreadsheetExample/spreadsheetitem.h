// (c) The Qt Company Ltd. BSD License
// Some code is fixed by j2doll.


#ifndef SPREADSHEETITEM_H
#define SPREADSHEETITEM_H

#include "spreadsheet.h"

#include <QTableWidgetItem>

class SpreadSheetItem : public QTableWidgetItem
{
public:
    SpreadSheetItem();
    SpreadSheetItem(const QString &text);

    QTableWidgetItem *clone() const override;

    QVariant data(int role) const override;
    void setData(int role, const QVariant &value) override;
    QVariant display() const;

    inline QString formula() const
    {
        return QTableWidgetItem::data(Qt::DisplayRole).toString();
    }

    static QVariant computeFormula(const QString &formula,
                                   const QTableWidget *widget,
                                   const QTableWidgetItem *self = 0);

private:
    mutable bool isResolving;
};

#endif // SPREADSHEETITEM_H

