#include "mypushbutton.h"
#include <QDebug>

MyPushButton::MyPushButton(QString normalImg, QString mouseOnImg, bool init_state): is_forbidden(init_state)
{

    imgPath = normalImg;
    mouseOnImgPath = mouseOnImg;

    QPixmap pixmap;
    bool ret = pixmap.load(imgPath);
    if (!ret){
        qDebug() << normalImg << "加载图片失败！";
    }

    //设置图片的固定尺寸
    this->setFixedSize(pixmap.width()*0.1, pixmap.height()*0.1);

    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pixmap);

    //设置图标大小
    this->setIconSize(QSize(pixmap.width()*0.1, pixmap.height()*0.1));

    //连接光标进入和离开事件
    installEventFilter(this);

    btnTimer = new QTimer(this);
    connect(btnTimer, &QTimer::timeout, [=](){
        this->setVisible(!is_forbidden);
    });

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, [=](){
        this->changeState();
        this->moveDown();
        moveTimer->stop();
    });
}

void MyPushButton::moveUp(){
    QPropertyAnimation* animationl = new QPropertyAnimation(this, "geometry");

    //设置时间间隔，单位毫秒：用100ms完成向上动作
    animationl->setDuration(100);

    //创建起始位置
    animationl->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animationl->setEndValue(QRect(this->x(),this->y()-s,this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce为弹跳效果
    animationl->setEasingCurve(QEasingCurve::Linear);

    //开始执行动画
    animationl->start();

    btnTimer->start(100);
}

void MyPushButton::moveDown(){
    QPropertyAnimation* animationl = new QPropertyAnimation(this, "geometry");

    //设置时间间隔，单位毫秒：用100ms完成向下动作
    animationl->setDuration(100);

    //创建起始位置
    animationl->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animationl->setEndValue(QRect(this->x(),this->y()+s,this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce为弹跳效果
    animationl->setEasingCurve(QEasingCurve::Linear);

    //开始执行动画
    animationl->start();

    this->setVisible(true);
}

bool MyPushButton::eventFilter(QObject *obj, QEvent *event){
    if (obj == this) {

        QPixmap pixmap;

        if (event->type() == QEvent::Enter) {
            // 鼠标进入时执行动画
            bool ret = pixmap.load(mouseOnImgPath);
            if (!ret){
                qDebug() << mouseOnImgPath << "加载图片失败！";
            }

            //设置图片的固定尺寸
            this->setFixedSize(pixmap.width()*0.1, pixmap.height()*0.1);

            //设置不规则图片的样式表
            this->setStyleSheet("QPushButton{border:0px;}");

            //设置图标
            this->setIcon(pixmap);

            //设置图标大小
            this->setIconSize(QSize(pixmap.width()*0.1, pixmap.height()*0.1));
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开时执行动画
            bool ret = pixmap.load(imgPath);
            if (!ret){
                qDebug() << imgPath << "加载图片失败！";
            }

            //设置图片的固定尺寸
            this->setFixedSize(pixmap.width()*0.1, pixmap.height()*0.1);

            //设置不规则图片的样式表
            this->setStyleSheet("QPushButton{border:0px;}");

            //设置图标
            this->setIcon(pixmap);

            //设置图标大小
            this->setIconSize(QSize(pixmap.width()*0.1, pixmap.height()*0.1));
        }
    }
    return false;
}

//实现自己重写的mouseEventPress事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->is_forbidden)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}

void MyPushButton::hideImg(){
    QPixmap pixmap;
    bool ret = pixmap.load(":/null.jpg");
    if (!ret){
        qDebug() << "空白图片加载失败！";
    }

    this->setFixedSize(pixmap.width()*0.3, pixmap.height()*0.3);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width()*0.3, pixmap.height()*0.3));
}

void MyPushButton::changeState(){
    if (is_forbidden){
        is_forbidden = false;
    }
    else{
        is_forbidden = true;
    }
}

void MyPushButton::setS(int a){
    s = a;
}
