#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lp_hp_dialog.h"
#include "bp_br_dialog.h"
#include "cmb_dialog.h"
#include "dialog.h"
#include "WavReader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (handleButton_1()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (handleButton_2()));
    connect(ui->pushButton_3, SIGNAL (released()),this, SLOT (handleButton_3()));
    connect(ui->pushButton_4, SIGNAL (released()),this, SLOT (handleButton_4()));
    connect(ui->pushButton_5, SIGNAL (released()),this, SLOT (handleButton_5()));
    connect(ui->toolButton, SIGNAL (released()),this, SLOT(handleFileButton()));
    connect(ui->pushButton_6, SIGNAL (released()), this, SLOT (handleExport()));
}

void MainWindow::handleButton_1(){
    LPHPDialog *dialog = new LPHPDialog;
    int cutoff = 0;
    int falloff = 0;
    dialog->cutoff = &cutoff;
    dialog->falloff = &falloff;
    dialog->exec();
    if(cutoff != -1 && falloff != -1){
        filter_handler->applyLPFilter(cutoff, falloff);
        ui->pushButton_6->setEnabled(true);
    }
}
void MainWindow::handleButton_2(){
    LPHPDialog *dialog = new LPHPDialog;
    int cutoff = 0;
    int falloff = 0;
    dialog->cutoff = &cutoff;
    dialog->falloff = &falloff;
    dialog->exec();
    if(cutoff != -1 && falloff != -1){
        filter_handler->applyHPFilter(cutoff, falloff);
        ui->pushButton_6->setEnabled(true);
    }
}
void MainWindow::handleButton_3(){
    BPBRDialog *dialog = new BPBRDialog;
    int cutoff_1 = 0;
    int cutoff_2 = 0;
    int falloff = 0;
    dialog->cutoff_1 = &cutoff_1;
    dialog->cutoff_2 = &cutoff_2;
    dialog->falloff = &falloff;
    dialog->exec();
    if(cutoff_1 != -1 && cutoff_2 != -1 && falloff != -1){
        filter_handler->applyBPFilter(cutoff_1, cutoff_2, falloff);
        ui->pushButton_6->setEnabled(true);
    }
}
void MainWindow::handleButton_4(){
    BPBRDialog *dialog = new BPBRDialog;
    int cutoff_1 = 0;
    int cutoff_2 = 0;
    int falloff = 0;
    dialog->cutoff_1 = &cutoff_1;
    dialog->cutoff_2 = &cutoff_2;
    dialog->falloff = &falloff;
    dialog->exec();
    if(cutoff_1 != -1 && cutoff_2 != -1 && falloff != -1){
        filter_handler->applyBRFilter(cutoff_1, cutoff_2, falloff);
        ui->pushButton_6->setEnabled(true);
    }
}
void MainWindow::handleButton_5(){
    CMBDialog *dialog = new CMBDialog;
    double delay = 0;
    double amplitude = 0;
    dialog->delay = &delay;
    dialog->amplitude = &amplitude;
    dialog->exec();
    if(delay != -1 && amplitude != -1){
        filter_handler->applyCMBFilter(delay, amplitude);
        ui->pushButton_6->setEnabled(true);
    }
}
void MainWindow::handleFileButton(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home/",
                                                    tr("Wave Files (*.wav)"));
    ui->lineEdit->setText(fileName);
    filter_handler = new FilterHandler(fileName.toLatin1().data());
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::handleExport(){
    QString location = QFileDialog::getSaveFileName(this, tr("Open File"),
                                                    "/home/",
                                                    tr("Wave Files (*.wav)"));
    filter_handler->exportFile(location.toLatin1().data());
}

MainWindow::~MainWindow()
{
    delete ui;
}
