#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class QTabWidget;
class QTableView;
class ExcelModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openExcelFile();
    void showAboutDialog();

private:
    QTabWidget *m_tabWidget = nullptr;
    QVector<ExcelModel*> m_models;  // one model per sheet

    void setupUi();
    void setupMenu();
    void clearTabs();
    void applySpansToView(QTableView *view, ExcelModel *model);
};

#endif // MAINWINDOW_H
