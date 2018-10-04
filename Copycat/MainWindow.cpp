
#include <QtGlobal>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QList>
#include <QSharedPointer>

#include "xlsxcelllocation.h"
#include "xlsxcell.h"
#include "XlsxTableModel.h"
#include "tableprinter.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    xlsxDoc = NULL;
    tabWidget = NULL;

    ui->setupUi(this);

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    this->setWindowTitle(QString("Copycat"));
}

MainWindow::~MainWindow()
{
    delete ui;

    if ( NULL != xlsxDoc )
    {
        delete xlsxDoc;
    }
}

void MainWindow::on_action_Quit_triggered()
{
    // quit
    this->close();
}

void MainWindow::on_action_Open_triggered()
{
    // open file dialog
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Excel"), ".", tr("Excel Files (*.xlsx)"));

    if ( ! loadXlsx(fileName) ) // load xlsx
    {
        QMessageBox msgBox;
        QString alertMsg = QString("Failed to load file.\n %1").arg(fileName);
        msgBox.setText(alertMsg);
        msgBox.exec();
        return;
    }

    this->setWindowTitle(fileName);

}

bool MainWindow::loadXlsx(QString fileName)
{
    // tried to load xlsx using temporary document
    QXlsx::Document xlsxTmp(fileName);
    if (!xlsxTmp.isLoadPackage())
    {
        return false; // failed to load
    }

    // clear xlsxDoc
    if ( NULL != xlsxDoc )
    {
        delete xlsxDoc;
        xlsxDoc = NULL;
    }

    // load new xlsx using new document
    xlsxDoc = new QXlsx::Document(fileName);
    xlsxDoc->isLoadPackage();

    // clear tab widget
    tabWidget->clear();
    // Removes all the pages, but does not delete them.
    // Calling this function is equivalent to calling removeTab()
    // until the tab widget is empty.

    // clear sub-items of every tab
    foreach ( XlsxTab* ptrTab, xlsxTabList )
    {
        if ( NULL == ptrTab )
            continue;
        delete ptrTab;
    }
    xlsxTabList.clear();

    int sheetIndexNumber = 0;
    int activeSheetNumber = -1;

    AbstractSheet* activeSheet = xlsxDoc->workbook()->activeSheet();
    // NOTICE: active sheet is lastest sheet. It's not focused sheet.

    foreach( QString curretnSheetName, xlsxDoc->sheetNames() )
    {
        QXlsx::AbstractSheet* currentSheet = xlsxDoc->sheet( curretnSheetName );
        if ( NULL == currentSheet )
            continue;

        if ( activeSheet == currentSheet )
        {
            // current sheet is active sheet.
            activeSheetNumber = sheetIndexNumber;
        }

        XlsxTab* newSheet = new XlsxTab( this, currentSheet, sheetIndexNumber ); // create new tab
        xlsxTabList.push_back( newSheet ); // append to xlsx pointer list
        tabWidget->addTab( newSheet, curretnSheetName  ); // add tab widget
        sheetIndexNumber++; // increase sheet index number
    }

    if ( (-1) != activeSheetNumber )
        tabWidget->setCurrentIndex(activeSheetNumber);

    return true;
}

void MainWindow::on_action_About_triggered()
{
    QString text = "QXlsx<br />"
            "<a href=\"https://github.com/j2doll/QXlsx\">https://github.com/j2doll/QXlsx</a><br />"
            "MIT License<br />" ;
    QMessageBox::about(this, "QXlsx", text);
}

void MainWindow::on_action_New_triggered()
{
    // TODO: new document
    QMessageBox msgBox;
    msgBox.setText( "New" );
    msgBox.exec();
}

void MainWindow::on_action_Save_triggered()
{
    // TODO: save document
    QMessageBox msgBox;
    msgBox.setText( "Save" );
    msgBox.exec();
}

void MainWindow::on_action_Print_triggered()
{
    if ( NULL == xlsxDoc )
        return;

    QPrintPreviewDialog dialog;
    connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    dialog.exec();
}

void MainWindow::print(QPrinter *printer)
{
    if ( NULL == xlsxDoc )
        return;

    Worksheet* wsheet = (Worksheet*) xlsxDoc->workbook()->activeSheet();
    if ( NULL == wsheet )
        return;

    QList<QString> colTitle;
    QList<VLIST> xlsxData;
    QVector<int> printColumnStretch;
    int sheetIndexNumber = 0;

    int maxRow = -1;
    int maxCol = -1;
    QVector<CellLocation> clList = wsheet->getFullCells( &maxRow, &maxCol );

    QString arr[maxRow][maxCol];

    for ( int ic = 0; ic < clList.size(); ++ic )
    {
        CellLocation cl = clList.at(ic);

        int row = cl.row;
        int col = cl.col;

        QSharedPointer<Cell> ptrCell = cl.cell; // cell pointer

        QString strValue = ptrCell->value().toString();

        arr[row - 1][col - 1] = strValue;
    }

    for (int ir = 0 ; ir < maxRow; ir++)
    {
        VLIST vl;

        for (int ic = 0 ; ic < maxCol; ic++)
        {
            QString strValue = arr[ir][ic];
            if ( strValue.isNull() )
                strValue = QString("");

            vl.append( strValue );
        }

        xlsxData.append( vl );
    }

    QVector<QString> printHeaders;

    for (int ic = 0 ; ic < maxCol; ic++)
    {
        QString strCol = QString("%1").arg(ic + 1);
        colTitle.append( strCol );

        printHeaders.append( strCol );

        printColumnStretch.append( wsheet->columnWidth( (ic + 1) ) ); // TODO: check this code
    }

    XlsxTableModel xlsxTableModel(colTitle, xlsxData);

    /*
    for ( int j = 0; j < maxRow; j++ )
    {
        qDebug() << "===================";
        for( int i = 0; i < maxCol; i++ )
        {
            QString strVal = xlsxTableModel.data( xlsxTableModel.index(j, i), Qt::DisplayRole).toString();
            qDebug() << strVal;
        }
    }
    */

    QPainter painter;
    if ( !painter.begin(printer) )
    {
        QMessageBox msgBox;
        msgBox.setText( "Can't start printer" );
        msgBox.setIcon( QMessageBox::Critical );
        msgBox.exec();
        return;
    }

    // print table
    TablePrinter tablePrinter(&painter, printer);
    if(!tablePrinter.printTable( &xlsxTableModel, printColumnStretch, printHeaders ))
    {
        QMessageBox msgBox;
        msgBox.setText( tablePrinter.lastError() );
        msgBox.setIcon( QMessageBox::Warning );
        msgBox.exec();
    }

    painter.end();
}
