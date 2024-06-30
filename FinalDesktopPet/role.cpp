#include "role.h"
#include "ui_role.h"

#include <QRandomGenerator>
#include <QSound>
#include <QDebug>

Role::Role(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Role)
    , myRoleLable(new QLabel(this))
{
    ui->setupUi(this);

    //先准备好动画和声音
    voice[0].text = "下雨了……";voice[0].voicePath = ":/mlynar/fight3.wav";voice[0].time = 1.6;
    voice[1].text = "这些东西……不配我拔剑。";voice[1].voicePath = ":/mlynar/bushu.wav";voice[1].time = 3.1;
    voice[2].text = "“不畏苦暗”……呵。一个并不值得怀念的时代。太过清醒的梦。";voice[2].voicePath = ":/mlynar/baodao.wav";voice[2].time = 9.6;
    voice[3].text = "怀念？不。我只是不能忘记这一切。在灯光照不到的地方，那些我所见的……我无能为力的事情。";voice[3].voicePath = ":/mlynar/wenhou.wav";voice[3].time = 12.1;
    voice[4].text = "即使尽头只是一声叹息。";voice[4].voicePath = ":/mlynar/fight2.wav";voice[4].time = 3.1;
    voice[5].text = "我仍然……听得见那声叹息。";voice[5].voicePath = ":/mlynar/fight1.wav";voice[5].time = 4.1;

    fight_gif[0].Action = ":/mlynar/ldle.gif";fight_gif[0].w = 213, fight_gif[0].h = 348;
    fight_gif[1].Action = ":/mlynar/die.gif";fight_gif[1].w = 300, fight_gif[1].h = 348;
    normal_gif[0].Action = ":/mlynar/interact.gif";normal_gif[0].w = 180, normal_gif[0].h = 352;
    normal_gif[1].Action = ":/mlynar/move.gif";normal_gif[1].w = 164, normal_gif[1].h = 352;

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QPixmap pixmap(":/role.png");
    pixmap = pixmap.scaled(pixmap.width()*0.2, pixmap.height()*0.2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    myRoleLable->setPixmap(pixmap);
    myRoleLable->resize(180, 352);

    QIcon icon(":/logo.jpg");
    setWindowIcon(icon);

    //鼠标，区分拖动和点击
    mouseTimer = new QTimer(this);

    //创建加号按钮
    plusBtn = new MyPushButton(":/button/plus_1.png", ":/button/plus_2.png", false);
    plusBtn->setParent(this);

    //移动按钮位置
    plusBtn->move(this->width()*0.3-plusBtn->width()*0.5, this->height()*0.3);

    plusBtn->setCursor(Qt::PointingHandCursor);

    plusBtn->setS(100);
    connect(plusBtn, &MyPushButton::clicked, [=](){
        plusBtn->changeState();
        plusBtn->moveUp();

        subBtn->changeState();
        subBtn->btnTimer->start(100);

        toolBtn->moveTimer->start(99);
        timeTableBtn->moveTimer->start(99);
        ddlBtn->moveTimer->start(99);
        galBtn->moveTimer->start(99);
        changeBtn->moveTimer->start(99);
    });

    //创建减号按钮
    subBtn = new MyPushButton(":/button/sub_1.png", ":/button/sub_2.png", true);
    subBtn->setParent(this);
    subBtn->setVisible(false);

    //移动按钮位置
    subBtn->move(this->width()*0.3-subBtn->width()*0.5, this->height()*0.1);

    subBtn->setCursor(Qt::PointingHandCursor);

    connect(subBtn, &MyPushButton::clicked, [=](){
        subBtn->changeState();
        subBtn->btnTimer->start();

        toolBtn->moveUp();
        toolBtn->changeState();

        timeTableBtn->moveUp();
        timeTableBtn->changeState();

        galBtn->moveUp();
        galBtn->changeState();

        ddlBtn->moveUp();
        ddlBtn->changeState();

        changeBtn->moveUp();
        changeBtn->changeState();

        plusBtn->moveTimer->start(100);
    });

    //创建工具按钮
    toolBtn = new MyPushButton(":/button/tool_1.png", ":/button/tool_2.png", true);
    toolBtn->setParent(this);
    toolBtn->setVisible(false);

    //移动按钮位置
    toolBtn->move(this->width()*0.3-toolBtn->width()*0.5, this->height()*0.1);

    toolBtn->setCursor(Qt::PointingHandCursor);

    toolBtn->setS(55);
    connect(toolBtn, &MyPushButton::clicked, [=](){
        myToolBug = new ToolBag;
        myToolBug->show();
    });

    //创建课表按钮
    timeTableBtn = new MyPushButton(":/button/timetable_1.png", ":/button/timetable_2.png", true);
    timeTableBtn->setParent(this);
    timeTableBtn->setVisible(false);

    //移动按钮位置
    timeTableBtn->move(this->width()*0.3-toolBtn->width()*0.5, this->height()*0.1);

    timeTableBtn->setCursor(Qt::PointingHandCursor);

    timeTableBtn->setS(110);
    connect(timeTableBtn, &MyPushButton::clicked, [=](){
        myTimeTable = new timetable;
        myTimeTable->show();
    });

    //创建ddl按钮
    ddlBtn = new MyPushButton(":/button/ddl_1.png", ":/button/ddl_2.png", true);
    ddlBtn->setParent(this);
    ddlBtn->setVisible(false);

    //移动按钮位置
    ddlBtn->move(this->width()*0.3-toolBtn->width()*0.5, this->height()*0.1);

    ddlBtn->setCursor(Qt::PointingHandCursor);

    ddlBtn->setS(165);
    connect(ddlBtn, &MyPushButton::clicked, [=](){
        myDDL = new entry;
        myDDL->show();
    });

    //创建养成按钮
    galBtn = new MyPushButton(":/button/gal_1.png", ":/button/gal_2.png", true);
    galBtn->setParent(this);
    galBtn->setVisible(false);

    //移动按钮位置
    galBtn->move(this->width()*0.3-toolBtn->width()*0.5, this->height()*0.1);

    galBtn->setCursor(Qt::PointingHandCursor);

    galBtn->setS(220);
    connect(galBtn, &MyPushButton::clicked, [=](){
        myGal = new GalSystem;
        myGal->show();
    });

    //创建切换按钮
    changeBtn = new MyPushButton(":/button/change_1.png", ":/button/change_2.png", true);
    changeBtn->setParent(this);
    changeBtn->setVisible(false);

    //移动按钮位置
    changeBtn->move(this->width()*0.3-toolBtn->width()*0.5, this->height()*0.1);

    changeBtn->setCursor(Qt::PointingHandCursor);

    changeBtn->setS(275);
    connect(changeBtn, &MyPushButton::clicked, [=](){
        if (!ingAnimation && !is_saying){
            if (state == 1){
                state = 0;
                QPixmap pixmap(":/role.png");
                pixmap = pixmap.scaled(pixmap.width()*0.2, pixmap.height()*0.2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                myRoleLable->setPixmap(pixmap);
                myRoleLable->resize(180, 352);
            }
            else{
                state = 1;
                QPixmap pixmap(":/idle.png");
                pixmap = pixmap.scaled(pixmap.width()*0.2, pixmap.height()*0.2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                myRoleLable->setPixmap(pixmap);
                myRoleLable->resize(213, 348);
            }
        }
    });
}

Role::~Role()
{
    delete ui;
}

void Role::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
    {
        mouseTimer->start(100);
        is_dragging = true;

        // 记录鼠标按下时的位置和窗口位置
        lastPos = event->globalPos();
        windowPos = this->frameGeometry().topLeft();

        connect(mouseTimer,&QTimer::timeout,[=](){
            if (!is_dragging && !ingAnimation && !is_saying) {
                this->startAnimation();
            }
            mouseTimer->stop();
        });
    }
}

void Role::mouseMoveEvent(QMouseEvent* event){
    if (event->buttons() & Qt::LeftButton)
    {
        if (is_dragging) {
            // 计算窗口移动的偏移量，并移动窗口
            QPoint delta = event->globalPos() - lastPos;
            move(windowPos + delta);
        }
        else {
            QWidget::mouseMoveEvent(event);
        }
    }
}

void Role::mouseReleaseEvent(QMouseEvent *event) {
    // 在鼠标释放时重置状态
    is_dragging = false;

    // 调用父类的mouseReleaseEvent函数以执行释放事件的默认行为
    QWidget::mouseReleaseEvent(event);
}

void Role::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick) {
        restoreWindow();
    }
}

