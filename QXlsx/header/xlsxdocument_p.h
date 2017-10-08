//--------------------------------------------------------------------
//
// QXlsx https://github.com/j2doll/QXlsx
//
// GPL License v3 https://www.gnu.org/licenses/gpl-3.0.en.html
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//--------------------------------------------------------------------

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

#include "xlsxdocument.h"
#include "xlsxworkbook.h"
#include "xlsxcontenttypes_p.h"

#include <QMap>

namespace QXlsx {

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

}

#endif // XLSXDOCUMENT_P_H
