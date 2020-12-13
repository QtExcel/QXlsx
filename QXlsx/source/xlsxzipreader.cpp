// xlsxzipreader.cpp

#include "xlsxzipreader_p.h"

#include <private/qzipreader_p.h>

QT_BEGIN_NAMESPACE_XLSX

ZipReader::ZipReader(const QString &filePath) :
    m_reader(new QZipReader(filePath))
{
    init();
}

ZipReader::ZipReader(QIODevice *device) :
    m_reader(new QZipReader(device))
{
    init();
}

ZipReader::~ZipReader()
{

}

void ZipReader::init()
{
    const auto& allFiles = m_reader->fileInfoList();
    for (const auto &fi : allFiles) {
        if (fi.isFile || (!fi.isDir && !fi.isFile && !fi.isSymLink))
            m_filePaths.append(fi.filePath);
    }
}

bool ZipReader::exists() const
{
    return m_reader->exists();
}

QStringList ZipReader::filePaths() const
{
    return m_filePaths;
}

QByteArray ZipReader::fileData(const QString &fileName) const
{
    return m_reader->fileData(fileName);
}

QT_END_NAMESPACE_XLSX
