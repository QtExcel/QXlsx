// xlsxtheme_p.h

#pragma once

#include <QtGlobal>
#include <QString>
#include <QIODevice>

#include "xlsxabstractooxmlfile.h"

QT_BEGIN_NAMESPACE_XLSX

class Theme : public AbstractOOXmlFile
{
public:
    Theme(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const;
    QByteArray saveToXmlData() const;
    bool loadFromXmlData(const QByteArray &data);
    bool loadFromXmlFile(QIODevice *device);

    QByteArray xmlData;
};

QT_END_NAMESPACE_XLSX
