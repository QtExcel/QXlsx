// xlsxutility_p.h

#pragma once

// references
class QDateTime ;
class QTime;
class QVariant;

// values
#include <QString> // template QStringList
#include <QStringList>

#include "xlsxglobal.h"

QT_BEGIN_NAMESPACE_XLSX

class CellReference;

bool parseXsdBoolean(const QString &value, bool defaultValue=false);

QStringList splitPath(const QString &path);
QString getRelFilePath(const QString &filePath);

double datetimeToNumber(const QDateTime &dt, bool is1904=false);
QVariant datetimeFromNumber(double num, bool is1904=false);
double timeToNumber(const QTime &t);

QString createSafeSheetName(const QString &nameProposal);
QString escapeSheetName(const QString &sheetName);
QString unescapeSheetName(const QString &sheetName);

bool isSpaceReserveNeeded(const QString &string);

QString convertSharedFormula(const QString &rootFormula, const CellReference &rootCell, const CellReference &cell);

QT_END_NAMESPACE_XLSX
