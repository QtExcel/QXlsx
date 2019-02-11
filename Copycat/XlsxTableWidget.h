// XlsxTableWidget.h

#ifndef XLSX_TABLE_WIDGET_H
#define XLSX_TABLE_WIDGET_H

#include <cstdio>

#include <QtGlobal>
#include <QList>
#include <QVector>

#include <QWidget>
#include <QTableWidget>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QTableWidgetSelectionRange>

class XlsxTableWidget : public QTableWidget
{
	Q_OBJECT	
public:
	explicit XlsxTableWidget(QWidget* parent = NULL);
	virtual ~XlsxTableWidget();

protected:
	virtual void mousePressEvent(QMouseEvent *event); 

};

#endif
