// XlsxTab.cpp

#include "XlsxTab.h"

#include <QLayout>
#include <QVBoxLayout>
#include <QVariant>
#include <QDebug>

XlsxTab::XlsxTab(QWidget* parent,
                 QXlsx::AbstractSheet* ptrSheet,
                 int SheetIndex)
    : QWidget(parent)
{
    table = NULL;
    sheet = NULL;
    sheetIndex = -1;

    if ( NULL != ptrSheet )
    {
        table = new QTableWidget;

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(table);

        this->setLayout(layout);

        sheet = ptrSheet; // set sheet data
        sheetIndex = SheetIndex; // set shett index
        setSheet();
    }

}

XlsxTab::~XlsxTab()
{
    if ( NULL != table )
    {
        table->deleteLater();
    }
}

bool XlsxTab::setSheet()
{
    if ( NULL == sheet )
        return false;

    if ( NULL == table )
        return false;

    sheet->workbook()->setActiveSheet( sheetIndex );
    Worksheet* wsheet = (Worksheet*) sheet->workbook()->activeSheet();
    if ( NULL == wsheet )
        return false;

    qDebug() << wsheet->sheetName() << "----------";

    // TODO: get max row count and column count of sheet
    table->setRowCount(100);
    table->setColumnCount(100);

    int maxRow = -1;
    int maxCol = -1;
    QVector<CellLocation> clList = wsheet->getFullCells();
    for (int ic = 0; ic < clList.size(); ++ic) {
          CellLocation cl = clList.at(ic);

          int row = cl.row - 1;
          if ( row > maxRow ) maxRow = row;

          int col = cl.col - 1;
          if ( col > maxCol ) maxCol = col;

          QVariant var = cl.cell.data()->value();
          QString str = var.toString();

          qDebug() << " row:" << row << " col:" << col << " val:"<< str;

          QTableWidgetItem *newItem = new QTableWidgetItem(str);
          table->setItem(row, col, newItem);
    }

    table->setRowCount(maxRow + 1);
    table->setColumnCount(maxCol + 1);

    return true;
}
