#include "BPBRDialog.h"
#include "ui_BPBRDialog.h"

BPBRDialog::BPBRDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BPBRDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (handleApplyButton()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (handleCancelButton()));
    connect(ui->dial, SIGNAL (valueChanged(int)), this, SLOT (handleDial_1()));
    connect(ui->dial_2, SIGNAL (valueChanged(int)), this, SLOT (handleDial_2()));
    connect(ui->dial_3, SIGNAL (valueChanged(int)), this, SLOT (handleDial_3()));
    connect(ui->lineEdit, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_1()));
    connect(ui->lineEdit_2, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_2()));
    connect(ui->lineEdit_3, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_3()));
}
void BPBRDialog::handleApplyButton(){
    this->close();
}
void BPBRDialog::handleCancelButton(){
    *cutoff_1 = -1;
    *cutoff_2 = -1;
    *falloff = -1;
    this->close();
}
void BPBRDialog::handleDial_1(){
    QString data;
    data.sprintf("%d", ui->dial->value());
    ui->lineEdit->setText(data);
    *cutoff_1 = ui->dial->value();
}
void BPBRDialog::handleDial_2(){
    QString data;
    data.sprintf("%d", ui->dial_2->value());
    ui->lineEdit_2->setText(data);
    *cutoff_2 = ui->dial_2->value();
}
void BPBRDialog::handleDial_3(){
    QString data;
    data.sprintf("%d", ui->dial_3->value());
    ui->lineEdit_3->setText(data);
    *falloff = ui->dial_3->value();
}
void BPBRDialog::handleText_1(){
    bool ok;
    QString data = ui->lineEdit->text();
    ui->dial->setValue(data.toInt(&ok, 10));
    *cutoff_1 = ui->dial->value();
}
void BPBRDialog::handleText_2(){
    bool ok;
    QString data = ui->lineEdit_2->text();
    ui->dial_2->setValue(data.toInt(&ok, 10));
    *cutoff_2 = ui->dial_2->value();
}
void BPBRDialog::handleText_3(){
    bool ok;
    QString data = ui->lineEdit_3->text();
    ui->dial_3->setValue(data.toInt(&ok, 10));
    *falloff = ui->dial_3->value();
}
BPBRDialog::~BPBRDialog()
{
    delete ui;
}
