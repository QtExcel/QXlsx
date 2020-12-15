// xlsxcelllocation.h

#pragma once

#include <QSharedPointer>

#include "xlsxglobal.h"

QT_BEGIN_NAMESPACE_XLSX

class Cell;

class CellLocation
{
public:
    CellLocation();

    int col;
    int row;

    QSharedPointer<Cell> cell;
};

QT_END_NAMESPACE_XLSX
