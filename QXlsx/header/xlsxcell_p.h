// xlsxcell_p.h

#ifndef XLSXCELL_P_H
#define XLSXCELL_P_H

#include "xlsxcell.h"
#include "xlsxcellformula.h"
#include "xlsxcellrange.h"
#include "xlsxglobal.h"
#include "xlsxrichstring.h"

#include <QList>
#include <QObject>
#include <QtGlobal>

QT_BEGIN_NAMESPACE_XLSX

class CellPrivate
{
    Q_DECLARE_PUBLIC(Cell)
public:
    CellPrivate(Cell *p);
    CellPrivate(const CellPrivate *const cp);

public:
    Worksheet *parent;
    Cell *q_ptr;

public:
    Cell::CellType cellType;
    QVariant value;

    CellFormula formula;
    Format format;

    RichString richString;

    qint32 styleNumber;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXCELL_P_H
