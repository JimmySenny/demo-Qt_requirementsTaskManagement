#ifndef RMTMWSECONDFORM_H
#define RMTMWSECONDFORM_H

#include <QWidget>

namespace Ui {
class RmtmwSecondForm;
}

class RmtmwSecondForm : public QWidget
{
    Q_OBJECT

public:
    explicit RmtmwSecondForm(QWidget *parent = nullptr);
    ~RmtmwSecondForm();

private:
    Ui::RmtmwSecondForm *ui;
};

#endif // RMTMWSECONDFORM_H
