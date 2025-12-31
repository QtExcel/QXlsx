#include "dump_options.hpp"
#include "formula_dump_fullcells.hpp"
#include "formula_single_cell_evaluator.hpp"

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QDebug>

#include "xlsxdocument.h"

static void setup_parser(QCommandLineParser& p)
{
    p.setApplicationDescription("FormulaDump - dump formula cells and values (with simple evaluator)");
    p.addHelpOption();

    p.addPositionalArgument("xlsx", "Path to xlsx file.");
    p.addOption({{"s","sheet"}, "Sheet name. Empty means all sheets.", "name"});
    p.addOption({{"a","all"}, "Dump all cells (not only formula cells)."});
    p.addOption({{"n","no-eval"}, "Disable formula evaluation when cached value is empty."});
    p.addOption({{"e","empty"}, "Print even if value is empty."});
    p.addOption({{"r","max-rows"}, "Limit rows (0=unlimited).", "n", "0"});
    p.addOption({{"c","max-cols"}, "Limit cols (0=unlimited).", "n", "0"});
    p.addOption({{"1","cell"}, "Evaluate single cell: format R,C (1-based). Example: 2,4", "r,c"});
}

static bool parse_rc(const QString& s, int& r, int& c)
{
    const QStringList parts = s.split(',');
    if (parts.size() != 2) return false;
    bool ok1=false, ok2=false;
    r = parts[0].trimmed().toInt(&ok1);
    c = parts[1].trimmed().toInt(&ok2);
    return ok1 && ok2 && r>0 && c>0;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("FormulaDump");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    setup_parser(parser);
    parser.process(app);

    const QStringList args = parser.positionalArguments();
    if (args.isEmpty()) {
        parser.showHelp(1);
    }

    const QString xlsx_path = QFileInfo(args[0]).absoluteFilePath();
    const QString sheet = parser.value("sheet");

    qxlsx_dump::dump_options_t opt;
    opt.only_formula_cells = !parser.isSet("all");
    opt.evaluate_formulas  = !parser.isSet("no-eval");
    opt.print_empty_value  = parser.isSet("empty");
    opt.max_rows = parser.value("max-rows").toInt();
    opt.max_cols = parser.value("max-cols").toInt();

    QXlsx::Document doc(xlsx_path);
    if (doc.sheetNames().isEmpty()) {
        qCritical().noquote() << "Failed to open xlsx:" << xlsx_path;
        return 2;
    }

    if (parser.isSet("cell")) {
        int r=0,c=0;
        if (!parse_rc(parser.value("cell"), r, c)) {
            qCritical().noquote() << "Invalid --cell format. Use R,C like 2,4";
            return 2;
        }
        qxlsx_dump::formula_single_cell_evaluator eval(&doc);
        const QVariant v = eval.evaluate(sheet.isEmpty() ? doc.sheetNames().value(0) : sheet, r, c);
        qInfo().noquote() << QString("R %1 C %2 value: %3").arg(r).arg(c).arg(v.toString());
        return 0;
    }

    qxlsx_dump::formula_dump_fullcells dumper(&doc, opt);
    return dumper.dump(sheet);
}
