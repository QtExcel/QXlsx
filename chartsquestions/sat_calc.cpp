
#include <QtGlobal>
#include <QObject>
#include <QUrl>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QDebug>

#include "sat_calc.h"

sat_calc::sat_calc(): output_line_count(5){}
sat_calc::~sat_calc(){}


void sat_calc::get_chromatogram(const QString & chromatogram){
    this->chromatogram=chromatogram;
}

void sat_calc::get_report_file(const QString & report_file){
    this->report_file=report_file;
}

void sat_calc::get_sheet_name(const QString & sheet_name){
    this->sheet_name=sheet_name;
}

void sat_calc::get_precision(const double precision){
    this->precision=precision;
}

#define QUICK_GUI_DEBUG USE

// fixed for testing by j2doll
void sat_calc::generate_report()
{
    // Define test parameters
    chromatogram = ":/Chromatogram_example.txt";
    report_file = "output.xlsx";
    sheet_name = "hello";
    precision = 0.1;

    double d1, d2, d3;

    bool isExist = QFile::exists(chromatogram);
    if (!isExist)
    {
        qDebug() << "[debug] file is not exist. : " << chromatogram;

#ifdef QUICK_GUI_DEBUG
        QMessageBox msgBox;
        msgBox.setText("File is not exist.");
        msgBox.exec();
#endif
        return;
    }

    QFile input( chromatogram );
    if ( !input.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug() << "[debug] failed to load file : " << chromatogram ;

#ifdef QUICK_GUI_DEBUG
        QMessageBox msgBox;
        msgBox.setText("Failed to load file.");
        msgBox.exec();
#endif

        return;
    }

    QXlsx::Document output(report_file);

    output.addSheet(sheet_name);
    output.selectSheet(sheet_name);
    QString chrom_data_array = "A" + QString::number(output_line_count + 3);

    unsigned int input_line_count=0;

    int step = 1;

    QString string_buffer, trash;
    QTextStream stream_buffer(&input);

    QXlsx::Format row_data, simple_green, title_stile;
    row_data.setBorderStyle(QXlsx::Format::BorderThin);
    row_data.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    row_data.setNumberFormat("0.000");
    simple_green.setFontColor(QColor(Qt::green));
    simple_green.setBorderStyle(QXlsx::Format::BorderThin);
    title_stile.setFontBold(true);
    title_stile.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    title_stile.setVerticalAlignment(QXlsx::Format::AlignVCenter);
    title_stile.setPatternBackgroundColor(QColor(225,225,225));
    title_stile.setBorderStyle(QXlsx::Format::BorderMedium);

    output.write( output_line_count+2, 1, "volume, ml", title_stile );
    output.write( output_line_count+2, 2, "OD, mAu", title_stile );

    while ( !stream_buffer.atEnd() )
    {
        if ( input_line_count % step == 0 )
        {
            for ( int j = 0 ; j < 2 ; j++ )
            {
                if ( input_line_count > 2 )
                {
                    if ( input_line_count == 2 && j == 0 )
                    {
                        stream_buffer >> string_buffer;
                    }

                    if ( input_line_count == 3 && j == 0 )
                    {
                        stream_buffer >> d1;
                        output.write( output_line_count, j+1, d1, simple_green );
                    }

                    if ( input_line_count == 4 && j == 0 )
                    {
                        stream_buffer >> d2;
                        step = (int)(precision / (d2-d1));
                        std::cout << "\nstep  " << step << std::endl;
                        output.write( output_line_count, j+1, d2, simple_green );
                    }

                    if ( j || input_line_count > 4 )
                    {
                        stream_buffer >> d3;
                        output.write( output_line_count, j+1, d3, row_data );
                    }

                } // if ( input_line_count > 2 ) ...

            } // for (int j = 0 ; j < 2 ; j++ )

            output_line_count++;

        } // if ( input_line_count % step == 0 )

        trash = stream_buffer.readLine();

        input_line_count++;
    }

    chrom_data_array += ":B" + QString::number(output_line_count - 1);

    Chart * Crom = output.insertChart( 3, 5, QSize(600, 500) );
    Crom->setChartType( Chart::CT_ScatterChart );
    Crom->addSeries( CellRange(chrom_data_array) );
    Crom->setAxisTitle( Chart::Left, QString("left title") );
    Crom->setAxisTitle( Chart::Bottom, QString("bottom title") );
    Crom->setChartTitle( QString("hello chart") );

    qDebug() << "[debug] chrom_data_array : " << chrom_data_array;

    output.saveAs(report_file);
    input.close();

    Document doc2(report_file);
    if (doc2.load())
    {
        doc2.saveAs("doc2.xlsx");
    }

    QMessageBox msgBox;
    msgBox.setText("Success to write a xlsx file.");
    msgBox.exec();

}
