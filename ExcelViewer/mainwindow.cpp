#include "mainwindow.h"
#include "excelmodel.h"

#include <QTabWidget>
#include <QTableView>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QtGlobal>    // for qVersion()

// QXlsx headers (for reading sheet names)
#include <xlsxdocument.h>

using namespace QXlsx;

// Hard-coded QXlsx version string (based on the library you are using)
// static const char *QXLSX_VERSION = "1.5.0";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupMenu();
}

void MainWindow::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    setWindowTitle("Excel Read-Only Viewer (All Sheets, Merged Cells + Styles)");
    resize(1000, 700);
}

void MainWindow::setupMenu()
{
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *openAction = new QAction("Open Excel...", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openExcelFile);

    QAction *quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, this, &QWidget::close);

    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("Help");

    QAction *aboutAction = new QAction("About ExcelViewer...", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

    helpMenu->addAction(aboutAction);
}

void MainWindow::clearTabs()
{
    // Delete models
    for (ExcelModel *m : m_models)
        delete m;
    m_models.clear();

    // Remove all tabs
    while (m_tabWidget->count() > 0)
    {
        QWidget *w = m_tabWidget->widget(0);
        m_tabWidget->removeTab(0);
        delete w;
    }
}

void MainWindow::applySpansToView(QTableView *view, ExcelModel *model)
{
    view->clearSpans();
    const auto &spans = model->spans();
    for (const auto &s : spans)
    {
        view->setSpan(s.row, s.column, s.rowSpan, s.columnSpan);
    }
}

void MainWindow::openExcelFile()
{
    // Show warning / information message before opening the file dialog
    QMessageBox::StandardButton choice = QMessageBox::question(
        this,
        "Information",
        "If the xlsx file is large, opening it may take a significant amount of time.\n\n"
        "Do you want to continue and select a file?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes
        );

    if (choice != QMessageBox::Yes)
        return;

    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Excel File",
        QString(),
        "Excel File (*.xlsx)"
        );

    if (filePath.isEmpty())
        return;

    // First, read sheet names using QXlsx::Document
    Document doc(filePath);
    if (!doc.isLoadPackage())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Failed to load the Excel file."
            );
        return;
    }

    const QStringList sheetNames = doc.sheetNames();
    if (sheetNames.isEmpty())
    {
        QMessageBox::information(
            this,
            "Info",
            "The Excel file has no sheets."
            );
        return;
    }

    clearTabs();

    // For each sheet, create a model and a view, and add as a tab
    for (const QString &sheetName : sheetNames)
    {
        ExcelModel *model = new ExcelModel(this);
        if (!model->loadFromXlsx(filePath, sheetName))
        {
            delete model;
            continue;
        }

        QTableView *view = new QTableView(m_tabWidget);
        view->setModel(model);

        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        view->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        view->setSelectionBehavior(QAbstractItemView::SelectItems);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);

        applySpansToView(view, model);

        m_tabWidget->addTab(view, sheetName);
        m_models.push_back(model);
    }

    if (m_tabWidget->count() == 0)
    {
        QMessageBox::warning(
            this,
            "Error",
            "No sheet could be loaded from the Excel file."
            );
    }
}

void MainWindow::showAboutDialog()
{
    QMessageBox aboutBox(this);
    aboutBox.setWindowTitle("About ExcelViewer");
    aboutBox.setTextFormat(Qt::RichText);
    aboutBox.setTextInteractionFlags(Qt::TextBrowserInteraction);
    aboutBox.setStandardButtons(QMessageBox::Ok);

    QString text = QString(
                       "<b>ExcelViewer</b><br>"
                       "A read-only viewer for .xlsx files using Qt and QXlsx.<br><br>"
                       "Qt version: <b>%1</b><br>"
                       "QXlsx Git Commit (full hash):<br>"
                       "<b>%2</b><br><br>"
                       "This program uses the "
                       "<a href=\"https://github.com/QtExcel/QXlsx\">QXlsx library</a>.<br><br>"
                       ).arg(QLatin1String(qVersion()))
                       .arg(QStringLiteral(QXLSX_GIT_FULL_HASH));

    aboutBox.setText(text);
    aboutBox.exec();
}

