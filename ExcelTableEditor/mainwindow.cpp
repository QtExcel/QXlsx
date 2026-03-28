#include "mainwindow.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QItemSelectionModel>

#include "excelitemdelegate.h"

#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "xlsxcell.h"
#include "xlsxformat.h"

using namespace QXlsx;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setup_ui();
    setup_menu();
}

MainWindow::~MainWindow() = default;

void MainWindow::setup_ui()
{
    // central widget: top sheet bar + table view
    QWidget *central = new QWidget(this);
    QVBoxLayout *v_layout = new QVBoxLayout(central);
    v_layout->setContentsMargins(4, 4, 4, 4);
    v_layout->setSpacing(4);

           // top sheet bar: sheet selection + rename + new/delete/move + row/column insertion
    QWidget *sheet_bar = new QWidget(central);
    QHBoxLayout *h_layout = new QHBoxLayout(sheet_bar);
    h_layout->setContentsMargins(0, 0, 0, 0);
    h_layout->setSpacing(4);

    QLabel *sheet_label = new QLabel(tr("Sheet:"), sheet_bar);
    sheet_combo_ = new QComboBox(sheet_bar);
    sheet_combo_->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    sheet_name_edit_ = new QLineEdit(sheet_bar);
    sheet_name_edit_->setPlaceholderText(tr("Sheet name"));

    sheet_rename_button_ = new QPushButton(tr("Rename"), sheet_bar);
    sheet_new_button_ = new QPushButton(tr("New"), sheet_bar);
    sheet_delete_button_ = new QPushButton(tr("Delete"), sheet_bar);
    sheet_move_left_button_ = new QPushButton(tr("◀"), sheet_bar);
    sheet_move_right_button_ = new QPushButton(tr("▶"), sheet_bar);

           // row / column insertion buttons
    add_row_button_ = new QPushButton(tr("+Row"), sheet_bar);
    add_column_button_ = new QPushButton(tr("+Col"), sheet_bar);

    h_layout->addWidget(sheet_label);
    h_layout->addWidget(sheet_combo_, 0);
    h_layout->addSpacing(8);
    h_layout->addWidget(new QLabel(tr("Name:"), sheet_bar));
    h_layout->addWidget(sheet_name_edit_, 1);
    h_layout->addWidget(sheet_rename_button_);
    h_layout->addSpacing(8);
    h_layout->addWidget(sheet_new_button_);
    h_layout->addWidget(sheet_delete_button_);
    h_layout->addWidget(sheet_move_left_button_);
    h_layout->addWidget(sheet_move_right_button_);

    h_layout->addSpacing(12);
    h_layout->addWidget(new QLabel(tr("Insert:"), sheet_bar));
    h_layout->addWidget(add_row_button_);
    h_layout->addWidget(add_column_button_);

    v_layout->addWidget(sheet_bar);

           // table view
    table_view_ = new QTableView(central);
    table_view_->setAlternatingRowColors(true);
    table_view_->setSelectionBehavior(QAbstractItemView::SelectItems);
    table_view_->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table_view_->setEditTriggers(QAbstractItemView::DoubleClicked |
                                 QAbstractItemView::SelectedClicked |
                                 QAbstractItemView::EditKeyPressed);
    v_layout->addWidget(table_view_, 1);

    setCentralWidget(central);

           // delegate
    delegate_ = new ExcelItemDelegate(this);
    table_view_->setItemDelegate(delegate_);

    statusBar()->showMessage(tr("Ready"));

           // connections
    connect(sheet_combo_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_current_sheet_changed);
    connect(sheet_rename_button_, &QPushButton::clicked,
            this, &MainWindow::on_sheet_rename_button_clicked);
    connect(sheet_new_button_, &QPushButton::clicked,
            this, &MainWindow::on_sheet_new_button_clicked);
    connect(sheet_delete_button_, &QPushButton::clicked,
            this, &MainWindow::on_sheet_delete_button_clicked);
    connect(sheet_move_left_button_, &QPushButton::clicked,
            this, &MainWindow::on_sheet_move_left_button_clicked);
    connect(sheet_move_right_button_, &QPushButton::clicked,
            this, &MainWindow::on_sheet_move_right_button_clicked);

           // row / column insertion buttons
    connect(add_row_button_, &QPushButton::clicked,
            this, &MainWindow::on_add_row_button_clicked);
    connect(add_column_button_, &QPushButton::clicked,
            this, &MainWindow::on_add_column_button_clicked);
}

