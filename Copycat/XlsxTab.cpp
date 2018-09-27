// XlsxTab.cpp

#include "XlsxTab.h"

XlsxTab::XlsxTab(QWidget* parent, QXlsx::AbstractSheet* ptrSheet)
    : QWidget(parent)
{
    table = NULL;

    if ( NULL != ptrSheet ) {
        // set sheet data
    }

}

XlsxTab::~XlsxTab()
{
    if ( NULL != table )
    {
        table->deleteLater();
    }
}


