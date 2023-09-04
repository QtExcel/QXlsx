// xlsxzipwriter.cpp

#include "xlsxzipwriter_p.h"

#include <private/qzipwriter_p.h>

#include <QDebug>
#include <QtGlobal>

QT_BEGIN_NAMESPACE_XLSX

ZipWriter::ZipWriter(const QString &filePath)
{
    m_writer = new QZipWriter(filePath, QIODevice::WriteOnly);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);
}

ZipWriter::ZipWriter(QIODevice *device)
{
    m_writer = new QZipWriter(device);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);
}

ZipWriter::~ZipWriter()
{
    delete m_writer;
}

bool ZipWriter::error() const
{
    return m_writer->status() != QZipWriter::NoError;
}

void ZipWriter::addFile(const QString &filePath, QIODevice *device)
{
    m_writer->addFile(filePath, device);
}

void ZipWriter::addFile(const QString &filePath, const QByteArray &data)
{
    m_writer->addFile(filePath, data);
}

void ZipWriter::close()
{
    m_writer->close();
}

QT_END_NAMESPACE_XLSX