void MainWindow::setup_menu()
{
    QMenu *file_menu = menuBar()->addMenu(tr("&File"));

    action_open_ = new QAction(tr("&Open..."), this);
    action_save_ = new QAction(tr("&Save"), this);
    action_save_as_ = new QAction(tr("Save &As..."), this);
    action_exit_ = new QAction(tr("E&xit"), this);

    action_save_->setEnabled(false);
    action_save_as_->setEnabled(false);

    file_menu->addAction(action_open_);
    file_menu->addSeparator();
    file_menu->addAction(action_save_);
    file_menu->addAction(action_save_as_);
    file_menu->addSeparator();
    file_menu->addAction(action_exit_);

           // Help menu
    QMenu *help_menu = menuBar()->addMenu(tr("&Help"));
    QAction *action_about = new QAction(tr("&About ExcelTableEditor"), this);
    help_menu->addAction(action_about);

    connect(action_about, &QAction::triggered,
            this, &MainWindow::on_action_about_triggered);

    connect(action_open_, &QAction::triggered,
            this, &MainWindow::on_action_open_triggered);
    connect(action_save_, &QAction::triggered,
            this, &MainWindow::on_action_save_triggered);
    connect(action_save_as_, &QAction::triggered,
            this, &MainWindow::on_action_save_as_triggered);
    connect(action_exit_, &QAction::triggered,
            this, &QWidget::close);
}

void MainWindow::clear_model()
{
    sheet_models_.clear();
    sheet_formats_.clear();
    sheet_names_.clear();
    current_sheet_name_.clear();
    current_model_.clear();

    if (table_view_) {
        table_view_->setModel(nullptr);
    }
    if (sheet_combo_) {
        sheet_combo_->clear();
    }
    if (sheet_name_edit_) {
        sheet_name_edit_->clear();
    }
}

bool MainWindow::confirm_discard_if_modified()
{
    if (!is_modified_) {
        return true;
    }

    const auto ret = QMessageBox::warning(
        this,
        tr("Unsaved Changes"),
        tr("The current document has been modified.\n"
           "Do you want to discard the changes?"),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
        );

    return ret == QMessageBox::Yes;
}

void MainWindow::on_action_open_triggered()
{
    if (!confirm_discard_if_modified()) {
        return;
    }

    const QString file_path = QFileDialog::getOpenFileName(
        this,
        tr("Open Excel File"),
        QString(),
        tr("Excel Files (*.xlsx);;All Files (*.*)")
        );

    if (file_path.isEmpty()) {
        return;
    }

    if (!load_excel_file(file_path)) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Failed to open the Excel file."));
        return;
    }

    current_file_path_ = file_path;
    is_modified_ = false;

    action_save_->setEnabled(true);
    action_save_as_->setEnabled(true);

    statusBar()->showMessage(tr("Loaded: %1").arg(file_path), 5000);
}

void MainWindow::on_action_save_triggered()
{
    if (current_file_path_.isEmpty()) {
        on_action_save_as_triggered();
        return;
    }

    if (!save_excel_file(current_file_path_)) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Failed to save the Excel file."));
        return;
    }

    is_modified_ = false;
    statusBar()->showMessage(tr("Saved: %1").arg(current_file_path_), 5000);
}

void MainWindow::on_action_save_as_triggered()
{
    const QString file_path = QFileDialog::getSaveFileName(
        this,
        tr("Save Excel File As"),
        current_file_path_.isEmpty() ? QStringLiteral("edited.xlsx")
                                     : current_file_path_,
        tr("Excel Files (*.xlsx);;All Files (*.*)")
        );

    if (file_path.isEmpty()) {
        return;
    }

    if (!save_excel_file(file_path)) {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Failed to save the Excel file."));
        return;
    }

    current_file_path_ = file_path;
    is_modified_ = false;

    action_save_->setEnabled(true);
    action_save_as_->setEnabled(true);

    statusBar()->showMessage(tr("Saved As: %1").arg(file_path), 5000);
}

void MainWindow::on_model_data_changed()
{
    is_modified_ = true;
}

// sheet combobox change handler
void MainWindow::on_current_sheet_changed(int index)
{
    if (index < 0 || index >= sheet_names_.size()) {
        return;
    }

    const QString sheet_name = sheet_names_.at(index);
    set_current_sheet(sheet_name);
}

