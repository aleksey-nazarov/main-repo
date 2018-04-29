#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "miniwidget.h"

class ContainerWidget;

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
    ContainerWidget * container4NewMW;
    ContainerWidget * container1;
    ContainerWidget * container2;


private slots:
    void engage();
    void ignite();
};

#endif // WIDGET_H
