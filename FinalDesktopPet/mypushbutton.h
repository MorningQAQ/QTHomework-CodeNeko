#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QEvent>
#include <QTimer>

class MyPushButton : public QPushButton
{
    Q_OBJECT
private:
    bool is_forbidden;

    int s; //移动距离
public:
    QTimer* btnTimer;
    QTimer* moveTimer;

    // explicit FunctionButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg, QString mouseOnImg, bool init_state);

    QString imgPath;
    QString mouseOnImgPath;

    void moveDown();
    void moveUp();

    bool eventFilter(QObject *obj, QEvent *event);

    void mousePressEvent(QMouseEvent *e);

    void hideImg();

    void changeState();

    void setS(int a);

signals:
};

#endif // MYPUSHBUTTON_H
