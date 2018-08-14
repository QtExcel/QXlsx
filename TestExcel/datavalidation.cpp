// datavalidation.cpp

// QXlsx
// MIT License
// https://github.com/j2doll/QXlsx
//
// QtXlsx
// https://github.com/dbzhang800/QtXlsxWriter
// http://qtxlsx.debao.me/
// MIT License

#include <QtCore>
#include "xlsxdocument.h"
#include "xlsxdatavalidation.h"

using namespace QXlsx;

int datavalidation()
{
    Document xlsx;
    xlsx.write("A1", "A2 and A3:E5 only accept the number between 33 and 99");

    //![1]
    DataValidation validation(DataValidation::Whole, DataValidation::Between, "33", "99");
    validation.addRange("A2");
    validation.addRange("A3:E5");
    validation.setPromptMessage("Please Input Integer between 33 and 99");
    xlsx.addDataValidation(validation);
    //![1]

	xlsx.saveAs("datavalidation.xlsx"); 

    return 0;
}
