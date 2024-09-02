// xlsxzipwriter_p.h

#ifndef QXLSX_ZIPWRITER_H
#define QXLSX_ZIPWRITER_H

#include "xlsxglobal.h"

#include <QIODevice>
#include <QString>

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

#endif // QXLSX_ZIPWRITER_H
