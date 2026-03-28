#ifndef XLSXREADSAX_H
#define XLSXREADSAX_H

#include <QXmlStreamReader>
#include <QString>
#include <QVariant>
#include <functional>

namespace QXlsx {

struct sax_options
{
    bool resolve_shared_strings = true;
    bool read_formulas_as_text = false;
    bool stop_on_empty_sheetdata = false;
};

struct sax_cell
{
    QString sheet_name;
    int row = 0;         // 1-based
    int col = 0;         // 1-based
    QVariant value;      // bool/double/QString etc. (minimum required)
};

using sax_cell_callback = std::function<bool(const sax_cell&)>;

// Load all of sharedStrings.xml (optional) - simple implementation
class ZipReader;
QStringList load_shared_strings_all(ZipReader& zip);

// Parse sheet.xml with SAX
bool read_sheet_xml_sax(const QByteArray& sheet_xml,
                        const sax_options& opt,
                        const QStringList* shared_strings, // nullptr 가능
                        const sax_cell_callback& on_cell);

} // namespace QXlsx

#endif // XLSXREADSAX_H
