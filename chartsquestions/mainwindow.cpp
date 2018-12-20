#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()),this,SLOT(generator()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generator()
{
    sat_calc calc;
    calc.generate_report();

    /*
    int check=0;
    if(ui->lineEdit_chrom->text()!="*.txt"&&!ui->lineEdit_chrom->text().isEmpty()){
        calc.get_chromatogram(ui->lineEdit_chrom->text());
        check+=1;
    }
    if(!ui->lineEdit_report->text().isEmpty()){
        check+=1;
        calc.get_report_file(ui->lineEdit_report->text());
    }
    if(!ui->lineEdit_sheet->text().isEmpty()){
        check+=1;
        calc.get_sheet_name(ui->lineEdit_sheet->text());
    }

    if(!ui->lineEdit_prec->text().isEmpty()){
        check+=1;
        calc.get_precision(ui->lineEdit_prec->text().toDouble());
    }

    if(4==check)
        calc.generate_report();
    */
}
