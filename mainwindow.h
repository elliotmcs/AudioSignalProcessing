#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMovie>

#include "filterhandler.h"

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
    void handleButton_1();
private slots:
    void handleButton_2();
private slots:
    void handleButton_3();
private slots:
    void handleButton_4();
private slots:
    void handleButton_5();
private slots:
    void handleFileButton();
private slots:
    void handleExport();
};

#endif // MAINWINDOW_H
