#ifndef RMTMESSAGEBOX_H
#define RMTMESSAGEBOX_H

#include <QDialog>

namespace Ui {
class RmtMessageBox;
}

class RmtMessageBox : public QDialog
{
    Q_OBJECT

public slots:
    void    slot_msgbox_set_code(int);
public:
    explicit RmtMessageBox(QWidget *parent = nullptr);
//    explicit RmtMessageBox(QString retcode, QString errmsg,QWidget *parent = nullptr );
    ~RmtMessageBox();

private:
    Ui::RmtMessageBox *ui;
};


#endif // RMTMESSAGEBOX_H
