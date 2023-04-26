
#ifndef MOUSES_H
#define MOUSES_H

#include<QObject>
#include<QPushButton>
#include<QMouseEvent>

class Mouses:public QMouseEvent
{
    Q_OBJECT

signals:

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MOUSES_H
