#include "sidewindow.h"
#include "ui_sidewindow.h"

SideWindow::SideWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton , SIGNAL(clicked(bool)),
            this, SLOT(close()));

    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(saveTxt()) );
}

SideWindow::~SideWindow()
{
    delete ui;
}

void SideWindow::saveTxt()
{
    txt = ui->lineEdit->text();
}
