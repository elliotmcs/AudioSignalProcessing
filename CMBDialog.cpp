#include "CMBDialog.h"
#include "ui_CMBDialog.h"

CMBDialog::CMBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMBDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (handleApplyButton()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (handleCancelButton()));
    connect(ui->dial, SIGNAL (valueChanged(int)), this, SLOT (handleDial_1()));
    connect(ui->dial_2, SIGNAL (valueChanged(int)), this, SLOT (handleDial_2()));
    connect(ui->lineEdit, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_1()));
    connect(ui->lineEdit_2, SIGNAL (textChanged(const QString &)), this, SLOT (handleText_2()));
}
void CMBDialog::handleApplyButton(){
    this->close();
}
void CMBDialog::handleCancelButton(){
    *delay = -1;
    *amplitude = -1;
    this->close();
}
void CMBDialog::handleDial_1(){
    QString data;
    data.sprintf("%f", ui->dial->value()/10.0);
    ui->lineEdit->setText(data);
    *delay = ui->dial->value()/10.0;
}
void CMBDialog::handleDial_2(){
    QString data;
    data.sprintf("%f", ui->dial_2->value()/10.0);
    ui->lineEdit_2->setText(data);
    *amplitude = ui->dial_2->value()/10.0;
}
void CMBDialog::handleText_1(){
    bool ok;
    QString data = ui->lineEdit->text();
    ui->dial->setValue(data.toDouble(&ok)*10);
    *delay = ui->dial->value()/10.0;
}
void CMBDialog::handleText_2(){
    bool ok;
    QString data = ui->lineEdit_2->text();
    ui->dial_2->setValue(data.toDouble(&ok)*10);
    *amplitude = ui->dial_2->value()/10.0;
}
CMBDialog::~CMBDialog()
{
    delete ui;
}
