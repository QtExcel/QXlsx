// xlsxzipwriter_p.h

#pragma once

// references
class QIODevice ;
class QString ;

#include "xlsxglobal.h"

class QZipWriter;

QT_BEGIN_NAMESPACE_XLSX

class ZipWriter
{
public:
    explicit ZipWriter(const QString &filePath);
    explicit ZipWriter(QIODevice *device);
    ~ZipWriter();

    void addFile(const QString &filePath, QIODevice *device);
    void addFile(const QString &filePath, const QByteArray &data);
    bool error() const;
    void close();

private:
    QZipWriter *m_writer;
};

QT_END_NAMESPACE_XLSX
