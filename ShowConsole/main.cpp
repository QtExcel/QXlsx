// main.cpp

#include <iostream>
#include <vector>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QVariant>
#include <QtCore>
#include <QtGlobal>
using namespace std;

// [0] include QXlsx headers
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxchartsheet.h"
#include "xlsxdocument.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

#include "fort.hpp" // libfort

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (argc != 2) {
        std::cout << "[Usage] ShowConsole *.xlsx" << std::endl;
        return 0;
    }

    // get xlsx file name
    QString xlsxFileName = argv[1];
    qDebug() << xlsxFileName;

    // tried to load xlsx using temporary document
    QXlsx::Document xlsxTmp(xlsxFileName);
    if (!xlsxTmp.isLoadPackage()) {
        qCritical() << "Failed to load" << xlsxFileName;
        return (-1); // failed to load
    }

    // load new xlsx using new document
    QXlsx::Document xlsxDoc(xlsxFileName);
    xlsxDoc.isLoadPackage();

    int sheetIndexNumber = 0;
    foreach (QString curretnSheetName, xlsxDoc.sheetNames()) {
        QXlsx::AbstractSheet *currentSheet = xlsxDoc.sheet(curretnSheetName);
        if (NULL == currentSheet)
            continue;

        // get full cells of sheet
        int maxRow = -1;
        int maxCol = -1;
        currentSheet->workbook()->setActiveSheet(sheetIndexNumber);
        Worksheet *wsheet = (Worksheet *) currentSheet->workbook()->activeSheet();
        if (NULL == wsheet)
            continue;

        QString strSheetName = wsheet->sheetName(); // sheet name

        // display sheet name
        std::cout << std::string(strSheetName.toLocal8Bit()) << std::endl;

        QVector<CellLocation> clList = wsheet->getFullCells(&maxRow, &maxCol);

        QVector<QVector<QString>> cellValues;
        for (int rc = 0; rc < maxRow; rc++) {
            QVector<QString> tempValue;
            for (int cc = 0; cc < maxCol; cc++) {
                tempValue.push_back(QString(""));
            }
            cellValues.push_back(tempValue);
        }

        for (int ic = 0; ic < clList.size(); ++ic) {
            // cell location
            CellLocation cl = clList.at(ic);

            int row = cl.row - 1;
            int col = cl.col - 1;

            // https://github.com/QtExcel/QXlsx/commit/9ab612ff5c9defc35333799c55b01be31aa66fc2
            // {{
            // QSharedPointer<Cell> ptrCell = cl.cell; // cell pointer
            std::shared_ptr<Cell> ptrCell = cl.cell; // cell pointer

            // value of cell
            // QVariant var = cl.cell.data()->value();
            QVariant var = ptrCell->value();
            // }}

            QString str = var.toString();

            cellValues[row][col] = str;
        }

        fort::table fortTable;
        for (int rc = 0; rc < maxRow; rc++) {
            for (int cc = 0; cc < maxCol; cc++) {
                QString strTemp = cellValues[rc][cc];
                fortTable << std::string(strTemp.toLocal8Bit()); // display value
            }
            fortTable << fort::endr; // change to new row
        }

        std::cout << fortTable.to_string() << std::endl; // display forttable row

        sheetIndexNumber++;
    }

    return 0;
}
