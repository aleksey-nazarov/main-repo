#ifndef SIDEWINDOW_H
#define SIDEWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class SideWindow;
}

class SideWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SideWindow(QWidget *parent = 0);
    ~SideWindow();

    QString txt;

private:
    Ui::SideWindow *ui;

private slots:
    void saveTxt();
};

#endif // SIDEWINDOW_H
