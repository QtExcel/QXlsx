// xlsxcelllocation.h

#ifndef CELL_LOCATION_H
#define CELL_LOCATION_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QMetaType>

#include <memory>

#include "xlsxglobal.h"

QT_BEGIN_NAMESPACE_XLSX

class Cell;

class QXLSX_EXPORT CellLocation
{
public:
    CellLocation();

    int col;
    int row;

    std::shared_ptr<Cell> cell;
};

QT_END_NAMESPACE_XLSX
#endif
