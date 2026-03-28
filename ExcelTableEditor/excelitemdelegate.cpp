#include "excelitemdelegate.h"

#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QLineEdit>

// Implement Delegate to provide appropriate editors based on Excel cell type

ExcelItemDelegate::ExcelItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *ExcelItemDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    Q_UNUSED(option);

    // Determine the type based on EditRole data
    const QVariant value = index.data(Qt::EditRole);
    const int type_id = value.userType();

    // numeric series: editing with double/spinbox
    if (value.canConvert<double>() &&
        type_id != QMetaType::QString &&
        type_id != QMetaType::Bool) {
        auto *spin = new QDoubleSpinBox(parent);
        spin->setDecimals(6);
        spin->setRange(-1e9, 1e9);
        spin->setSingleStep(1.0);
        return spin;
    }

    // Date/Time: QDateEdit / QDateTimeEdit
    if (type_id == QMetaType::QDate) {
        auto *date_edit = new QDateEdit(parent);
        date_edit->setCalendarPopup(true);
        date_edit->setDisplayFormat("yyyy-MM-dd");
        return date_edit;
    }

    if (type_id == QMetaType::QDateTime) {
        auto *dt_edit = new QDateTimeEdit(parent);
        dt_edit->setCalendarPopup(true);
        dt_edit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
        return dt_edit;
    }

    // String and others: using default QLineEdit
    auto *line_edit = new QLineEdit(parent);
    return line_edit;
}

void ExcelItemDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    const QVariant value = index.data(Qt::EditRole);
    const int type_id = value.userType();

    if (auto *spin = qobject_cast<QDoubleSpinBox *>(editor)) {
        spin->setValue(value.toDouble());
        return;
    }

    if (auto *date_edit = qobject_cast<QDateEdit *>(editor)) {
        date_edit->setDate(value.toDate());
        return;
    }

    if (auto *dt_edit = qobject_cast<QDateTimeEdit *>(editor)) {
        dt_edit->setDateTime(value.toDateTime());
        return;
    }

    if (auto *line_edit = qobject_cast<QLineEdit *>(editor)) {
        // Number/date can be shown after string conversion
        line_edit->setText(value.toString());
        return;
    }

    QStyledItemDelegate::setEditorData(editor, index);
}

void ExcelItemDelegate::setModelData(QWidget *editor,
                                     QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    if (auto *spin = qobject_cast<QDoubleSpinBox *>(editor)) {
        model->setData(index, spin->value(), Qt::EditRole);
        return;
    }

    if (auto *date_edit = qobject_cast<QDateEdit *>(editor)) {
        model->setData(index, date_edit->date(), Qt::EditRole);
        return;
    }

    if (auto *dt_edit = qobject_cast<QDateTimeEdit *>(editor)) {
        model->setData(index, dt_edit->dateTime(), Qt::EditRole);
        return;
    }

    if (auto *line_edit = qobject_cast<QLineEdit *>(editor)) {
        model->setData(index, line_edit->text(), Qt::EditRole);
        return;
    }

    QStyledItemDelegate::setModelData(editor, model, index);
}
