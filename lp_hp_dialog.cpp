#include "lp_hp_dialog.h"
#include "ui_lp_hp_dialog.h"
#include "mainwindow.h"

LPHPDialog::LPHPDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LPHPDialog)
{
    ui->setupUi(this);
    this->parent_widget = parent;
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (handleApplyButton()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (handleCancelButton()));
    connect(ui->dial, SIGNAL (valueChanged(int)), this, SLOT (handleDial_1()));
    connect(ui->dial_2, SIGNAL (valueChanged(int)), this, SLOT (handleDial_2()));
    connect(ui->lineEdit, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_1()));
    connect(ui->lineEdit_2, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_2()));
}
void LPHPDialog::handleApplyButton(){
    this->close();
}
void LPHPDialog::handleCancelButton(){
    *cutoff = -1;
    *falloff = -1;
    this->close();
}
void LPHPDialog::handleDial_1(){
    QString data;
    data.sprintf("%d", ui->dial->value());
    ui->lineEdit->setText(data);
    *cutoff = ui->dial->value();
}
void LPHPDialog::handleDial_2(){
    QString data;
    data.sprintf("%d", ui->dial_2->value());
    ui->lineEdit_2->setText(data);
    *falloff = ui->dial_2->value();
}
void LPHPDialog::handleText_1(){
    bool ok;
    QString data = ui->lineEdit->text();
    ui->dial->setValue(data.toInt(&ok, 10));
    *cutoff = ui->dial->value();
}
void LPHPDialog::handleText_2(){
    bool ok;
    QString data = ui->lineEdit_2->text();
    ui->dial_2->setValue(data.toInt(&ok, 10));
    *falloff = ui->dial_2->value();
}
LPHPDialog::~LPHPDialog()
{
    delete ui;
}
