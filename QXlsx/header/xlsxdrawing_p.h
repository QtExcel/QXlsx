// xlsxdrwaing_p.h

#pragma once

// references
class QIODevice;
class QXmlStreamWriter;

#include <QList>

#include "xlsxrelationships_p.h"
#include "xlsxabstractooxmlfile.h"

QT_BEGIN_NAMESPACE_XLSX

class DrawingAnchor;
class Workbook;
class AbstractSheet;
class MediaFile;

class Drawing : public AbstractOOXmlFile
{
public:
    Drawing(AbstractSheet *sheet, CreateFlag flag);
    ~Drawing();
    void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);

    AbstractSheet *sheet;
    Workbook *workbook;
    QList<DrawingAnchor *> anchors;
};

QT_END_NAMESPACE_XLSX
