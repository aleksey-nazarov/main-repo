#ifndef MINIWIDGET_H
#define MINIWIDGET_H

#include <QFrame>

namespace Ui {
class miniWidget;
}

class miniWidget : public QFrame
{
    Q_OBJECT

public:
    explicit miniWidget(QWidget *parent = 0);
    ~miniWidget();
    void setText1(QString txt);
    void setText2(QString txt);
    void setText3(QString txt);
    void dim();
    void undim();
    QString text1();
    QString text2();
    QString text3();

private:
    Ui::miniWidget *ui;
};

#endif // MINIWIDGET_H
