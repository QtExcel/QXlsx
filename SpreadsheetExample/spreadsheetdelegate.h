// (c) The Qt Company Ltd. BSD License
// Some code is fixed by j2doll.


#ifndef SPREADSHEETDELEGATE_H
#define SPREADSHEETDELEGATE_H

#include "spreadsheet.h"

#include <QItemDelegate>

class SpreadSheetDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    SpreadSheetDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

private slots:
    void commitAndCloseEditor();
};

#endif // SPREADSHEETDELEGATE_H

