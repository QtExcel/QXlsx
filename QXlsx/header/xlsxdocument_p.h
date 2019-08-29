//--------------------------------------------------------------------
//
// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx
//
// QtXlsx
// https://github.com/dbzhang800/QtXlsxWriter
// http://qtxlsx.debao.me/
// MIT License

#ifndef XLSXDOCUMENT_P_H
#define XLSXDOCUMENT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Xlsx API.  It exists for the convenience
// of the Qt Xlsx.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtGlobal>
#include <QMap>

#include "xlsxglobal.h"
#include "xlsxdocument.h"
#include "xlsxworkbook.h"
#include "xlsxcontenttypes_p.h"

QT_BEGIN_NAMESPACE_XLSX

class DocumentPrivate
{
    Q_DECLARE_PUBLIC(Document)
public:
    DocumentPrivate(Document *p);
    void init();

    bool loadPackage(QIODevice *device);
    bool savePackage(QIODevice *device) const;

    Document *q_ptr;
    const QString defaultPackageName; //default name when package name not specified
    QString packageName; //name of the .xlsx file

    QMap<QString, QString> documentProperties; //core, app and custom properties
    QSharedPointer<Workbook> workbook;
    QSharedPointer<ContentTypes> contentTypes;
	bool isLoad; 
};

QT_END_NAMESPACE_XLSX

#endif // XLSXDOCUMENT_P_H
