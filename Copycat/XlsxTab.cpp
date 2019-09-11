// XlsxTab.cpp

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QLayout>
#include <QVBoxLayout>
#include <QVariant>
#include <QFont>
#include <QBrush>
#include <QDebug>
#include <QTextCharFormat>

#include "XlsxTab.h"
#include "xlsxcell.h"
#include "xlsxformat.h"

XlsxTab::XlsxTab(QWidget* parent,
                 QXlsx::Document* ptrDoc,
                 QXlsx::AbstractSheet* ptrSheet,
                 int SheetIndex)
    : QWidget(parent)
{
    table = NULL;
    sheet = NULL;
    sheetIndex = -1;

    if ( NULL == ptrSheet )
        return;

    table = new XlsxTableWidget( this );
    Q_ASSERT( NULL != table );

    // set layout
    vLayout = new QVBoxLayout;
    vLayout->addWidget(table);
    this->setLayout(vLayout);

    document = ptrDoc; // set document
    sheet = ptrSheet; // set sheet data
    sheetIndex = SheetIndex; // set shett index
    if ( ! setSheet() )
    {
    }

}

XlsxTab::~XlsxTab()
{

    if ( NULL != vLayout )
    {
        vLayout->deleteLater();
        vLayout = NULL;
    }

    if ( NULL != table )
    {
        table->clear();
        table->deleteLater();
        table = NULL;
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
      // NOTE: This part should be modified later.
      //  The maximum value of the sheet should be set to an appropriate value.
    table->setRowCount( maxRow  );
    table->setColumnCount( maxCol );

    for ( int ic = 0; ic < clList.size(); ++ic )
    {
          // cell location
          CellLocation cl = clList.at(ic);

          ////////////////////////////////////////////////////////////////////
          /// NOTE: First cell index of tableWidget is 0(zero).
          ///       But, first cell of Qxlsx document is 1(one).

          int row = cl.row - 1;
          int col = cl.col - 1;

          ////////////////////////////////////////////////////////////////////
          /// cell pointer

          QSharedPointer<Cell> ptrCell = cl.cell;

          ////////////////////////////////////////////////////////////////////
          /// create new item of table widget

          QTableWidgetItem* newItem = new QTableWidgetItem();

          ///////////////////////////////////////////////////////////////////
          /// value of cell

            QVariant var = cl.cell.data()->value(); // cell value
            QString str;
            Cell::CellType cType = cl.cell->cellType();

            // qDebug() << "(r,c) = " << cl.row << cl.col << var.toString()  ;

            str = var.toString();

          ////////////////////////////////////////////////////////////////////
          /// set text

          newItem->setText( str );

          ////////////////////////////////////////////////////////////////////
          /// set item

          table->setItem( row, col, newItem );

          // TODO: set label of table widget ('A', 'B', 'C', ...)
              // QTableWidgetItem *QTableWidget::horizontalHeaderItem(int column) const
              // QTableWidgetItem *QTableWidget::verticalHeaderItem(int row) const

            ////////////////////////////////////////////////////////////////////
            /// row height and column width

            double dRowHeight = wsheet->rowHeight( cl.row );
            double dColWidth  = wsheet->columnWidth( cl.col );

            // qDebug() <<" ROW HEIGHT: "  << dRowHeight << " COLUMN WIDTH: " << dColWidth;

            double wWidth = cellWidthToWidgetWidth( dColWidth );
            double wHeight = cellHeightToWidgetHeight( dRowHeight );

            table->setRowHeight( row, wHeight );
            table->setColumnWidth( col, wWidth );

          ////////////////////////////////////////////////////////////////////
          /// font

          newItem->setFont( ptrCell->format().font() );

          ////////////////////////////////////////////////////////////////////
          /// font color

          if ( ptrCell->format().fontColor().isValid() )
          {
            newItem->setTextColor( ptrCell->format().fontColor() );
          }

          ////////////////////////////////////////////////////////////////////
          /// background color

          {
              QColor clrForeGround = ptrCell->format().patternForegroundColor();
              if ( clrForeGround.isValid() )
              {
                    // qDebug() << "[debug] ForeGround : " << clrForeGround;
              }

              QColor clrBackGround = ptrCell->format().patternBackgroundColor();
              if ( clrBackGround.isValid() )
              {
                    // TODO: You must use various patterns.
                    newItem->setBackground( Qt::SolidPattern );
                    newItem->setBackgroundColor( clrBackGround );
              }
          }

          ////////////////////////////////////////////////////////////////////
          /// pattern

          Format::FillPattern fp = ptrCell->format().fillPattern();
          Qt::BrushStyle qbs = Qt::NoBrush;
          switch(fp)
          {
              case Format::PatternNone :       qbs = Qt::NoBrush; break;
              case Format::PatternSolid :      qbs = Qt::SolidPattern; break;
              case Format::PatternMediumGray :
              case Format::PatternDarkGray :
              case Format::PatternLightGray :
              case Format::PatternDarkHorizontal :
              case Format::PatternDarkVertical :
              case Format::PatternDarkDown :
              case Format::PatternDarkUp :
              case Format::PatternDarkGrid :
              case Format::PatternDarkTrellis :
              case Format::PatternLightHorizontal :
              case Format::PatternLightVertical :
              case Format::PatternLightDown :
              case Format::PatternLightUp :
              case Format::PatternLightTrellis :
              case Format::PatternGray125 :
              case Format::PatternGray0625 :
              case Format::PatternLightGrid :
              default:
              break;
          }

        /*
        QBrush qbr( ptrCell->format().patternForegroundColor(), qbs );
        newItem->setBackground( qbr );
        newItem->setBackgroundColor( ptrCell->format().patternBackgroundColor() );
        */

          ////////////////////////////////////////////////////////////////////
          /// alignment

          int alignment = 0;
          Format::HorizontalAlignment ha = ptrCell->format().horizontalAlignment();
          switch(ha)
          {
            case Format::AlignHCenter :
            case Format::AlignHFill :
            case Format::AlignHMerge :
            case Format::AlignHDistributed :
                alignment = alignment | Qt::AlignHCenter;
            break;

            case Format::AlignRight :
                alignment = alignment | Qt::AlignRight;
            break;

            case Format::AlignHJustify :
                alignment = alignment | Qt::AlignJustify;
            break;

            case Format::AlignLeft :
            case Format::AlignHGeneral :
            default:
                alignment = alignment | Qt::AlignLeft;
            break;
          }

          Format::VerticalAlignment va = ptrCell->format().verticalAlignment();
          switch(va)
          {
              case Format::AlignTop :
                  alignment = alignment |  Qt::AlignTop;
              break;

              case Format::AlignVCenter :
                  alignment = alignment |  Qt::AlignVCenter;
              break;

              case Format::AlignBottom :
                  alignment = alignment |  Qt::AlignBottom;
              break;

              case Format::AlignVJustify :
              case Format::AlignVDistributed :
              default:
                // alignment = alignment | (int)(Qt::AlignBaseline);
                alignment = alignment | QTextCharFormat::AlignBaseline;
              break;
          }

          newItem->setTextAlignment( alignment );

          ////////////////////////////////////////////////////////////////////

    }

    // dev56

    ////////////////////////////////////////////////////////////////////
    /// merged cell

    QList<CellRange> mergeCellRangeList = wsheet->mergedCells();
    for ( int mc = 0; mc < mergeCellRangeList.size(); ++mc )
    {
        CellRange mergedCellRange = mergeCellRangeList.at(mc);

        CellReference crTopLeft = mergedCellRange.topLeft();
        int tlCol = crTopLeft.column();
        int tlRow = crTopLeft.row();

        CellReference crBottomRight = mergedCellRange.bottomRight();
        int brCol = crBottomRight.column();
        int brRow = crBottomRight.row();

        // row : tlRow ~ brRow
        // col : tlCol ~ brCol

        /// NOTE: First cell index of tableWidget is 0(zero).
        ///       But, first cell of Qxlsx document is 1(one).

        int rowSpan = brRow - tlRow + 1;
        int colSpan = brCol - tlCol + 1;

        table->setSpan( (tlRow - 1), (tlCol - 1), rowSpan, colSpan );

        // qDebug() << "[merged cell] [topLeft]" << tlRow << tlCol << " [bottomRight] " << brRow << brCol ;

    }


    return true;
}

std::string XlsxTab::convertFromNumberToExcelColumn(int n)
{
    // main code from https://www.geeksforgeeks.org/find-excel-column-name-given-number/
    // Function to print Excel column name for a given column number

    std::string stdString;

    char str[1000]; // To store result (Excel column name)
    int i = 0; // To store current index in str which is result

    while ( n > 0 )
    {
        // Find remainder
        int rem = n % 26;

        // If remainder is 0, then a 'Z' must be there in output
        if ( rem == 0 )
        {
            str[i++] = 'Z';
            n = (n/26) - 1;
        }
        else // If remainder is non-zero
        {
            str[i++] = (rem-1) + 'A';
            n = n / 26;
        }
    }
    str[i] = '\0';

    // Reverse the string and print result
    std::reverse( str, str + strlen(str) );

    stdString = str;
    return stdString;
}

// 72 points (DPI) = 1 inch = 2.54 cm = 96 pixels
// 1 PT(point) = 1.333 PX(pixel) (point is a absolute unit.)
// 1 PX(pixel) = 0.75  PT(point) (pixel is a relative unit.) (In Windows. Mac is diffrent.)

double XlsxTab::cellWidthToWidgetWidth(double width)
{
    // unit of width is a character. default value is 8.43.
    // 8.43 characters = 64 pixel = 48 point (in Windows)

    double ret = width * (double(64) / double(8.43));
    return ret;
}

double XlsxTab::cellHeightToWidgetHeight(double height)
{
    // default value is 16.5 point
    // 3 point = 4 pixel

    double ret = height * (double(3) / double(4));
    return ret;
}


