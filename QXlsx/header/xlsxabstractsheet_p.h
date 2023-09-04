// xlsxabstractsheet_p/h

#ifndef XLSXABSTRACTSHEET_P_H
#define XLSXABSTRACTSHEET_P_H

#include "xlsxabstractooxmlfile_p.h"
#include "xlsxabstractsheet.h"
#include "xlsxdrawing_p.h"
#include "xlsxglobal.h"

#include <memory>

#include <QString>

QT_BEGIN_NAMESPACE_XLSX

class AbstractSheetPrivate : public AbstractOOXmlFilePrivate
{
    Q_DECLARE_PUBLIC(AbstractSheet)
public:
    AbstractSheetPrivate(AbstractSheet *p, AbstractSheet::CreateFlag flag);
    ~AbstractSheetPrivate();

    Workbook *workbook;
    std::shared_ptr<Drawing> drawing;

    QString name;
    int id;
    AbstractSheet::SheetState sheetState;
    AbstractSheet::SheetType type;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXABSTRACTSHEET_P_H
