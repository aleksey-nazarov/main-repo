#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "sidedialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    SideDialog * sw;

private slots:
    void showSideWindow();
    void setLabelTxt();
};

#endif // WIDGET_H
