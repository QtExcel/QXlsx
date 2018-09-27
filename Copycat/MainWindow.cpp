
#include <QtGlobal>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

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

    // tried to load xlsx
    QXlsx::Document xlsxTmp(fileName);
    if (!xlsxTmp.isLoadPackage())
    {
        QMessageBox msgBox;
        QString alertMsg = QString("Failed to load file.\n %1").arg(fileName);
        msgBox.setText(alertMsg);
        msgBox.exec();
        return;
    }

    bool returnLoading = loadXlsx(fileName);
}

bool MainWindow::loadXlsx(QString fileName)
{
    // clear xlsxDoc
    if ( NULL != xlsxDoc )
    {
        delete xlsxDoc;
        xlsxDoc = NULL;
    }

    // load new xlsx
    xlsxDoc = new QXlsx::Document(fileName);
    xlsxDoc->isLoadPackage();

    // clear tab widget
    tabWidget->clear();
    // Removes all the pages, but does not delete them.
    // Calling this function is equivalent to calling removeTab() until the tab widget is empty.
    //
    //for ( int ic = 0 ; ic < tabWidget->count() ; ic++ ) {
    //    tabWidget->removeTab( ic );
    //}

    // TODO: clear sub-items of every tab

    foreach( QString curretnSheetName, xlsxDoc->sheetNames() ) {
       QXlsx::AbstractSheet* currentSheet = xlsxDoc->sheet( curretnSheetName );
       if ( NULL == currentSheet )
           continue;

       // create new tab
       // XlsxTab* newSheet = new XlsxTab( this, currentSheet );

            // TODO: append to xlsx pointer list

       // tabWidget->addTab( newSheet );
    }

}
