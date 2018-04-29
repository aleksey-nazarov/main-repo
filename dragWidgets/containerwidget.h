#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QFrame>
class QLabel;

namespace Ui {
class ContainerWidget;
}

class ContainerWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ContainerWidget(QWidget *parent = 0);
    ~ContainerWidget();

    void fitAndCalc();

private:
    Ui::ContainerWidget *ui;
    QLabel * sumLabel;

    void positionSumLabel();


protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;

    void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;


};

#endif // CONTAINERWIDGET_H
