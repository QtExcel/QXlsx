// xlsxtheme_p.h

#ifndef XLSXTHEME_H
#define XLSXTHEME_H

#include <QtGlobal>
#include <QString>
#include <QIODevice>

#include "xlsxabstractooxmlfile.h"

QT_BEGIN_NAMESPACE_XLSX

class Theme : public AbstractOOXmlFile
{
public:
    Theme(CreateFlag flag);

    void saveToXmlFile(QIODevice *device) const override;
    QByteArray saveToXmlData() const override;
    bool loadFromXmlData(const QByteArray &data) override;
    bool loadFromXmlFile(QIODevice *device) override;

    QByteArray xmlData;
};

QT_END_NAMESPACE_XLSX

#endif // XLSXTHEME_H
