// xlsxcell_p.h

#pragma once

#include <QtGlobal>
#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "xlsxglobal.h"
#include "xlsxcell.h"
#include "xlsxcellrange.h"
#include "xlsxrichstring.h"
#include "xlsxcellformula.h"

QT_BEGIN_NAMESPACE_XLSX

class CellPrivate
{
    Q_DECLARE_PUBLIC(Cell)
public:
    CellPrivate(Cell *p);
    CellPrivate(const CellPrivate * const cp);
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
