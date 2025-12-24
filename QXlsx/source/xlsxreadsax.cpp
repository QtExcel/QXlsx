#include "xlsxdocument.h"
#include "xlsxworkbook.h"
#include "xlsxzipreader_p.h"    // QXlsx internal zip reader (adjust include as per project structure)

#include "xlsxreadsax.h"

#include <QtCore>
#include <QXmlStreamReader>

namespace QXlsx {

int parse_col_letters(const QStringView& s, int* letters_len)
{
    // A -> 1, Z -> 26, AA -> 27 ...
    int col = 0;
    int len = 0;
    for (int i = 0; i < s.size(); ++i) {
        const QChar ch = s.at(i);
        if (ch < QLatin1Char('A') || ch > QLatin1Char('Z'))
            break;
        col = col * 26 + (ch.unicode() - QLatin1Char('A').unicode() + 1);
        ++len;
    }
    if (letters_len)
        *letters_len = len;
    return col;
}

bool parse_cell_ref(const QString& r, int* out_row, int* out_col)
{
    // Example: "C12"
    int letters_len = 0;
    int col = parse_col_letters(QStringView(r), &letters_len);
    if (col <= 0 || letters_len <= 0)
        return false;
    bool ok = false;
    int row = r.mid(letters_len).toInt(&ok);
    if (!ok || row <= 0)
        return false;
    if (out_row) *out_row = row;
    if (out_col) *out_col = col;
    return true;
}

QStringList load_shared_strings_all(ZipReader& zip)
{
    QStringList out;
    const QByteArray xml = zip.fileData(QStringLiteral("xl/sharedStrings.xml"));
    if (xml.isEmpty())
        return out;

    QXmlStreamReader rd(xml);

    bool in_si = false;
    QString acc;

    while (!rd.atEnd()) {
        rd.readNext();
        if (rd.isStartElement()) {
            const auto name = rd.name();
            if (name == QLatin1String("si")) {
                in_si = true;
                acc.clear();
            } else if (in_si && name == QLatin1String("t")) {
                acc += rd.readElementText(QXmlStreamReader::IncludeChildElements);
            }
        } else if (rd.isEndElement()) {
            const auto name = rd.name();
            if (name == QLatin1String("si")) {
                in_si = false;
                out.push_back(acc);
            }
        }
    }
    return out;
}

bool read_sheet_xml_sax(const QByteArray& sheet_xml,
                        const sax_options& opt,
                        const QStringList* shared_strings,
                        const sax_cell_callback& on_cell)
{
    QXmlStreamReader rd(sheet_xml);

    bool in_sheetdata = false;
    bool in_c = false;
    bool in_v = false;

    QString cell_r;
    QString cell_t;
    QString cell_s;
    QString v_text;

    while (!rd.atEnd()) {
        rd.readNext();

        if (rd.isStartElement()) {
            const auto name = rd.name();

            if (name == QLatin1String("sheetData")) {
                in_sheetdata = true;
            } else if (in_sheetdata && name == QLatin1String("c")) {
                in_c = true;
                cell_r = rd.attributes().value(QLatin1String("r")).toString();
                cell_t = rd.attributes().value(QLatin1String("t")).toString();
                cell_s = rd.attributes().value(QLatin1String("s")).toString();
                v_text.clear();
            } else if (in_c && name == QLatin1String("v")) {
                in_v = true;
                v_text = rd.readElementText(QXmlStreamReader::IncludeChildElements);
                in_v = false;
            } else if (in_c && name == QLatin1String("f")) {
                const QString f = rd.readElementText(QXmlStreamReader::IncludeChildElements);
                if (opt.read_formulas_as_text) {
                    cell_t = QLatin1String("str");
                    v_text = f;
                }
            } else if (in_c && name == QLatin1String("t") && cell_t == QLatin1String("inlineStr")) {
                in_v = true;
                v_text = rd.readElementText(QXmlStreamReader::IncludeChildElements);
                in_v = false;
            }
        } else if (rd.isEndElement()) {
            const auto name = rd.name();

            if (name == QLatin1String("sheetData")) {
                in_sheetdata = false;
                if (opt.stop_on_empty_sheetdata)
                    break;
            } else if (in_c && name == QLatin1String("c")) {
                in_c = false;

                int row = 0, col = 0;
                if (!parse_cell_ref(cell_r, &row, &col)) {
                    continue;
                }

                sax_cell c;
                c.row = row;
                c.col = col;

                if (cell_t == QLatin1String("s")) {
                    bool ok = false;
                    const int idx = v_text.toInt(&ok);
                    if (ok && shared_strings && idx >= 0 && idx < shared_strings->size())
                        c.value = (*shared_strings)[idx];
                    else
                        c.value = v_text;
                } else if (cell_t == QLatin1String("b")) {
                    c.value = (v_text == QLatin1String("1"));
                } else {
                    bool ok = false;
                    const double d = v_text.toDouble(&ok);
                    c.value = ok ? QVariant(d) : QVariant(v_text);
                }

                if (on_cell) {
                    if (!on_cell(c))
                        return true;
                }
            }
        }
    }

    return !rd.hasError();
}

} // namespace QXlsx