// rename current sheet
void MainWindow::on_sheet_rename_button_clicked()
{
    if (current_sheet_name_.isEmpty()) {
        return;
    }

    const QString new_name = sheet_name_edit_->text().trimmed();
    if (new_name.isEmpty() || new_name == current_sheet_name_) {
        return;
    }

    if (sheet_names_.contains(new_name)) {
        QMessageBox::warning(this,
                             tr("Rename Sheet"),
                             tr("A sheet with the same name already exists."));
        return;
    }

    const int idx = sheet_names_.indexOf(current_sheet_name_);
    if (idx < 0) {
        return;
    }

           // update sheet name list
    sheet_names_[idx] = new_name;

           // change map key
    auto model = sheet_models_.take(current_sheet_name_);
    auto formats = sheet_formats_.take(current_sheet_name_);
    sheet_models_.insert(new_name, model);
    sheet_formats_.insert(new_name, formats);

    current_sheet_name_ = new_name;

    rebuild_sheet_combo(new_name);

    is_modified_ = true;
    statusBar()->showMessage(tr("Sheet renamed to: %1").arg(new_name), 3000);
}

// create new sheet
void MainWindow::on_sheet_new_button_clicked()
{
    const QString new_name = generate_unique_sheet_name();

    auto *model = new QStandardItemModel(this);
    const int default_rows = 10;
    const int default_cols = 5;
    model->setRowCount(default_rows);
    model->setColumnCount(default_cols);

    for (int c = 0; c < default_cols; ++c) {
        model->setHeaderData(c, Qt::Horizontal, QString::number(c + 1));
    }
    for (int r = 0; r < default_rows; ++r) {
        model->setHeaderData(r, Qt::Vertical, QString::number(r + 1));
    }

    sheet_names_.append(new_name);
    sheet_models_.insert(new_name, model);
    sheet_formats_.insert(new_name, {}); // empty format map

    rebuild_sheet_combo(new_name);
    set_current_sheet(new_name);

    is_modified_ = true;
    statusBar()->showMessage(tr("New sheet created: %1").arg(new_name), 3000);
}

// delete current sheet
void MainWindow::on_sheet_delete_button_clicked()
{
    if (current_sheet_name_.isEmpty()) {
        return;
    }

    if (sheet_names_.size() <= 1) {
        QMessageBox::warning(this,
                             tr("Delete Sheet"),
                             tr("Cannot delete the last sheet."));
        return;
    }

    const int idx = sheet_names_.indexOf(current_sheet_name_);
    if (idx < 0) {
        return;
    }

    const auto ret = QMessageBox::question(
        this,
        tr("Delete Sheet"),
        tr("Do you really want to delete the sheet \"%1\"?")
            .arg(current_sheet_name_),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
        );

    if (ret != QMessageBox::Yes) {
        return;
    }

    const QString removed_name = current_sheet_name_;

    sheet_models_.remove(removed_name);
    sheet_formats_.remove(removed_name);
    sheet_names_.removeAt(idx);

    int new_idx = idx;
    if (new_idx >= sheet_names_.size()) {
        new_idx = sheet_names_.size() - 1;
    }

    QString new_name;
    if (new_idx >= 0 && new_idx < sheet_names_.size()) {
        new_name = sheet_names_.at(new_idx);
    }

    rebuild_sheet_combo(new_name);

    if (!new_name.isEmpty()) {
        set_current_sheet(new_name);
    } else {
        table_view_->setModel(nullptr);
        current_sheet_name_.clear();
        current_model_.clear();
    }

    is_modified_ = true;
    statusBar()->showMessage(tr("Sheet deleted: %1").arg(removed_name), 3000);
}

// move current sheet to the left
void MainWindow::on_sheet_move_left_button_clicked()
{
    if (current_sheet_name_.isEmpty()) {
        return;
    }

    const int idx = sheet_names_.indexOf(current_sheet_name_);
    if (idx <= 0) {
        return;
    }

    sheet_names_.swapItemsAt(idx, idx - 1);
    rebuild_sheet_combo(current_sheet_name_);

    is_modified_ = true;
    statusBar()->showMessage(tr("Sheet moved left"), 2000);
}

