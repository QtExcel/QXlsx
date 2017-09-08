/****************************************************************************
** Copyright (c) 2013-2014 Debao Zhang <hello@debao.me>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#ifndef XLSXGLOBAL_H
#define XLSXGLOBAL_H
#include <QtGlobal>

#define QT_BEGIN_NAMESPACE_XLSX namespace QXlsx {
#define QT_END_NAMESPACE_XLSX }
#define QTXLSX_USE_NAMESPACE using namespace QXlsx;

#if !defined(QT_STATIC) && !defined(XLSX_NO_LIB)
#  if defined(QT_BUILD_XLSX_LIB)
#    define Q_XLSX_EXPORT Q_DECL_EXPORT
#  else
#    define Q_XLSX_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_XLSX_EXPORT
#endif

#ifdef XLSX_TEST
#  define XLSX_AUTOTEST_EXPORT Q_XLSX_EXPORT
#else
#  define XLSX_AUTOTEST_EXPORT
#endif

#endif // XLSXGLOBAL_H
