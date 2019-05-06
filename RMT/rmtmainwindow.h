#ifndef RMTMAINWINDOW_H
#define RMTMAINWINDOW_H

#include <QMainWindow>
#include "rmtcomm.h"

namespace Ui {
class RmtMainWindow;
}

class RmtMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RmtMainWindow(QWidget *parent = nullptr);
    ~RmtMainWindow();
    bool rmw_init();

private:
    Ui::RmtMainWindow *ui;
    QLabel * label_1;
    QLabel * label_2;
};

#endif // RMTMAINWINDOW_H
