#include "widget.h"
#include "ui_widget.h"

#include "miniwidget.h"
#include "containerwidget.h"
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //MiniWidget * mWgt = new MiniWidget(this);

    //connect( ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(engage()) );

    /*
    QFile infile("test.csv");
    infile.open(QIODevice::ReadOnly);
    QTextStream istream(&infile);

    QString str = istream.readLine();
    QStringList lst = str.split(";");
    ui->tableWidget->setColumnCount(lst.size());
    ui->tableWidget->setHorizontalHeaderLabels(lst);

    while (true) {
        str = istream.readLine();
        if (str.isNull() == true) {
            break;
        }
        lst = str.split(";");
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(row + 1);

        for (int i = 0; i < ui->tableWidget->columnCount(); i++) {
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setText(lst.at(i));
            ui->tableWidget->setItem(row, i, item);
        }
    }
    */

    QHBoxLayout *horizontalLayout = new QHBoxLayout;

    container1 = new ContainerWidget;
    container1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    horizontalLayout->addWidget(container1);
    container2 = new ContainerWidget;
    container2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    horizontalLayout->addWidget(container2);
    container4NewMW = new ContainerWidget;
    container4NewMW->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    horizontalLayout->addWidget(container4NewMW);
    this->setLayout(horizontalLayout);

    //ui->verticalLayout->setParent(horizontalLayout);
    QVBoxLayout * verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(ui->lineEdit_1);
    verticalLayout->addWidget(ui->lineEdit_2);
    verticalLayout->addWidget(ui->lineEdit_3);
    verticalLayout->addWidget(ui->pushButton);
    verticalLayout->addWidget(ui->pushButton_2);
    verticalLayout->addStretch();
    horizontalLayout->addLayout(verticalLayout);

    //this->takeLayout();




    /*miniWidget * miniW = new miniWidget(contain1);

    miniW->move(20, 30);

    miniWidget * miniW2 = new miniWidget(contain1);

    miniW2->move(50, 130);

    int ct = contain1->children().count();
    miniW->setText1(QString::number(ct));*/

    connect ( ui->pushButton,
              SIGNAL(clicked(bool)),
              this,
              SLOT(engage()) );

    connect ( ui->pushButton_2,
              SIGNAL(clicked(bool)),
              this,
              SLOT(ignite()) );

}

Widget::~Widget()
{
    delete ui;
}

void Widget::engage()
{
    miniWidget * mWgt = new miniWidget(container4NewMW);
    mWgt->setText1(ui->lineEdit_1->text());
    mWgt->setText2(ui->lineEdit_2->text());
    mWgt->setText3(ui->lineEdit_3->text());

    mWgt->show();
    //mWgt->move(20, 20);
    container4NewMW->fitAndCalc();
}

void Widget::ignite()
{
    container1->fitAndCalc();
    container2->fitAndCalc();
    container4NewMW->fitAndCalc();
}