// move current sheet to the right
void MainWindow::on_sheet_move_right_button_clicked()
{
    if (current_sheet_name_.isEmpty()) {
        return;
    }

    const int idx = sheet_names_.indexOf(current_sheet_name_);
    if (idx < 0 || idx >= sheet_names_.size() - 1) {
        return;
    }

    sheet_names_.swapItemsAt(idx, idx + 1);
    rebuild_sheet_combo(current_sheet_name_);

    is_modified_ = true;
    statusBar()->showMessage(tr("Sheet moved right"), 2000);
}

// set current sheet model / view
void MainWindow::set_current_sheet(const QString &sheet_name)
{
    if (!sheet_models_.contains(sheet_name)) {
        return;
    }

    current_sheet_name_ = sheet_name;
    current_model_ = sheet_models_.value(sheet_name);

    if (table_view_) {
        table_view_->setModel(current_model_);
    }

    if (sheet_name_edit_) {
        sheet_name_edit_->setText(sheet_name);
    }

    if (current_model_) {
        disconnect(current_model_, &QStandardItemModel::dataChanged,
                   this, &MainWindow::on_model_data_changed);
        connect(current_model_, &QStandardItemModel::dataChanged,
                this, &MainWindow::on_model_data_changed);
    }
}

// apply QXlsx::Format to a Qt item
void MainWindow::apply_format_to_item(QStandardItemModel *model,
                                      int row,
                                      int col,
                                      const Format &fmt)
{
    if (!model) {
        return;
    }

    QStandardItem *item = model->item(row, col);
    if (!item) {
        return;
    }

    QFont font = item->font();
    if (fmt.fontBold()) {
        font.setBold(true);
    }
    if (fmt.fontItalic()) {
        font.setItalic(true);
    }
    if (!fmt.fontName().isEmpty()) {
        font.setFamily(fmt.fontName());
    }
    if (fmt.fontSize() > 0) {
        font.setPointSize(fmt.fontSize());
    }
    item->setFont(font);

    if (fmt.fontColor().isValid()) {
        item->setData(fmt.fontColor(), Qt::ForegroundRole);
    }
    if (fmt.fillPattern() != Format::PatternNone &&
        fmt.patternBackgroundColor().isValid()) {
        item->setData(fmt.patternBackgroundColor(), Qt::BackgroundRole);
    }

    Qt::Alignment align = {};
    switch (fmt.horizontalAlignment()) {
    case Format::AlignLeft:    align |= Qt::AlignLeft;    break;
    case Format::AlignRight:   align |= Qt::AlignRight;   break;
    case Format::AlignHCenter: align |= Qt::AlignHCenter; break;
    default: break;
    }
    switch (fmt.verticalAlignment()) {
    case Format::AlignTop:     align |= Qt::AlignTop;     break;
    case Format::AlignBottom:  align |= Qt::AlignBottom;  break;
    case Format::AlignVCenter: align |= Qt::AlignVCenter; break;
    default: break;
    }
    if (align != 0) {
        item->setTextAlignment(align);
    }
}

// look up cell format
Format MainWindow::format_for_cell(const QString &sheet_name,
                                   int row,
                                   int col) const
{
    auto it_sheet = sheet_formats_.constFind(sheet_name);
    if (it_sheet == sheet_formats_.constEnd()) {
        return Format();
    }

    const auto &fmt_map = it_sheet.value();
    const auto key = qMakePair(row, col);
    auto it = fmt_map.constFind(key);
    if (it != fmt_map.constEnd()) {
        return it.value();
    }
    return Format();
}

// generate a unique sheet name like "Sheet1", "Sheet2", ...
QString MainWindow::generate_unique_sheet_name() const
{
    QString base = QStringLiteral("Sheet");
    int idx = 1;
    while (true) {
        const QString candidate = base + QString::number(idx);
        if (!sheet_names_.contains(candidate)) {
            return candidate;
        }
        ++idx;
    }
}

// rebuild sheet combobox and keep current sheet selection
void MainWindow::rebuild_sheet_combo(const QString &current_name)
{
    if (!sheet_combo_) {
        return;
    }

    sheet_combo_->blockSignals(true);
    sheet_combo_->clear();
    for (const QString &name : sheet_names_) {
        sheet_combo_->addItem(name);
    }
    int idx = sheet_names_.indexOf(current_name);
    if (idx >= 0) {
        sheet_combo_->setCurrentIndex(idx);
    }
    sheet_combo_->blockSignals(false);
}

