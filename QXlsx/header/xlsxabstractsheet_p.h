// xlsxabstractsheet_p/h

#pragma once

// values
#include <QString>
#include <QSharedPointer>

#include "xlsxglobal.h"

#include "xlsxabstractsheet.h"
#include "xlsxabstractooxmlfile_p.h"
#include "xlsxdrawing_p.h"

QT_BEGIN_NAMESPACE_XLSX

class AbstractSheetPrivate : public AbstractOOXmlFilePrivate
{
    Q_DECLARE_PUBLIC(AbstractSheet)
public:
    AbstractSheetPrivate(AbstractSheet *p, AbstractSheet::CreateFlag flag);
    ~AbstractSheetPrivate();

    Workbook *workbook;
    QSharedPointer<Drawing> drawing;

    QString name;
    int id;
    AbstractSheet::SheetState sheetState;
    AbstractSheet::SheetType type;
};

QT_END_NAMESPACE_XLSX
