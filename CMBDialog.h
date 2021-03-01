#ifndef CMB_DIALOG_H
#define CMB_DIALOG_H

#include <QDialog>

namespace Ui {
class CMBDialog;
}

class CMBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CMBDialog(QWidget *parent = 0);
    double *delay;
    double *amplitude;
    ~CMBDialog();

private:
    Ui::CMBDialog *ui;
private slots:
    void handleApplyButton();
    void handleCancelButton();
    void handleDial_1();
    void handleDial_2();
    void handleText_1();
    void handleText_2();
};

#endif // CMB_DIALOG_H
