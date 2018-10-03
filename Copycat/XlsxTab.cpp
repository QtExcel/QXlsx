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

    if ( NULL == ptrSheet )
        return;

    table = new QTableWidget;

    // set layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(table);
    this->setLayout(layout);

    sheet = ptrSheet; // set sheet data
    sheetIndex = SheetIndex; // set shett index
    if ( ! setSheet() )
    {
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

          QSharedPointer<Cell> ptrCell = cl.cell; // cell pointer

          // create new item of table widget
          QTableWidgetItem* newItem = new QTableWidgetItem();

          QVariant var = cl.cell.data()->value();
          QString str = var.toString();

          // set text
          newItem->setText( str );

          // set item
          table->setItem( row, col, newItem );

          // font
          newItem->setFont( ptrCell->format().font() );

          // font color
          if ( ptrCell->format().fontColor().isValid() )
          {
            newItem->setTextColor( ptrCell->format().fontColor() );
          }

          // pattern
          Format::FillPattern fp = ptrCell->format().fillPattern();
          Qt::BrushStyle qbs = Qt::NoBrush;
          switch(fp)
          {
              case Format::FillPattern::PatternNone :       qbs = Qt::NoBrush; break;
              case Format::FillPattern::PatternSolid :      qbs = Qt::SolidPattern; break;
              case Format::FillPattern::PatternMediumGray :
              case Format::FillPattern::PatternDarkGray :
              case Format::FillPattern::PatternLightGray :
              case Format::FillPattern::PatternDarkHorizontal :
              case Format::FillPattern::PatternDarkVertical :
              case Format::FillPattern::PatternDarkDown :
              case Format::FillPattern::PatternDarkUp :
              case Format::FillPattern::PatternDarkGrid :
              case Format::FillPattern::PatternDarkTrellis :
              case Format::FillPattern::PatternLightHorizontal :
              case Format::FillPattern::PatternLightVertical :
              case Format::FillPattern::PatternLightDown :
              case Format::FillPattern::PatternLightUp :
              case Format::FillPattern::PatternLightTrellis :
              case Format::FillPattern::PatternGray125 :
              case Format::FillPattern::PatternGray0625 :
              case Format::FillPattern::PatternLightGrid :
              default:
              break;
          }

          /*
        QBrush qbr( ptrCell->format().patternForegroundColor(), qbs );
        newItem->setBackground( qbr );
        newItem->setBackgroundColor( ptrCell->format().patternBackgroundColor() );
        */

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

          newItem->setTextAlignment( alignment ); // set alignment

    }

    return true;
}
