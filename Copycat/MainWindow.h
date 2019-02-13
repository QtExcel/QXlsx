#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QVector>
#include <QList>
#include <QWidget>
#include <QMainWindow>
#include <QTabWidget>
#include <QPrinter>

#include "xlsx.h"
#include "XlsxTab.h"
#include "CopycatTableModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Quit_triggered();
    void on_action_Open_triggered();
    void on_action_About_triggered();
    void on_action_New_triggered();
    void on_action_Save_triggered();
    void on_action_Print_triggered();
    void print(QPrinter *printer);

protected:
    Ui::MainWindow *ui;
    QXlsx::Document* xlsxDoc;
    QTabWidget *tabWidget;
    QVector<XlsxTab*> xlsxTabList;

protected:
    bool loadXlsx(QString xlsxFilename);
    std::string convertFromNumberToExcelColumn(int n);
};

#endif // MAINWINDOW_H