//事件过滤器
// 重写窗口关闭事件
void Role::closeEvent(QCloseEvent *event){
    // // 阻止窗口关闭事件，将窗口隐藏并最小化到系统托盘es
    // event->ignore();
    // QMessageBox msgBox;
    // msgBox.setText("下雨了");
    // msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    // // 获取用户的选择
    // int ret = msgBox.exec();

    // // 根据用户的选择进行处理
    // if (ret == QMessageBox::Yes) {
    //     // 用户选择了"Yes",直接退出程序
    //     qApp->quit();
    // } else if (ret == QMessageBox::No) {
    //     // 用户选择了"No"，最小化到托盘
    //     this->hide();
    //     trayIcon->show();
    // }
}

// 将窗口从系统托盘中恢复
void Role::restoreWindow()
{
    this->show();
    trayIcon->hide();
}

//动画
void Role::startAnimation(){
    ingAnimation = true;
    is_saying = true;

    int num = QRandomGenerator::global()->bounded(2);

    if (this->state == 0){
        myAnimation = new QMovie(normal_gif[num].Action);

        myRoleLable->resize(normal_gif[num].w, normal_gif[num].h);

        // 将 QMovie 对象设置给 QLabel
        myRoleLable->setMovie(myAnimation);

        myRoleLable->setScaledContents(true);

        // 播放动画
        myAnimation->start();

        connect(myAnimation, &QMovie::finished, myAnimation, [&](){
            ingAnimation = false;
            delete myAnimation;
            myAnimation = NULL;

            QPixmap pixmap(":/role.png");
            pixmap = pixmap.scaled(pixmap.width()*0.2, pixmap.height()*0.2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            myRoleLable->setPixmap(pixmap);
            myRoleLable->resize(180, 352);
        });
    }
    else{
        myAnimation = new QMovie(fight_gif[num].Action);

        myRoleLable->resize(fight_gif[num].w, fight_gif[num].h);

        // 将 QMovie 对象设置给 QLabel
        myRoleLable->setMovie(myAnimation);

        myRoleLable->setScaledContents(true);

        // 播放动画
        myAnimation->start();

        connect(myAnimation, &QMovie::finished, myAnimation, [&](){
            ingAnimation = false;
            delete myAnimation;
            myAnimation = NULL;

            QPixmap pixmap(":/idle.png");
            pixmap = pixmap.scaled(pixmap.width()*0.2, pixmap.height()*0.2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            myRoleLable->setPixmap(pixmap);
            myRoleLable->resize(213, 348);
        });
    }

    textlabel = new QLabel(this);

    // 设置文本
    int num2 = QRandomGenerator::global()->bounded(6);
    textlabel->setText(voice[num2].text);

    // 创建一个半透明的黑色背景
    QPalette pal = textlabel->palette();
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 150)); // 设置背景颜色为半透明的黑色
    textlabel->setAutoFillBackground(true);
    textlabel->setPalette(pal);

    QString styleSheet = "QLabel { padding: 10px; color: white;}";
    textlabel->setStyleSheet(styleSheet);

    textlabel->move(140, 30);
    textlabel->setWordWrap(true);
    textlabel->adjustSize();

    textlabel->show();

    QSound::play(voice[num2].voicePath);

    //声音结束后关闭文字
    textTimer = new QTimer(this);
    textTimer->start(1000*voice[num2].time);
    connect(textTimer, &QTimer::timeout, [=](){
        is_saying = false;

        delete textlabel;
        textlabel = NULL;

        textTimer->stop();
    });
}
