#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMovie>

#include "FilterHandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FilterHandler *filter_handler;
private slots:
    void handleLowPassButton();
private slots:
    void handleHighPassButton();
private slots:
    void handleBandPassButton();
private slots:
    void handleBandRejectButton();
private slots:
    void handleCombButton();
private slots:
    void handleFileButton();
private slots:
    void handleExport();
};

#endif // MAINWINDOW_H
