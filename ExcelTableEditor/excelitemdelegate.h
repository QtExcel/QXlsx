#ifndef EXCELITEMDELEGATE_H
#define EXCELITEMDELEGATE_H

#include <QStyledItemDelegate>

class ExcelItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ExcelItemDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif // EXCELITEMDELEGATE_H
