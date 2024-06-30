#include "entry.h"
#include "ui_entry.h"
entry::entry(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::entry)
{
    ui->setupUi(this);
    tab = new QScrollArea(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    //setWindowFlags(Qt::CustomizeWindowHint);
    setWindowTitle("ddl清单");
    QIcon icon(":/logo.jpg");
    setWindowIcon(icon);
    setFixedSize(620, 920);
    a = new itemsbox(this);
    a->setWindowOpacity(0.5);
    //setWindowOpacity(0.5);
    setStyleSheet("QMainWindow{background-image: url(:/entbackground.jpg);}");
    closebut = new QPushButton("✕", this);
    closebut->resize(40, 40);
    closebut->move(580, 0);
    closebut->setStyleSheet("QPushButton { background-color : white; border: none;}QPushButton:hover { background-color : red;}");
    closebut->show();
    QObject::connect(closebut, &QPushButton::clicked, this, &entry::close);
    closebut->hide();
    tab->resize(620, 800);
    tab->move(0, 95);
    //tab->show();
    tab->setWidget(a);
    h1=new QLabel("待办",this);
    h2=new QLabel("排序方式",this);
    h3=new QLabel("显示内容",this);
    h1->move(15,10);
    h1->setStyleSheet("QLabel{font:30px}");
    h1->resize(300,35);
    h2->move(15,50);
    h2->setStyleSheet("QLabel{font:15px;color:orange}");
    h3->move(15,70);
    h3->setStyleSheet("QLabel{font:15px;color:blue}");

    ncom = new QCheckBox("仅未完成",this);
    ncom->move(100,70);
    closebut->setWindowOpacity(0.5);
    com = new QCheckBox("仅已完成", this);
    com->move(210,70);
    all = new QCheckBox("全部", this);
    all->move(320,70);
    las = new QCheckBox("修改时间", this);
    ddl = new QCheckBox("截止时间", this);
    imp = new QCheckBox("重要性", this);
    las->move(100, 50);
    ddl->move(210, 50);
    imp->move(320, 50);
    QObject::connect(las, &QCheckBox::clicked, this, [&]() {
        ddl->setChecked(0);
        imp->setChecked(0);
        las->setChecked(1);
        feature = 1;
    });
    QObject::connect(ddl, &QCheckBox::clicked, this, [&]() {
        ddl->setChecked(1);
        imp->setChecked(0);
        las->setChecked(0);
        feature = 2;
    });
    QObject::connect(imp, &QCheckBox::clicked, this, [&]() {
        ddl->setChecked(0);
        imp->setChecked(1);
        las->setChecked(0);
        feature = 3;
    });
    QObject::connect(all, &QCheckBox::clicked, this, [&]() {kind = 3;
    all->setChecked(1);
    com->setChecked(0);
    ncom->setChecked(0); });
    QObject::connect(com, &QCheckBox::clicked, this, [&]() {kind = 2;
    all->setChecked(0);
    com->setChecked(1);
    ncom->setChecked(0); });
    QObject::connect(ncom, &QCheckBox::clicked, this, [&]() {kind = 1;
    all->setChecked(0);
    com->setChecked(0);
    ncom->setChecked(1); });
    sav = new QPushButton("保存",this);
    tab->setStyleSheet("background-color:transparent;border:none;");
    sav->setStyleSheet("QPushButton{background-color:transparent;color:black;font:20px;}QPushButton:hover { color : red;}");
    sav->move(500, 70);
    x=new QPushButton("取消",this);
    x->setStyleSheet("QPushButton{background-color:transparent;color:black;font:20px;}QPushButton:hover { color : red;}");
    x->move(400,70);
    auto reset1=[&] (){
        a->reset(feature,kind);h1->setText(QString::number(a->s1)+"条待办/"+QString::number(a->s0)+"条未完成");
    };
    QObject::connect(x,&QPushButton::clicked,this,reset1);
    auto reset0 = [&]() {
        a->save();
        a->reset(feature, kind);h1->setText(QString::number(a->s1)+"条待办/"+QString::number(a->s0)+"条未完成");
    };
    QObject::connect(sav, &QPushButton::clicked, this, reset0);
    QObject::connect(all, &QCheckBox::clicked, this, reset0);
    QObject::connect(com, &QCheckBox::clicked, this, reset0);
    QObject::connect(ncom, &QCheckBox::clicked, this, reset0);
    QObject::connect(las, &QCheckBox::clicked, this, reset0);
    QObject::connect(ddl, &QCheckBox::clicked, this, reset0);
    QObject::connect(imp, &QCheckBox::clicked, this, reset0);
    ncom->click();
    imp->click();
    las->setStyleSheet("QCheckBox{color:orange}");
    ddl->setStyleSheet("color:orange");
    imp->setStyleSheet("color:orange");
    all->setStyleSheet("color:blue");
    com->setStyleSheet("color:blue");
    ncom->setStyleSheet("color:blue");
    reset1();
    //resize(1080, 720);

    las->setStyleSheet("font:13px;color:orange");
        ddl->setStyleSheet("font:13px;color:orange");
        imp->setStyleSheet("font:13px;color:orange");
        all->setStyleSheet("font:13px;color:blue");
        com->setStyleSheet("font:13px;color:blue");
        ncom->setStyleSheet("font:13px;color:blue");
}

entry::~entry()
{}