// load all sheets from an Excel file
// all rows including the first row are loaded as data, so row 1 is editable.
bool MainWindow::load_excel_file(const QString &file_path)
{
    Document xlsx(file_path);
    if (!xlsx.isLoadPackage()) {
        return false;
    }

    clear_model();

    sheet_names_ = xlsx.sheetNames();
    if (sheet_names_.isEmpty()) {
        if (auto cur_sheet = dynamic_cast<Worksheet *>(xlsx.currentWorksheet())) {
            sheet_names_ << cur_sheet->sheetName();
        }
    }

    for (const QString &sheet_name : sheet_names_) {
        if (!xlsx.selectSheet(sheet_name)) {
            continue;
        }

        Worksheet *sheet = dynamic_cast<Worksheet *>(xlsx.currentWorksheet());
        if (!sheet) {
            continue;
        }

        CellRange range = sheet->dimension();
        int first_row = range.firstRow();
        int last_row  = range.lastRow();
        int first_col = range.firstColumn();
        int last_col  = range.lastColumn();

        if (first_row == 0 || last_row == 0 ||
            first_col == 0 || last_col == 0) {
            auto *empty_model = new QStandardItemModel(this);
            sheet_models_.insert(sheet_name, empty_model);
            continue;
        }

        int row_count = last_row - first_row + 1;
        int col_count = last_col - first_col + 1;

        auto *model = new QStandardItemModel(this);
        model->setRowCount(row_count);
        model->setColumnCount(col_count);

        for (int c = 0; c < col_count; ++c) {
            model->setHeaderData(c, Qt::Horizontal, QString::number(c + 1));
        }
        for (int r = 0; r < row_count; ++r) {
            model->setHeaderData(r, Qt::Vertical, QString::number(r + 1));
        }

        auto &fmt_map = sheet_formats_[sheet_name];

        for (int r = first_row; r <= last_row; ++r) {
            for (int c = first_col; c <= last_col; ++c) {
                auto cell = sheet->cellAt(r, c);
                if (!cell) {
                    continue;
                }

                QVariant value = cell->value();
                if (value.isNull()) {
                    continue;
                }

                const int model_row = r - first_row;
                const int model_col = c - first_col;

                auto *item = new QStandardItem();
                item->setData(value, Qt::EditRole);

                if (value.typeId() == QMetaType::Bool) {
                    item->setCheckable(true);
                    item->setCheckState(
                        value.toBool() ? Qt::Checked : Qt::Unchecked);
                }

                model->setItem(model_row, model_col, item);

                const Format fmt = cell->format();
                if (fmt.isValid()) {
                    const auto key = qMakePair(model_row, model_col);
                    fmt_map.insert(key, fmt);
                    apply_format_to_item(model, model_row, model_col, fmt);
                }
            }
        }

        sheet_models_.insert(sheet_name, model);
    }

    rebuild_sheet_combo(sheet_names_.isEmpty() ? QString() : sheet_names_.first());

    if (!sheet_names_.isEmpty()) {
        set_current_sheet(sheet_names_.first());
    } else {
        table_view_->setModel(nullptr);
        current_sheet_name_.clear();
        current_model_.clear();
    }

    return true;
}

// save all sheets in memory into an Excel file
bool MainWindow::save_excel_file(const QString &file_path)
{
    if (sheet_names_.isEmpty()) {
        Document empty_doc;
        return empty_doc.saveAs(file_path);
    }

    Document xlsx;

    QString default_sheet_name;
    if (auto ws = dynamic_cast<Worksheet *>(xlsx.currentWorksheet())) {
        default_sheet_name = ws->sheetName(); // usually "Sheet1"
    }

    bool used_default_sheet = false;

    for (const QString &sheet_name : sheet_names_) {
        QStandardItemModel *model = sheet_models_.value(sheet_name, nullptr);
        if (!model) {
            continue;
        }

        if (!used_default_sheet && !default_sheet_name.isEmpty()) {
            xlsx.renameSheet(default_sheet_name, sheet_name);
            xlsx.selectSheet(sheet_name);
            used_default_sheet = true;
        } else {
            xlsx.addSheet(sheet_name);
            xlsx.selectSheet(sheet_name);
        }

        const int row_count = model->rowCount();
        const int col_count = model->columnCount();

        for (int r = 0; r < row_count; ++r) {
            for (int c = 0; c < col_count; ++c) {
                QModelIndex index = model->index(r, c);
                QVariant value = model->data(index, Qt::EditRole);

                if (model->data(index, Qt::CheckStateRole).isValid()) {
                    const bool checked =
                        (model->data(index, Qt::CheckStateRole).toInt()
                         == Qt::Checked);
                    value = checked;
                }

                if (value.isNull()) {
                    continue;
                }

                const int excel_row = r + 1;
                const int excel_col = c + 1;

                Format fmt = format_for_cell(sheet_name, r, c);
                if (fmt.isValid()) {
                    xlsx.write(excel_row, excel_col, value, fmt);
                } else {
                    xlsx.write(excel_row, excel_col, value);
                }
            }
        }
    }

    return xlsx.saveAs(file_path);
}

