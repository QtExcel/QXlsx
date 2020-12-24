// xlsxdatavalidation_p.h

#pragma once

#include <QSharedData> // base class

#include "xlsxdatavalidation.h"

QT_BEGIN_NAMESPACE_XLSX

class    DataValidationPrivate : public QSharedData
{
public:
    DataValidationPrivate();
    DataValidationPrivate(DataValidation::ValidationType type, DataValidation::ValidationOperator op, const QString &formula1, const QString &formula2, bool allowBlank);
    DataValidationPrivate(const DataValidationPrivate &other);
    ~DataValidationPrivate();

    DataValidation::ValidationType validationType;
    DataValidation::ValidationOperator validationOperator;
    DataValidation::ErrorStyle errorStyle;
    bool allowBlank;
    bool isPromptMessageVisible;
    bool isErrorMessageVisible;
    QString formula1;
    QString formula2;
    QString errorMessage;
    QString errorMessageTitle;
    QString promptMessage;
    QString promptMessageTitle;
    QList<CellRange> ranges;
};

QT_END_NAMESPACE_XLSX
