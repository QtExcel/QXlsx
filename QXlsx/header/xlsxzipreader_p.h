// xlsxzipreader_p.h

#pragma once

// references
class QZipReader;
class QIODevice;

// values
#include <QScopedPointer>
#include <QStringList>

#include "xlsxglobal.h"

QT_BEGIN_NAMESPACE_XLSX

class  ZipReader
{
public:
    explicit ZipReader(const QString &fileName);
    explicit ZipReader(QIODevice *device);
    ~ZipReader();
    bool exists() const;
    QStringList filePaths() const;
    QByteArray fileData(const QString &fileName) const;

private:
    Q_DISABLE_COPY(ZipReader)
    void init();
    QScopedPointer<QZipReader> m_reader;
    QStringList m_filePaths;
};

QT_END_NAMESPACE_XLSX
