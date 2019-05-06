#ifndef RMTMWFIRSTFORM_H
#define RMTMWFIRSTFORM_H

#include <QWidget>

namespace Ui {
class RmtmwFirstForm;
}

class RmtmwFirstForm : public QWidget
{
    Q_OBJECT

public:
    explicit RmtmwFirstForm(QWidget *parent = nullptr);
    ~RmtmwFirstForm();

private:
    Ui::RmtmwFirstForm *ui;
};

#endif // RMTMWFIRSTFORM_H
