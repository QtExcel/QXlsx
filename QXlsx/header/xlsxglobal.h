// xlsxglobal.h

#ifndef XLSXGLOBAL_H
#define XLSXGLOBAL_H

#include <cstdio>
#include <iostream>
#include <string>

#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

#if defined(QXlsx_SHAREDLIB)
#    if defined(QXlsx_EXPORTS)
#        define QXLSX_EXPORT Q_DECL_EXPORT
#    else
#        define QXLSX_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define QXLSX_EXPORT
#endif

#define QT_BEGIN_NAMESPACE_XLSX namespace QXlsx {
#define QT_END_NAMESPACE_XLSX }

#define QXLSX_USE_NAMESPACE using namespace QXlsx;

#endif // XLSXGLOBAL_H
