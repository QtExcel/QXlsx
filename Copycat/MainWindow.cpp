// MainWindow.cpp

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
#include <QInputDialog>
#include <QStringList>
#include <QVarLengthArray>

#include "xlsxcelllocation.h"
#include "xlsxcell.h"
#include "CopycatTableModel.h"
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

    setWindowIcon(QIcon(":/excel.ico"));
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
        msgBox.setIcon( QMessageBox::Critical );
        msgBox.setText( alertMsg );
        msgBox.exec();
        return;
    }

    this->setWindowTitle(fileName);

}

bool MainWindow::loadXlsx(QString fileName)
{
    // tried to load xlsx using temporary document
    QXlsx::Document xlsxTmp( fileName );
    if ( !xlsxTmp.isLoadPackage() )
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
    xlsxDoc = new QXlsx::Document( fileName );
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

        XlsxTab* newSheet = new XlsxTab( this, xlsxDoc, currentSheet, sheetIndexNumber ); // create new tab
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
    QString text =
        "QXlsx Copycat<br />"
        "<a href=\"https://github.com/j2doll/QXlsx\">https://github.com/j2doll/QXlsx</a><br />" ;

    QMessageBox::about(this, "QXlsx", text);
}

void MainWindow::on_action_New_triggered()
{
    // TODO: new document
    QMessageBox msgBox;
    msgBox.setText( "TODO: New xlsx" );
    msgBox.exec();
}

void MainWindow::on_action_Save_triggered()
{
    // TODO: save document
    QMessageBox msgBox;
    msgBox.setText( "TODO: Save xlsx" );
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
    {
        QMessageBox msgBox;
        msgBox.setText( "xlsx document is empty." );
        msgBox.setIcon( QMessageBox::Warning );
        msgBox.exec();
        return;
    }

    Worksheet* wsheet = (Worksheet*) xlsxDoc->workbook()->activeSheet();
    if ( NULL == wsheet )
    {
        QMessageBox msgBox;
        msgBox.setText( "worksheet is set." );
        msgBox.setIcon( QMessageBox::Warning );
        msgBox.exec();
        return;
    }

    QStringList items;
    foreach( QString curretnSheetName, xlsxDoc->sheetNames() )
    {
        items << curretnSheetName;
    }

    bool ok = false;
    QString selectedItem
        = QInputDialog::getItem( this, tr("QXlsx"), tr("Select sheet:"), items, 0, false, &ok );

    if (!ok)
    {
        QMessageBox msgBox;
        msgBox.setText( "Please select printable sheet" );
        msgBox.setIcon( QMessageBox::Warning );
        msgBox.exec();
        return;
    }

    int idx = 0;
    foreach (const QString& varList, items)
    {
        if ( varList == selectedItem )
        {
            break;
        }
        idx++;
    }

    xlsxDoc->workbook()->setActiveSheet( idx );
    wsheet = (Worksheet*) xlsxDoc->workbook()->activeSheet(); // set active sheet

    QList<QString> colTitle;
    QList<VLIST> xlsxData;
    QVector<int> printColumnStretch;
    int sheetIndexNumber = 0;

    int maxRow = -1;
    int maxCol = -1;
    QVector<CellLocation> clList = wsheet->getFullCells( &maxRow, &maxCol );

	// Fixed for Visual C++, cause VC++ does not support C99. 
	// https://docs.microsoft.com/en-us/cpp/c-language/ansi-conformance?view=vs-2017
    // QString arr[maxRow][maxCol];

	QVector <QVector <QString> > arr;

	for (int i = 0; i < maxRow; i++)
	{
		QVector<QString> tempVector;
		for (int j = 0; j < maxCol; j++)
		{
			tempVector.push_back(QString("")); 
		}
		arr.push_back(tempVector);
	}

    for ( int ic = 0; ic < clList.size(); ++ic )
    {
        CellLocation cl = clList.at(ic);

        int row = cl.row - 1;
        int col = cl.col - 1;

        QSharedPointer<Cell> ptrCell = cl.cell; // cell pointer

        QString strValue = ptrCell->value().toString();

        arr[row][col] = strValue;
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

    for ( int ic = 0 ; ic < maxCol; ic++ )
    {
        std::string colString = convertFromNumberToExcelColumn( ( ic + 1 ) );
        QString strCol = QString::fromStdString( colString );

        colTitle.append( strCol );
        printHeaders.append( strCol );

        printColumnStretch.append( wsheet->columnWidth( (ic + 1) ) ); // TODO: check this code
    }

    CopycatTableModel copycatTableModel(colTitle, xlsxData); // model

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
    if ( !tablePrinter.printTable( &copycatTableModel, printColumnStretch, printHeaders ) )
    {
        QMessageBox msgBox;
        msgBox.setText( tablePrinter.lastError() );
        msgBox.setIcon( QMessageBox::Warning );
        msgBox.exec();
        return;
    }

    // tablePrinter.setCellMargin( l, r, t, b );
    // tablePrinter.setPageMargin( l, r, t, b );

    painter.end();
}

std::string MainWindow::convertFromNumberToExcelColumn(int n)
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