void MainWindow::on_action_about_triggered()
{
    QString text;
    text += "<b>ExcelTableEditor</b><br>";
    text += "A simple Excel editor example using <b>Qt Widgets</b> and <b>QXlsx</b>.<br><br>";
    text += "Features:<ul>"
            "<li>Load / Save Excel (.xlsx)</li>"
            "<li>Multiple sheet support</li>"
            "<li>Editable sheet data</li>"
            "<li>Sheet rename / add / delete / reorder</li>"
            "<li>Basic cell formatting</li>"
            "<li>Insert rows / columns</li>"
            "</ul>";
    text += "<br>Project: <a href=\"https://github.com/QtExcel/QXlsx\">QXlsx GitHub</a><br>";
    text += "First Author: Jay Two<br>";

    QMessageBox::about(this, tr("About ExcelTableEditor"), text);
}

// ----------------------------
// row / column insertion logic
// ----------------------------

// row insertion button: insert a new row above the selected row,
// or append to the bottom if nothing is selected
void MainWindow::on_add_row_button_clicked()
{
    if (!current_model_) {
        return;
    }

    int insert_row = current_model_->rowCount();

    if (table_view_ && table_view_->selectionModel()) {
        const QModelIndexList indexes =
            table_view_->selectionModel()->selectedIndexes();
        if (!indexes.isEmpty()) {
            insert_row = indexes.first().row();
            // find the topmost row among selected cells
            for (const QModelIndex &idx : indexes) {
                if (idx.row() < insert_row) {
                    insert_row = idx.row();
                }
            }
        }
    }

    current_model_->insertRow(insert_row);

           // update vertical header numbers (1,2,3,...)
    const int row_count = current_model_->rowCount();
    for (int r = 0; r < row_count; ++r) {
        current_model_->setHeaderData(r, Qt::Vertical, QString::number(r + 1));
    }

           // for simplicity, clear the format map after row insertion
           // (format indices would be shifted otherwise)
    if (!current_sheet_name_.isEmpty()) {
        sheet_formats_[current_sheet_name_].clear();
    }

    is_modified_ = true;
    statusBar()->showMessage(tr("Row inserted"), 2000);
}

// column insertion button: insert a new column to the left of the selected column,
// or append to the right if nothing is selected
void MainWindow::on_add_column_button_clicked()
{
    if (!current_model_) {
        return;
    }

    int insert_col = current_model_->columnCount();

    if (table_view_ && table_view_->selectionModel()) {
        const QModelIndexList indexes =
            table_view_->selectionModel()->selectedIndexes();
        if (!indexes.isEmpty()) {
            insert_col = indexes.first().column();
            // find the leftmost column among selected cells
            for (const QModelIndex &idx : indexes) {
                if (idx.column() < insert_col) {
                    insert_col = idx.column();
                }
            }
        }
    }

    current_model_->insertColumn(insert_col);

           // update horizontal header numbers (1,2,3,...)
    const int col_count = current_model_->columnCount();
    for (int c = 0; c < col_count; ++c) {
        current_model_->setHeaderData(c, Qt::Horizontal, QString::number(c + 1));
    }

           // for simplicity, clear the format map after column insertion
           // (format indices would be shifted otherwise)
    if (!current_sheet_name_.isEmpty()) {
        sheet_formats_[current_sheet_name_].clear();
    }

    is_modified_ = true;
    statusBar()->showMessage(tr("Column inserted"), 2000);
}
