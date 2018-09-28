
#include <QtGlobal>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

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

}

MainWindow::~MainWindow()
{
    // tabWidget->close();

    delete ui;

    if ( NULL != xlsxDoc )
    {
        delete xlsxDoc;
    }

}

void MainWindow::on_action_Quit_triggered()
{
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
        return false;
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
    //
    // for ( int ic = 0 ; ic < tabWidget->count() ; ic++ ) {
    //    tabWidget->removeTab( ic );
    // }

    // clear sub-items of every tab
    foreach ( XlsxTab* ptrTab, xlsxTabList ) {
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

        tabWidget->addTab( newSheet, curretnSheetName  );

        sheetIndexNumber++;
    }

    return true;
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(QString("Copycat\nhttps://github.com/j2doll/QXlsx"));
    msgBox.exec();
}
