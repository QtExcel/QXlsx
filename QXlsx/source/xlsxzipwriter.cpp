// xlsxzipwriter.cpp

#include "xlsxzipwriter_p.h"

#include <private/qzipwriter_p.h>

#include <QDebug>
#ifndef QT_NO_TEMPORARYFILE
#include <QSaveFile>
#endif

QT_BEGIN_NAMESPACE_XLSX

namespace {

class NonClosingDevice : public QIODevice
{
public:
    explicit NonClosingDevice(QIODevice *device)
        : m_device(device)
    {
        if (device->isOpen())
            QIODevice::open(device->openMode());
    }

    bool open(OpenMode mode) override
    {
        if (!m_device->isOpen() && !m_device->open(mode))
            return false;
        return QIODevice::open(m_device->openMode());
    }

    bool isSequential() const override { return m_device->isSequential(); }
    qint64 pos() const override { return m_device->pos(); }
    qint64 size() const override { return m_device->size(); }

    bool seek(qint64 position) override
    {
        if (!m_device->seek(position))
            return false;
        return QIODevice::seek(position);
    }

protected:
    qint64 readData(char *data, qint64 maxSize) override { return m_device->read(data, maxSize); }
    qint64 writeData(const char *data, qint64 maxSize) override
    {
        return m_device->write(data, maxSize);
    }

private:
    QIODevice *m_device;
};

} // namespace

ZipWriter::ZipWriter(const QString &filePath)
{
    m_writer = new QZipWriter(filePath, QIODevice::WriteOnly);
    m_writer->setCompressionPolicy(QZipWriter::AutoCompress);
}

ZipWriter::ZipWriter(QIODevice *device)
{
#ifndef QT_NO_TEMPORARYFILE
    if (qobject_cast<QSaveFile *>(device))
        m_deviceProxy.reset(new NonClosingDevice(device));
#endif
    m_writer = new QZipWriter(m_deviceProxy ? m_deviceProxy.data() : device);
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
