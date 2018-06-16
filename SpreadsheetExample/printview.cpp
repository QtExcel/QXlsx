// (c) The Qt Company Ltd. BSD License
// Some code is fixed by j2doll.


#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif
#include <QStyleOptionViewItem>

#include "printview.h"

PrintView::PrintView()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PrintView::print(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
    resize(printer->width(), printer->height());
    render(printer);
#endif
}

