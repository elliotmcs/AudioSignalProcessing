#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "LPHPDialog.h"
#include "BPBRDialog.h"
#include "CMBDialog.h"
#include "Dialog.h"
#include "WavReader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lowPassButton, SIGNAL (released()),this, SLOT (handleLowPassButton()));
    connect(ui->highPassButton, SIGNAL (released()),this, SLOT (handleHighPassButton()));
    connect(ui->bandPassButton, SIGNAL (released()),this, SLOT (handleBandPassButton()));
    connect(ui->bandRejectButton, SIGNAL (released()),this, SLOT (handleBandRejectButton()));
    connect(ui->combButton, SIGNAL (released()),this, SLOT (handleCombButton()));
    connect(ui->browseButton, SIGNAL (released()),this, SLOT(handleFileButton()));
    connect(ui->exportButton, SIGNAL (released()), this, SLOT (handleExport()));
    QMovie *movie = new QMovie(":/assets/ajax-loader.gif");
    ui->loadingLabel->setMovie(movie);
    movie->start();
    ui->loadingLabel->setVisible(false);
}

void MainWindow::handleLowPassButton(){
    ui->exportButton->setEnabled(false);
    ui->loadingLabel->setVisible(true);
    LPHPDialog *dialog = new LPHPDialog;
    int cutoff = 0;
    int falloff = 0;
    dialog->cutoff = &cutoff;
    dialog->falloff = &falloff;
    dialog->exec();
    if(cutoff != -1 && falloff != -1){
        printf("Apply LP filter with cutoff %d and fallof %d\n", cutoff, falloff);
        filter_handler->applyLPFilter(cutoff, falloff);
    }
    ui->exportButton->setEnabled(true);
    ui->loadingLabel->setVisible(false);
}
void MainWindow::handleHighPassButton(){
    ui->exportButton->setEnabled(false);
    ui->loadingLabel->setVisible(true);
    LPHPDialog *dialog = new LPHPDialog;
    int cutoff = 0;
    int falloff = 0;
    dialog->cutoff = &cutoff;
    dialog->falloff = &falloff;
    dialog->exec();
    if(cutoff != -1 && falloff != -1){
        filter_handler->applyHPFilter(cutoff, falloff);
    }
    ui->exportButton->setEnabled(true);
    ui->loadingLabel->setVisible(false);
}
void MainWindow::handleBandPassButton(){
    ui->exportButton->setEnabled(false);
    ui->loadingLabel->setVisible(true);
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
        ui->exportButton->setEnabled(true);
    }
}
void MainWindow::handleBandRejectButton(){
    ui->exportButton->setEnabled(false);
    ui->loadingLabel->setVisible(true);
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
    }
    ui->exportButton->setEnabled(true);
    ui->loadingLabel->setVisible(false);
}
void MainWindow::handleCombButton(){
    ui->exportButton->setEnabled(false);
    ui->loadingLabel->setVisible(true);
    CMBDialog *dialog = new CMBDialog;
    double delay = 0;
    double amplitude = 0;
    dialog->delay = &delay;
    dialog->amplitude = &amplitude;
    dialog->exec();
    if(delay != -1 && amplitude != -1){
        filter_handler->applyCMBFilter(delay, amplitude);
    }
    ui->exportButton->setEnabled(true);
    ui->loadingLabel->setVisible(false);
}
void MainWindow::handleFileButton(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Wave Files (*.wav)"));
    ui->fileLineEdit->setText(fileName);
    filter_handler = new FilterHandler(fileName.toLatin1().data());
    ui->lowPassButton->setEnabled(true);
    ui->highPassButton->setEnabled(true);
    ui->bandPassButton->setEnabled(true);
    ui->bandRejectButton->setEnabled(true);
    ui->combButton->setEnabled(true);
}

void MainWindow::handleExport(){
    QString location = QFileDialog::getSaveFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Wave Files (*.wav)"));
    filter_handler->exportFile(location.toLatin1().data());
}

MainWindow::~MainWindow()
{
    delete ui;
}
