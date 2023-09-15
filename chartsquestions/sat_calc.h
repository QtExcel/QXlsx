#ifndef SAT_CALC_H
#define SAT_CALC_H
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"

#include <iostream>

#include <QColor>
#include <QString>
#include <QTextStream>
#include <QtCore>

using namespace QXlsx;

class sat_calc
{
private:
    QString chromatogram;
    double precision;
    QString report_file;
    QString sheet_name;
    int output_line_count;

public:
    void generate_report(void);
    void get_chromatogram(const QString &chromatogram);
    void get_report_file(const QString &report_file);
    void get_sheet_name(const QString &sheet_name);
    void get_precision(const double precision);

    sat_calc();
    ~sat_calc();
};

#endif // SAT_CALC_H
