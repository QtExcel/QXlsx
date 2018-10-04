/****************************************************************************
**
** Copyright (c) 2016, Anton Onishchenko
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without
** specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
** ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "tableprinter.h"

#include <QAbstractItemModel>
#include <QPainter>
#include <QPrinter>

TablePrinter::TablePrinter(QPainter* painter, QPrinter* printer) :
    painter(painter),
    printer(printer) {
    topMargin = 5;
    bottomMargin = 5;
    leftMargin = 10;
    rightMargin = 5;
    headerHeight = 0;
    bottomHeight = 0;
    leftBlank = 0;
    rightBlank = 0;
    maxRowHeight = 1000;
    pen = painter->pen();
    headersFont = painter->font();
    contentFont = painter->font();
    headerColor = painter->pen().color();
    contentColor = painter->pen().color();
    prepare = NULL;
    error = "No error";
}

bool TablePrinter::printTable(const QAbstractItemModel* model, const QVector<int> columnStretch,
                              const QVector<QString> headers) {

    //--------------------------------- error checking -------------------------------------

    int columnCount = model->columnCount();
    int count = columnStretch.count();
    if(count != columnCount) {
        error = "Different columns count in model and in columnStretch";
        return false;
    }
    count = headers.count();
    if(count != columnCount && count != 0) {
        error = "Different columns count in model and in headers";
        return false;
    }
    if(!printer->isValid()) {
        error = "printer.isValid() == false";
        return false;
    }
    if(!painter->isActive()) {
        error = "painter.isActive() == false";
        return false;
    }
    double tableWidth = painter->viewport().width() - leftBlank - rightBlank;
    if(tableWidth <= 0) {
        error = "wrong table width";
        return false;
    }
    int totalStretch = 0;
    for (int i = 0; i < columnStretch.count(); i++) {
        if(columnStretch[i] < 0) {
            error = QString("wrong column stretch, columnt: %1 stretch: %2").arg(i).arg(columnStretch[i]);
            return false;
        }
        totalStretch += columnStretch[i];
    }
    if(totalStretch <= 0) {
        error = QString("wrong stretch");
        return false;
    }
    QVector<double> columnWidth;
    for (int i = 0; i < columnStretch.count(); i++) {
        columnWidth.append(tableWidth / totalStretch * columnStretch[i]);
    }
    int initValue;
    headers.isEmpty() ? initValue = 0 : initValue = -1;

    //----------------------------------------------------------------------------

    painter->save(); // before table print

    // to know row height before printing
    // at first print to test image
    QPainter testSize;
    QImage* image = new QImage(10, 10, QImage::Format_RGB32);
    image->setDotsPerMeterX(printer->logicalDpiX() * 100 / 2.54); // 2.54 cm = 1 inch
    image->setDotsPerMeterY(printer->logicalDpiY() * 100 / 2.54);
    testSize.begin(image);

    if(prepare) {
        painter->save();
        painter->translate(-painter->transform().dx(), -painter->transform().dy());
        prepare->preparePage(painter);
        painter->restore();
    }

    painter->setPen(pen);
    painter->setFont(contentFont);
    testSize.setFont(contentFont);
    painter->translate(-painter->transform().dx() + leftBlank, 0);
    painter->save();
    painter->setFont(headersFont);
    testSize.setFont(headersFont);
    painter->drawLine(0, 0, tableWidth, 0); // first horizontal line

    float max_y;

    for(int j = initValue; j < model->rowCount(); j++) { // for each row
        if(j == 0) {
            painter->setFont(contentFont);
            testSize.setFont(contentFont);
        }

        // --------------------------- row height counting ----------------------------

        int maxHeight = 0; // max row Height
        for(int i = 0; i < columnCount; i++) { // for each column
            QString str;
            if(j >= 0) {
                str = model->data(model->index(j,i), Qt::DisplayRole).toString();
            } else {
                str = headers.at(i);
            }
            QRect rect(0, 0, columnWidth[i] - rightMargin - leftMargin, maxRowHeight);
            QRect realRect;
            testSize.drawText(rect, Qt::AlignLeft | Qt::TextWordWrap, str, &realRect);
            if (realRect.height() > maxHeight && columnStretch[i] != 0) {
                 realRect.height() > maxRowHeight ? maxHeight = maxRowHeight : maxHeight = realRect.height();
            }
        }

        if(painter->transform().dy() + maxHeight + topMargin + bottomMargin > painter->viewport().height() -
                bottomHeight) { // begin from new page
            int y = painter->transform().dy();
            painter->restore();
            painter->save();
            for(int i = 0; i < columnCount; i++) { // vertical lines
                painter->drawLine(0, 0, 0,
                                  - painter->transform().dy() + y);
                painter->translate(columnWidth[i], 0);
            }
            painter->drawLine(0, 0, 0, - painter->transform().dy() + y); // last vertical line
            painter->restore();
            printer->newPage();
            if(prepare) {
                painter->save();
                painter->translate(-painter->transform().dx(), -painter->transform().dy());
                prepare->preparePage(painter);
                painter->restore();
            }
            painter->translate(-painter->transform().dx() + leftBlank, -painter->transform().dy() + headerHeight);
            painter->save();
            painter->drawLine(0, 0, tableWidth,
                              0); // first horizontal line
        }

        //------------------------------ content printing -------------------------------------------

        painter->save();
        j >= 0 ? painter->setPen(QPen(contentColor)) : painter->setPen(QPen(headerColor));
        for(int i = 0; i < columnCount; i++) { // for each column
            QString str;
            if(j >= 0) {
                str = model->data(model->index(j,i), Qt::DisplayRole).toString();
            } else {
                str = headers.at(i);
            }
            QRect rec(leftMargin, topMargin, columnWidth[i] - rightMargin - leftMargin, maxHeight);
            painter->drawText(rec, Qt::AlignLeft | Qt::TextWordWrap, str);
            painter->translate(columnWidth[i], 0);
        }
        painter->restore();

        painter->drawLine(0, maxHeight + topMargin + bottomMargin, tableWidth,
                          maxHeight + topMargin + bottomMargin); // last horizontal line
        painter->translate(0, maxHeight + topMargin + bottomMargin);
        max_y = painter->transform().dy();
    }
    int y = painter->transform().dy();
    painter->restore();
    painter->save();
    for(int i = 0; i < columnCount; i++) { // vertical lines
        painter->drawLine(0, 0, 0,
                          - painter->transform().dy() + y);
        painter->translate(columnWidth[i], 0);
    }
    painter->drawLine(0, 0, 0, - painter->transform().dy() + y); // last vertical line
    painter->restore();

    testSize.end();
    delete image;

    painter->restore(); // before table print

    painter->translate(0, max_y);

    return true;
}

QString TablePrinter::lastError() {
    return error;
}

void TablePrinter::setCellMargin(int left, int right, int top, int bottom) {
    topMargin = top;
    bottomMargin = bottom;
    leftMargin = left;
    rightMargin = right;
}

void TablePrinter::setPageMargin(int left, int right, int top, int bottom) {
    headerHeight = top;
    bottomHeight = bottom;
    leftBlank = left;
    rightBlank = right;
}

void TablePrinter::setPagePrepare(PagePrepare *prep) {
    prepare = prep;
}

void TablePrinter::setPen(QPen p) {
    pen = p;
}

void TablePrinter::setHeadersFont(QFont f) {
    headersFont = f;
}

void TablePrinter::setContentFont(QFont f) {
    contentFont = f;
}

void TablePrinter::setHeaderColor(QColor color) {
    headerColor = color;
}

void TablePrinter::setContentColor(QColor color) {
    contentColor = color;
}

void TablePrinter::setMaxRowHeight(int height) {
    maxRowHeight = height;
}
