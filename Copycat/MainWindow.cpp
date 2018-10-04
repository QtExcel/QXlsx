
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
    foreach( QString curretnSheetName, xlsxDoc->sheetNames() )
    {
        QXlsx::AbstractSheet* currentSheet = xlsxDoc->sheet( curretnSheetName );
        if ( NULL == currentSheet )
            continue;

        XlsxTab* newSheet = new XlsxTab( this, currentSheet, sheetIndexNumber ); // create new tab
        xlsxTabList.push_back( newSheet ); // append to xlsx pointer list
        tabWidget->addTab( newSheet, curretnSheetName  ); // add tab widget
        sheetIndexNumber++; // increase sheet index number
    }

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

    QList<QString> colTitle;

    QList<VLIST> xlsxData;

    QVector<int> printColumnStretch;

    int sheetIndexNumber = 0;
    foreach( QString curretnSheetName, xlsxDoc->sheetNames() )
    {
        if ( curretnSheetName.isEmpty() )
            continue;

        QXlsx::AbstractSheet* currentSheet = xlsxDoc->sheet( curretnSheetName );
        if ( NULL == currentSheet )
            continue;

        // set active sheet
        currentSheet->workbook()->setActiveSheet( sheetIndexNumber );
        Worksheet* wsheet = (Worksheet*) currentSheet->workbook()->activeSheet();

        int maxRow = -1;
        int maxCol = -1;
        QVector<CellLocation> clList = wsheet->getFullCells( &maxRow, &maxCol );

        for ( int ic = 0; ic < clList.size(); ++ic )
        {
              CellLocation cl = clList.at(ic);

              // First cell of tableWidget is 0.
              // But first cell of Qxlsx document is 1.
              int row = cl.row - 1;
              int col = cl.col - 1;

              QSharedPointer<Cell> ptrCell = cl.cell; // cell pointer


        }

        // TODO: load sheet and ship into tablemodel
        //       ( colTitle,  xlsxData,  printColumnStretch )

        // colTitle.append(QString("A"));

        /*
        VLIST vl1;
        vl1.append( xlsx.read("A1") );
        vl1.append( xlsx.read("B1") );
        vl1.append( xlsx.read("C1") );
        xlsxData.append( vl1 );
        */

        // printColumnStretch = QVector<int>() << 2 << 5 << 10 << 15;

        sheetIndexNumber++; // increase sheet index number
    }

    XlsxTableModel xlsxTableModel(colTitle, xlsxData);

    QPainter painter;
    if ( !painter.begin(printer) )
    {
        QMessageBox msgBox;
        msgBox.setText( "Can't start printer" );
        msgBox.exec();
        return;
    }

    // print table
    TablePrinter tablePrinter(&painter, printer);
    if(!tablePrinter.printTable( &xlsxTableModel, printColumnStretch ))
    {
        QMessageBox msgBox;
        msgBox.setText( tablePrinter.lastError() );
        msgBox.exec();
    }

    painter.end();
}
