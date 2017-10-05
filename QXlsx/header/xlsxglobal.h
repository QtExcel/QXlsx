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

#ifndef XLSXGLOBAL_H
#define XLSXGLOBAL_H
#include <QtGlobal>

#define QT_BEGIN_NAMESPACE_XLSX namespace QXlsx {
#define QT_END_NAMESPACE_XLSX }
#define QTXLSX_USE_NAMESPACE using namespace QXlsx;
 
#define Q_XLSX_EXPORT // use static lib

#ifdef XLSX_TEST
#  define XLSX_AUTOTEST_EXPORT Q_XLSX_EXPORT
#else
#  define XLSX_AUTOTEST_EXPORT
#endif

#endif // XLSXGLOBAL_H
