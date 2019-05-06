#ifndef RMTMWTHIRDFORM_H
#define RMTMWTHIRDFORM_H

#include <QWidget>

namespace Ui {
class RmtmwThirdForm;
}

class RmtmwThirdForm : public QWidget
{
    Q_OBJECT

public:
    explicit RmtmwThirdForm(QWidget *parent = nullptr);
    ~RmtmwThirdForm();

private:
    Ui::RmtmwThirdForm *ui;
};

#endif // RMTMWTHIRDFORM_H
