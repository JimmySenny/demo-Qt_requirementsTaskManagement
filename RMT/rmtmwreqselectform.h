#ifndef RMTMWREQSELECTFORM_H
#define RMTMWREQSELECTFORM_H

#include <QWidget>

namespace Ui {
class RmtmwReqSelectForm;
}

class RmtmwReqSelectForm : public QWidget
{
    Q_OBJECT

public:
    explicit RmtmwReqSelectForm(QWidget *parent = nullptr);
    ~RmtmwReqSelectForm();

private:
    Ui::RmtmwReqSelectForm *ui;
};

#endif // RMTMWREQSELECTFORM_H
