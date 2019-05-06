#ifndef RMTMWHOMEPAGE_H
#define RMTMWHOMEPAGE_H

#include <QWidget>

namespace Ui {
class RmtmwHomePage;
}

class RmtmwHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit RmtmwHomePage(QWidget *parent = nullptr);
    ~RmtmwHomePage();

private:
    Ui::RmtmwHomePage *ui;
};

#endif // RMTMWHOMEPAGE_H
