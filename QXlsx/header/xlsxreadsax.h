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
    QVariant value;      // bool/double/QString 등 (필요 최소)
};

using sax_cell_callback = std::function<bool(const sax_cell&)>;

// sharedStrings.xml 전체 로드(옵션) - 간단 구현
class ZipReader;
QStringList load_shared_strings_all(ZipReader& zip);

// sheet.xml을 SAX로 파싱
bool read_sheet_xml_sax(const QByteArray& sheet_xml,
                        const sax_options& opt,
                        const QStringList* shared_strings, // nullptr 가능
                        const sax_cell_callback& on_cell);

} // namespace QXlsx

#endif // XLSXREADSAX_H
