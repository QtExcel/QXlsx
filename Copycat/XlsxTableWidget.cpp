// XlsxTableWidget.cpp

#include <QDebug>
#include <QTime>

#include <QList>
#include <QTableWidgetSelectionRange>

#include "XlsxTableWidget.h"

XlsxTableWidget::XlsxTableWidget(QWidget* parent)
    : QTableWidget(parent)
{
    //
}

XlsxTableWidget::~XlsxTableWidget()
{

}

void XlsxTableWidget::mousePressEvent(QMouseEvent *event)
{
    QTableWidget::mousePressEvent(event);

    if ( event->button() == Qt::RightButton )
    {
        // qDebug() << "right button is pressed";

        QList<QTableWidgetItem *> items = this->selectedItems();

        // selected range

        QList<QTableWidgetSelectionRange> ranges = this->selectedRanges();
        for (int ic = 0 ; ic < ranges.size(); ic++ )
        {
            QTableWidgetSelectionRange range = ranges.at(ic);

            int rowCount = range.rowCount();

            int topRow = range.topRow();
            int bottomRow = range.bottomRow();

            int colCount = range.columnCount();

            int leftCol = range.leftColumn();
            int rightCol = range.rightColumn();

            qDebug()
            << QTime::currentTime();

            qDebug()
            << "row: "     << rowCount << " : "
            << " top:"     << topRow
            << ", bottom:" << bottomRow ;

            qDebug()
            << "col: "   << colCount << " : "
            << " left:"  << leftCol
            << " right:" << rightCol ;

        }

    }
} 

