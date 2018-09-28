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
        if ( ! setSheet() )
        {

        }
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

    // set active sheet
    sheet->workbook()->setActiveSheet( sheetIndex );
    Worksheet* wsheet = (Worksheet*) sheet->workbook()->activeSheet();
    if ( NULL == wsheet )
        return false;

    // get full cells of sheet
    int maxRow = -1;
    int maxCol = -1;
    QVector<CellLocation> clList = wsheet->getFullCells( &maxRow, &maxCol );

    // set max count of row,col
    table->setRowCount( maxRow  );
    table->setColumnCount( maxCol );

    for ( int ic = 0; ic < clList.size(); ++ic )
    {
          CellLocation cl = clList.at(ic);

          // First cell of tableWidget is 0.
          // But first cell of Qxlsx document is 1.
          int row = cl.row - 1;
          int col = cl.col - 1;

          QVariant var = cl.cell.data()->value();
          QString str = var.toString();

          QTableWidgetItem *newItem = new QTableWidgetItem(str);
          table->setItem(row, col, newItem);
    }

    return true;
}
