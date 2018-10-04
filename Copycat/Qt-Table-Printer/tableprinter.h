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

#ifndef TABLEPRINTER_H
#define TABLEPRINTER_H

#include <QPen>
#include <QFont>

class QPrinter;
class QPainter;
class QAbstractItemModel;

/**
 * @brief The PagePrepare Abstract class - base class for
 * classes that will print something like headers, borders...
 * on each page with table
 */
class PagePrepare {
public:
    virtual void preparePage(QPainter *painter) = 0;
    virtual ~PagePrepare() {}
};

class TablePrinter
{
public:
  TablePrinter(QPainter *painter, QPrinter *printer);
  bool printTable(const QAbstractItemModel* model, const QVector<int> columnStretch,
                  const QVector<QString> headers = QVector<QString>());
  QString lastError();
  void setCellMargin(int left = 10, int right = 5, int top = 5, int bottom = 5);
  void setPageMargin(int left = 50, int right = 20, int top = 20, int bottom = 20);
  void setPagePrepare(PagePrepare *prepare);
  void setPen(QPen pen); // for table borders
  void setHeadersFont(QFont font);
  void setContentFont(QFont font);
  void setHeaderColor(QColor color);
  void setContentColor(QColor color);
  void setMaxRowHeight(int height);
private:
  QPainter *painter;
  QPrinter *printer;
  PagePrepare *prepare;
  QPen pen; // for table borders
  QFont headersFont;
  QFont contentFont;
  QColor headerColor;
  QColor contentColor;
  // cell margins
  int topMargin;
  int bottomMargin;
  int leftMargin;
  int rightMargin;

  // margins for table
  int headerHeight;
  int bottomHeight;
  int leftBlank;
  int rightBlank;

  int maxRowHeight;

  QString error;
};

#endif // TABLEPRINTER_H
