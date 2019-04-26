#ifndef RMTMAINWINDOW_H
#define RMTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class RmtMainWindow;
}

class RmtMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RmtMainWindow(QWidget *parent = nullptr);
    ~RmtMainWindow();

private:
    Ui::RmtMainWindow *ui;
};

#endif // RMTMAINWINDOW_H
