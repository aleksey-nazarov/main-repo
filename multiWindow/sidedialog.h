#ifndef SIDEDIALOG_H
#define SIDEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class SideDialog;
}

class SideDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SideDialog(QWidget *parent = 0);
    ~SideDialog();

    //QString txtIn;
    QString txt;

private:
    Ui::SideDialog *ui;

private slots:
    void saveTxt();

public slots:
    void setLabel(QString s);
};

#endif // SIDEDIALOG_H
