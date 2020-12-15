// xlsxdrwaing_p.h

#pragma once

#include <QtGlobal>
#include <QList>
#include <QString>
#include <QSharedPointer>

#include "xlsxrelationships_p.h"
#include "xlsxabstractooxmlfile.h"

class QIODevice;
class QXmlStreamWriter;

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
