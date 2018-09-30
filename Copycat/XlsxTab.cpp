// XlsxTab.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QLayout>
#include <QVBoxLayout>
#include <QVariant>
#include <QFont>
#include <QDebug>

#include "XlsxTab.h"
#include "xlsxcell.h"

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
          QSharedPointer<Cell> ptrCell = cl.cell;

          QVariant var = cl.cell.data()->value();
          QString str = var.toString();

          QTableWidgetItem *newItem = new QTableWidgetItem(str);

          // set item
          table->setItem( row, col, newItem );

          // font
          newItem->setFont( ptrCell->format().font() );

          // font color
          newItem->setTextColor( ptrCell->format().fontColor() );

          // ptrCell->format().patternBackgroundColor()
          // ptrCell->format().patternForegroundColor()
          // newItem->setBackgroundColor( ptrCell->format().patternBackgroundColor() );
          // newItem->setBackgroundColor( ptrCell->format().patternForegroundColor() );
          // newItem->setBackgroundColor( ptrCell->format().diagonalBorderColor() );

          // alignment
          int alignment = 0;
          Format::HorizontalAlignment ha = ptrCell->format().horizontalAlignment();
          switch(ha)
          {
            case Format::HorizontalAlignment::AlignHCenter :
            case Format::HorizontalAlignment::AlignHFill :
            case Format::HorizontalAlignment::AlignHMerge :
            case Format::HorizontalAlignment::AlignHDistributed :
                alignment = alignment | Qt::AlignHCenter;
            break;

            case Format::HorizontalAlignment::AlignRight :
                alignment = alignment | Qt::AlignRight;
            break;

            case Format::HorizontalAlignment::AlignHJustify :
                alignment = alignment | Qt::AlignJustify;
            break;

            case Format::HorizontalAlignment::AlignLeft :
            case Format::HorizontalAlignment::AlignHGeneral :
            default:
                alignment = alignment | Qt::AlignLeft;
            break;
          }

          Format::VerticalAlignment va = ptrCell->format().verticalAlignment();
          switch(va)
          {
              case Format::VerticalAlignment::AlignTop :
                  alignment = alignment |  Qt::AlignTop;
              break;

              case Format::VerticalAlignment::AlignVCenter :
                  alignment = alignment |  Qt::AlignVCenter;
              break;

              case Format::VerticalAlignment::AlignBottom :
                  alignment = alignment |  Qt::AlignBottom;
              break;

              case Format::VerticalAlignment::AlignVJustify :
              case Format::VerticalAlignment::AlignVDistributed :
              default:
                alignment = alignment |  Qt::AlignBaseline;
              break;
          }

          newItem->setTextAlignment( alignment );
    }

    return true;
}
