#ifndef LP_HP_DIALOG_H
#define LP_HP_DIALOG_H

#include <QDialog>

namespace Ui {
class LPHPDialog;
}

class LPHPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LPHPDialog(QWidget *parent = 0);
    int *cutoff;
    int *falloff;
    QWidget *parent_widget;
    ~LPHPDialog();

private:
    Ui::LPHPDialog *ui;
private slots:
    void handleApplyButton();
    void handleCancelButton();
    void handleDial_1();
    void handleDial_2();
    void handleText_1();
    void handleText_2();
};

#endif // LP_HP_DIALOG_H
