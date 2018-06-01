#include "sidedialog.h"
#include "ui_sidedialog.h"

SideDialog::SideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SideDialog)
{
    ui->setupUi(this);

    //ui->label->setText(txtIn);

    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(saveTxt()) );
}

SideDialog::~SideDialog()
{
    delete ui;
}

void SideDialog::saveTxt()
{
    txt = ui->lineEdit->text();
}

void SideDialog::setLabel(QString s)
{
    ui->label->setText(s);
}
