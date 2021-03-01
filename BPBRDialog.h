#ifndef BP_BR_DIALOG_H
#define BP_BR_DIALOG_H

#include <QDialog>

namespace Ui {
class BPBRDialog;
}

class BPBRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BPBRDialog(QWidget *parent = 0);
    int *cutoff_1;
    int *cutoff_2;
    int *falloff;
    ~BPBRDialog();

private:
    Ui::BPBRDialog *ui;
private slots:
    void handleApplyButton();
    void handleCancelButton();
    void handleDial_1();
    void handleDial_2();
    void handleDial_3();
    void handleText_1();
    void handleText_2();
    void handleText_3();
};

#endif // BP_BR_DIALOG_H
