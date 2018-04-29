#include "containerwidget.h"
#include "ui_containerwidget.h"

#include "miniwidget.h"

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QLabel>

ContainerWidget::ContainerWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ContainerWidget)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    sumLabel = new QLabel(this);
    sumLabel->setFrameShape(QFrame::StyledPanel);
    sumLabel->setFrameShadow(QFrame::Raised);
    sumLabel->setLineWidth(1);
    sumLabel->setFixedSize(100, 20);

    positionSumLabel();
}

ContainerWidget::~ContainerWidget()
{
    delete ui;
}

void ContainerWidget::positionSumLabel()
{
    int margin = 5;
    int w = this->width();
    int h = this->height();

    int x = w - margin - sumLabel->width();
    int y = h - margin - sumLabel->height();

    sumLabel->move(x, y);
}

void ContainerWidget::fitAndCalc()
{
    // упорядочивает имеющиеся минивиджеты и считает сумму по их третьим полям
    // сумма ПОКА ЧТО считается одна, включает все часы
    QList <QObject *> childrenList = this->children();
    // список первых строк минивиджетов, используется для сортировки
    QStringList mWgtNames;
    // QMap с указателями на виджеты и опять же первыми их строками
    // (указатели используются в качестве ключа на случай если попадутся одинаковые строки)
    QMap <miniWidget *, QString> mWgtMap;

    //DROP
    //sumLabel->setText("ИТОГО: " + QString::number(childrenList.size()));
    //positionSumLabel();
    //return;

    for (int i = 0; i < childrenList.size(); i++) {
        if ( static_cast<QLabel*>(childrenList.at(i)) ==
             sumLabel ) {
            continue; // sumLabel рассматривается отдельно и нас не интересует
        }
        miniWidget * mWgt = static_cast<miniWidget*>(childrenList.at(i));
        QString text1 = mWgt->text1();
        mWgtNames.append(text1);
        mWgtMap.insert(mWgt, text1);
    }
    mWgtNames.sort(Qt::CaseInsensitive);

    if ( mWgtNames.size() == 0 ) {
        // сразу штык в землю, если работать просто не с чем
        sumLabel->setText("ИТОГО: 0");
        positionSumLabel();
        return;
    }

    // извлечем размер произвольного минивиджета
    miniWidget * mWgt = mWgtMap.key(mWgtNames.at(0), NULL);
    if (mWgt == NULL) {
        return;
    }
    QSize mWgtSize = mWgt->size();

    // рассчитываем "табличку"
    // пока не решено, что делать, если ширина контейнера меньше ширины одного минивиджета
    int margin = 5;
    int w = this->width();
    //int h = this->height();

    int columnCount = (w - margin) / (mWgtSize.width() + margin);
    if (columnCount == 0) {
        columnCount = 1; //TODO
    }

    int row = 0, col = 0, sum = 0;

    for (int i = 0; i < mWgtNames.size(); i++) {
        QString name = mWgtNames.at(i);
        mWgt = mWgtMap.key(name, NULL);
        if (mWgt == NULL) {
            return;
        }
        mWgt->move( margin + (mWgtSize.width() + margin) * col,
                    margin + (mWgtSize.height() + margin) * row );

        sum += mWgt->text3().toInt();
        mWgtMap.remove(mWgt);

        col++;
        if (col >= columnCount) {
            row++;
            col = 0;
        }
    }
    sumLabel->setText("ИТОГО: " + QString::number(sum));
    positionSumLabel();
}

void ContainerWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget * child = childAt(event->pos());

    if ( child == NULL ||
         child == sumLabel ) {
        return;
    }

    miniWidget * childMW = NULL;
    QPoint hotSpot = event->pos();

    if ( child->parent() == this ) {
        // ткнули в "сына"
        childMW = static_cast <miniWidget*> (child);
        hotSpot = hotSpot - childMW->pos();
    }
    else {
        // рекурсивно ищем виджет-"сына"
        while (true) {
            child = static_cast <miniWidget*>(child->parent());
            hotSpot = hotSpot - child->pos();
            if ( child->parent() == this ) {
                childMW = static_cast <miniWidget*> (child);
                break;
            }
            if ( child->parent() == NULL ){
                // какая-то дикая чушь. бежим отсюда
                return;
            }
        }
    }

    if ( childMW == NULL ) { // paranoid check
        return;
    }


    // создаем QPixmap для формирования QDrag-виджета
    QPixmap pixmap( childMW->size() );
    childMW->render(&pixmap);

    // в MIME-data храним указатель на исходный виджет
    QByteArray mWgtPtrData;
    QDataStream dataStream(&mWgtPtrData, QIODevice::WriteOnly);
    quintptr childPtr_seria = (quintptr) childMW;
    dataStream << childPtr_seria << hotSpot;
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-draggableminiwidgetdata", mWgtPtrData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);

    childMW->dim();

    //Qt::DropAction dropAction =
    drag->exec();
    childMW->undim();

    /*QPoint hotSpot = event->pos() - child->pos();

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(child->text());
    mimeData->setData("application/x-hotspot",
                      QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

    QPixmap pixmap(child->size());
    child->render(&pixmap);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);*/

    //childMW->setText1("YOU HIT ME!!!");
    //childMW->dim();

}

void ContainerWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-draggableminiwidgetdata") == true) {
        // несколько внешне сложных строк кода всего лишь извлекают указатель на
        // тащимый miniWidget
        QByteArray itemData = event->mimeData()->data("application/x-draggableminiwidgetdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        miniWidget * mWgt;
        quintptr mWgtPtr_seria;
        QPoint offset;
        dataStream >> mWgtPtr_seria >> offset;
        mWgt = (miniWidget *) mWgtPtr_seria;

        if (event->source() == this) {
            // переносим виджет в рамках одного контейнера
            //mWgt->move(event->pos() - offset);
            //event->setDropAction(Qt::MoveAction);
            //event->accept();
            event->ignore();
        } else {
            // забираем виджет из "вон того" контейнера и ставим в "вот этот"
            mWgt->setParent(this);
            //mWgt->setp
            mWgt->move(event->pos() - offset);
            mWgt->show();
            event->accept();

            /*
            ContainerWidget * src = qobject_cast<ContainerWidget *>(event->source());
            if (src != NULL) {
                src->fitAndCalc(); // TODO - пока что попытка автоматического пересчета
                // вызывает падение программы
            }
            */

            //event->acceptProposedAction();
            //event->ignore();


            //event->setDropAction(Qt::MoveAction);
            //event->accept();

        }
        this->fitAndCalc();
    }
    else {
        event->ignore();
    }

}

void ContainerWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-draggableminiwidgetdata") == true) {
        //event->setDropAction(Qt::MoveAction);
        //event->accept();

        if (event->source() == this) {
            event->setDropAction(Qt::IgnoreAction);
            event->ignore();
        } else {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
    } else {
        event->ignore();

    }
}

void ContainerWidget::resizeEvent(QResizeEvent *event)
{
    fitAndCalc();
}
