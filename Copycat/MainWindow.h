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

#include "xlsx.h"
#include "XlsxTab.h"

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

private:
    Ui::MainWindow *ui;
    QXlsx::Document* xlsxDoc;
    QTabWidget *tabWidget;
    QVector<XlsxTab*> xlsxTabList;

private:
    bool loadXlsx(QString xlsxFilename);

};

#endif // MAINWINDOW_H
