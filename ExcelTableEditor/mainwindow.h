#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QHash>
#include <QPair>
#include <QStringList>

namespace QXlsx {
class Format;
}

class QTableView;
class QStandardItemModel;
class QAction;
class ExcelItemDelegate;
class QComboBox;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_action_open_triggered();
    void on_action_save_triggered();
    void on_action_save_as_triggered();

    void on_model_data_changed();

    void on_current_sheet_changed(int index);
    void on_sheet_rename_button_clicked();

    void on_sheet_new_button_clicked();
    void on_sheet_delete_button_clicked();
    void on_sheet_move_left_button_clicked();
    void on_sheet_move_right_button_clicked();

    void on_action_about_triggered();

           // row / column insertion slots
    void on_add_row_button_clicked();
    void on_add_column_button_clicked();

private:
    void setup_ui();
    void setup_menu();
    void clear_model();
    bool load_excel_file(const QString &file_path);
    bool save_excel_file(const QString &file_path);
    bool confirm_discard_if_modified();

    void set_current_sheet(const QString &sheet_name);

    void apply_format_to_item(QStandardItemModel *model,
                              int row,
                              int col,
                              const QXlsx::Format &fmt);
    QXlsx::Format format_for_cell(const QString &sheet_name,
                                  int row,
                                  int col) const;

    QString generate_unique_sheet_name() const;
    void rebuild_sheet_combo(const QString &current_name);

private:
    QPointer<QTableView> table_view_;
    QPointer<ExcelItemDelegate> delegate_;

           // widgets for selecting and editing sheets
    QPointer<QComboBox> sheet_combo_;
    QPointer<QLineEdit> sheet_name_edit_;
    QPointer<QPushButton> sheet_rename_button_;
    QPointer<QPushButton> sheet_new_button_;
    QPointer<QPushButton> sheet_delete_button_;
    QPointer<QPushButton> sheet_move_left_button_;
    QPointer<QPushButton> sheet_move_right_button_;

           // row / column insertion buttons
    QPointer<QPushButton> add_row_button_;
    QPointer<QPushButton> add_column_button_;

           // current sheet model
    QPointer<QStandardItemModel> current_model_;
    QString current_sheet_name_;

           // document state
    QString current_file_path_;
    bool is_modified_ = false;

           // sheet list and per-sheet models / formats
    QStringList sheet_names_;
    QHash<QString, QPointer<QStandardItemModel>> sheet_models_;
    QHash<QString, QHash<QPair<int, int>, QXlsx::Format>> sheet_formats_;

    QPointer<QAction> action_open_;
    QPointer<QAction> action_save_;
    QPointer<QAction> action_save_as_;
    QPointer<QAction> action_exit_;
};

// qHash for using QPair<int,int> as QHash key
inline uint qHash(const QPair<int, int> &key, uint seed = 0) noexcept
{
    return qHash((quint64(key.first) << 32) ^ quint64(key.second), seed);
}

#endif // MAINWINDOW_H
