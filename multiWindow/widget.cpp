#include "widget.h"
#include "ui_widget.h"

#include "sidedialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect (ui->pushButton, SIGNAL(clicked(bool)),
             this, SLOT(showSideWindow()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showSideWindow()
{
    sw = new SideDialog();
    sw->setModal(true);

    sw->setAttribute(Qt::WA_DeleteOnClose);
    sw->setLabel(ui->lineEdit->text());
    sw->show();


    connect(sw, SIGNAL(accepted()),
            this, SLOT(setLabelTxt()));

}

void Widget::setLabelTxt()
{
    QString t = sw->txt;
    ui->label->setText(t);
}
