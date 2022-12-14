// xlsxchartsheet.h

#ifndef XLSXCHARTSHEET_H
#define XLSXCHARTSHEET_H

#include <QtGlobal>
#include <QStringList>

#include "xlsxabstractsheet.h"

QT_BEGIN_NAMESPACE_XLSX

class Workbook;
class DocumentPrivate;
class ChartsheetPrivate;
class Chart;

class QXLSX_EXPORT Chartsheet : public AbstractSheet
{
    Q_DECLARE_PRIVATE(Chartsheet)

public:
    ~Chartsheet();
    Chart *chart();

private:
    friend class DocumentPrivate;
    friend class Workbook;

    Chartsheet(const QString &sheetName, int sheetId, Workbook *book, CreateFlag flag);
    Chartsheet *copy(const QString &distName, int distId) const override;

    void saveToXmlFile(QIODevice *device) const override;
    bool loadFromXmlFile(QIODevice *device) override;
};

QT_END_NAMESPACE_XLSX
#endif // XLSXCHARTSHEET_H
