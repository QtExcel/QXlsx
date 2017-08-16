/****************************************************************************
** MIT License
** initial code is made by  Debao Zhang <hello@debao.me>
**
**  fixed by j2doll (https://github.com/j2doll/)
**   https://github.com/dbzhang800/QtXlsxWriter/issues/108
**   https://github.com/dbzhang800/QtXlsxWriter/issues/117
****************************************************************************/

#include "xlsxzipreader_p.h"

#include <private/qzipreader_p.h>

#include <QVector> // https://github.com/dbzhang800/QtXlsxWriter/issues/108

namespace QXlsx {

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

    // https://github.com/dbzhang800/QtXlsxWriter/issues/117
    // QList<QZipReader::FileInfo> allFiles = m_reader->fileInfoList(); // before
    QVector<QZipReader::FileInfo> allFiles = m_reader->fileInfoList(); // after

    foreach (const QZipReader::FileInfo &fi, allFiles) {
        if (fi.isFile)
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

} // namespace QXlsx
