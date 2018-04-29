#include "miniwidget.h"
#include "ui_miniwidget.h"

miniWidget::miniWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::miniWidget)
{
    ui->setupUi(this);
}

miniWidget::~miniWidget()
{
    delete ui;
}

void miniWidget::setText1(QString txt)
{
    ui->label1->setText(txt);
}

void miniWidget::setText2(QString txt)
{
    ui->label2->setText(txt);
}

void miniWidget::setText3(QString txt)
{
    ui->label3->setText(txt);
}

void miniWidget::dim()
{
    ui->label1->setEnabled(false);
    ui->label2->setEnabled(false);
    ui->label3->setEnabled(false);
}

void miniWidget::undim()
{
    ui->label1->setEnabled(true);
    ui->label2->setEnabled(true);
    ui->label3->setEnabled(true);
}

QString miniWidget::text1()
{
    return ui->label1->text();
}

QString miniWidget::text2()
{
    return ui->label2->text();
}

QString miniWidget::text3()
{
    return ui->label3->text();
}
