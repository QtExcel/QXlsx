
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

        tabWidget->addTab( newSheet, curretnSheetName  );

        sheetIndexNumber++;
    }

    return true;
}

void MainWindow::on_action_About_triggered()
{
    QString title = "QXlsx";
    QString text = "QXlsx<br />"
            "<a href=\"https://github.com/j2doll/QXlsx\">https://github.com/j2doll/QXlsx</a><br />"
            "MIT License<br />" ;

    QMessageBox::about(this, title, text);
}

void MainWindow::on_action_New_triggered()
{
    QMessageBox msgBox;
    msgBox.setText( "New" );
    msgBox.exec();
}

void MainWindow::on_action_Save_triggered()
{
    QMessageBox msgBox;
    msgBox.setText( "Save" );
    msgBox.exec();
}

