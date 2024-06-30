#include "timetable.h"
#include "myqwitem.h"
#include "myqlabel.h"
#include "./ui_timetable.h"
#include<QDateTime>
#include<QHeaderView>
QSize timetable::sizeHint()
{
    return QSize(800, 600);
}
void timetable::getc() {
    std::ifstream I("colortab.txt", std::ios::in);
    for (int i = 0; i < 16; i++) {
        std::string co;
        std::getline(I, co);
        c[i] = QString::fromStdString(co);
    }
    I.close();
}
void timetable::show0() {
    classname->show();
    teacher->show();
    classroom->show();
    rmk->show();
    //fcolor->show();
    bcolor->show();
    QColor C1=QColor(255-C0.red(),255-C0.green(),255-C0.blue());
    str = "QPushButton {color:"+C1.name()+";border-radius: 40px; background-color : white;background-color :" + C0.name() + ";border : white;font : 14px;}";
    bcolor->setStyleSheet(str);
    scolor->hide();
}
void timetable::reset0() {
    classname->setText("");
    teacher->setText("");
    classroom->setText("");
    rmk->setText("");
    classname->hide();
    teacher->hide();
    classroom->hide();
    rmk->hide();
    bcolor->hide();
    scolor->hide();
}
void timetable::flush() {
    std::ofstream O("timetable.txt", std::ios::out);
    for (int i = 1, tot = 0; i <=7; i++) for (int j = 1; j <=12; j++) if (TableWidget->item(j, i)->text() != "") {
                TableWidget->item(j, i)->setBackground(((myqwitem*)TableWidget->item(j, i))->realcolor);
            }
            else {
                TableWidget->item(j, i)->setBackground(QColor(255,255,255,128));
            }
    for (int i = 1; i <= 7; i++) for (int j = 1; j <=12; j++) {
            //output(O,((myqwitem*)TableWidget->item(i, j))->Classroom);
            O << ((myqwitem*)TableWidget->item(j, i))->Classname.toStdString() << "\n" ;
            O << ((myqwitem*)TableWidget->item(j, i))->Classroom.toStdString() << "\n";
            O << ((myqwitem*)TableWidget->item(j, i))->Teacher.toStdString() << "\n";
            O << ((myqwitem*)TableWidget->item(j, i))->Rmk.toStdString() << "\n";
            O << ((myqwitem*)TableWidget->item(j, i))->realcolor.name().toStdString() << "\n";
        }
    O.close();
}
void timetable::flush1() {
    std::ofstream O("colortab.txt", std::ios::out);
    for (int i = 0; i < 16; i++) {
        O << fcolor->customColor(i).name().toStdString()<<"\n";
        //output(O,((myqwitem*)TableWidget->item(i, j))->Classroom);
    }
    O.close();
    getc();
}/*MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)*/
timetable::timetable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::timetable)
{
    ui->setupUi(this);

    for (int i = 0; i < 10; i++) c[i] = Qt::GlobalColor(i+8);
    c[7] = Qt::GlobalColor(4);
    c[1]= Qt::GlobalColor(7);
    c[5] = Qt::GlobalColor(6);
    c[12] = " #d0ffd0";
    c[10] = "pink";
    c[11] = "violet";
    c[9] = "orange";
    c[13] = "#49cfff";
    c[14] = "#ff988a";
    c[15] = "#d5d8ff";
    QString name = ("课程表");
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    closebut = new QPushButton("✕",this);
    setWindowTitle(name);
    QIcon icon(":/logo.jpg");
    setWindowIcon(icon);
    setFixedSize(1080, 720);

    closebut->resize(40, 40);
    closebut->move(1040, 0);
    closebut->setStyleSheet("QPushButton { background-color : white; border: none;}QPushButton:hover { background-color : red;}");
    closebut->hide();
    QObject::connect(closebut, &QPushButton::clicked, this, &timetable::close);
    //auto x=parent->findChildren<QWidget>();
    TableWidget=new QTableWidget(13, 8,this);
    TableWidget->resize(1080, 600);
    TableWidget->setStyleSheet("font:15px;border:none;background-color:rgba(255,255,255,0.5)");
    //TableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); TableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    for(int i = 1;i <= 7; i++) TableWidget->setColumnWidth(i,1049/7);
    for (int i = 1; i <= 12; i++) TableWidget->setRowHeight(i, 565 / 12);
    TableWidget->setColumnWidth(0,30);
    TableWidget->setRowHeight(0,30);
    //TableWidget->setFont(QFont("宋体", 15px));
    TableWidget->setHorizontalHeaderLabels(QStringList() << "周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六"<<"周日");
    TableWidget->setVerticalHeaderLabels(QStringList() << "1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12");
    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TableWidget->setItem(0,1,new QTableWidgetItem("周一"));
    TableWidget->setItem(0,2,new QTableWidgetItem("周二"));
    TableWidget->setItem(0,3,new QTableWidgetItem("周三"));
    TableWidget->setItem(0,4,new QTableWidgetItem("周四"));
    TableWidget->setItem(0,5,new QTableWidgetItem("周五"));
    TableWidget->setItem(0,6,new QTableWidgetItem("周六"));
    TableWidget->setItem(0,7,new QTableWidgetItem("周日"));
    for(int i=1;i<=12;i++) TableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
    auto S0=QDateTime::currentDateTime().toString("ddd");
    if(S0=="Mon") TableWidget->item(0,1)->setForeground(QColor("red"));
    if(S0=="Tue") TableWidget->item(0,2)->setForeground(QColor("red"));
    if(S0=="Wed") TableWidget->item(0,3)->setForeground(QColor("red"));
    if(S0=="Thu") TableWidget->item(0,4)->setForeground(QColor("red"));
    if(S0=="Fri") TableWidget->item(0,5)->setForeground(QColor("red"));
    if(S0=="Sat") TableWidget->item(0,6)->setForeground(QColor("red"));
    if(S0=="Sun") TableWidget->item(0,7)->setForeground(QColor("red"));
    TableWidget->verticalHeader()->hide();
    TableWidget->horizontalHeader()->hide();
    //TableWidget->hide();
    //a->setBackgroundColor(Qt::green);
    std::ifstream O("timetable.txt", std::ios::in);
    for (int i = 1; i <=7; i++) for (int j = 1; j <=12; j++) {
            std::string cn,cr,t,r,c;
            std::getline(O, cn);
            std::getline(O, cr);
            std::getline(O, t);
            std::getline(O, r);
            std::getline(O, c);
            TableWidget->setItem(j, i, new myqwitem(QString::fromStdString(cn), i * 13 + j, QString::fromStdString(cr), QString::fromStdString(t), QString::fromStdString(r) , QString::fromStdString(c)));
            TableWidget->item(j,i)->setBackground(QColor(255,255,255,128));
            //TableWidget->item(j, i)->setFlags(TableWidget->item(j, i)->flags() & ~Qt::ItemIsSelectable);//(TableWidget->item(j, i)->flags() & ; ~Qt::ItemIsSelectable);
            //TableWidget->setItem(i, j, new myqwitem("QString::fromStdString(cn)", i * 12 + j));
        }
    //TableWidget->setStyleSheet("QTableWidget::item:selected { background: transparent; }");
    O.close();
    lab=new myqlabel("",this);
    lab->resize(720, 120);
    lab->move(0, 600);
    lab->setAlignment(Qt::AlignCenter);
    lab->setFont(QFont("微软雅黑", 12));
    lab->setStyleSheet("color:white;background-color:transparent;");
    edit = new QCheckBox("开始编辑", this);
    edit->setStyleSheet("color:white;font:18px");
    edit->resize(120,80);
    edit->move(960, 610);
    def = new QPushButton("修改", this);
    def->move(650, 600);
    def->setVisible(false);
    era = new QPushButton("删除", this);
    era->move(650, 640);
    era->setVisible(false);
    choose = new QPushButton("选择已有课程", this);
    choose->move(650, 680);
    choose->setVisible(false);
    bcolor= new QPushButton("选择颜色", this);
    bcolor -> move(800, 630);
    bcolor->setVisible(false);
    bcolor->setFixedSize(80,80);
    scolor = new QPushButton("●", this);
    scolor->move(830, 680);
    C0 = "blue";
    str = "QPushButton {color:white;border-radius: 40px; background-color : white;background-color :" + C0.name() + ";border : white;font : 10px;}";
    bcolor->setStyleSheet(str);
    scolor->hide();
    setStyleSheet("QWidget{background-color:white;}");
    fcolor = new QColorDialog();
    getc();
    for (int i = 0; i < 16; i++) fcolor->setCustomColor(i, c[i]);
    fcolor->hide();
    QObject::connect(bcolor, &QPushButton::clicked, this, [&]() {
        fcolor = new QColorDialog();
        getc();
        for (int i = 0; i < 16; i++) {
            fcolor->setCustomColor(i, c[i]);
        }
        fcolor->setCurrentColor(C0);
        fcolor->show();
        QObject::connect(fcolor, &QColorDialog::currentColorChanged, this, [&](QColor cc) {
            C0 = cc;
            show0();
            flush1();
            //assert(0);
        });
        QObject::connect(fcolor, &QColorDialog::colorSelected, this, [&](QColor cc) {
            flush1();
        });
    });
    scolor->setVisible(false);
    auto f4 = [&](const QString &s) {
        if (s.trimmed() == "") return;
        for (int i = 1; i <= 7; i++) for (int j = 1; j <=12; j++)if (((myqwitem*)TableWidget->item(j, i))->Classname == s.trimmed()) {
                    if (classroom->text() == "")classroom->setText(((myqwitem*)TableWidget->item(j, i))->Classroom);
                    if (teacher->text() == "")teacher->setText(((myqwitem*)TableWidget->item(j, i))->Teacher);
                    if (rmk->text() == "")rmk->setText(((myqwitem*)TableWidget->item(j, i))->Rmk);
                    return;
                }
    };
    classname = new QLineEdit(this);
    classname->setPlaceholderText("课程名称");
    classname->resize(200, 40);
    classname->move(0, 600);
    teacher = new QLineEdit(this);
    teacher->setPlaceholderText("课程教师");
    teacher->resize(200, 40);
    teacher->move(400, 600);
    classroom = new QLineEdit(this);
    classroom->setPlaceholderText("课程地点");
    classroom->resize(200, 40);
    classroom->move(200, 600);
    rmk = new QLineEdit(this);
    rmk->setPlaceholderText("备注");
    rmk->resize(600, 80);
    rmk->move(0, 640);
    classname->setStyleSheet("background-color:rgba(255,255,255,120)");
    classroom->setStyleSheet("background-color:rgba(255,255,255,120)");
    rmk->setStyleSheet("background-color:rgba(255,255,255,120)");
    teacher->setStyleSheet("background-color:rgba(255,255,255,120)");
    reset0();
    QObject::connect(classname, &QLineEdit::textChanged, this, f4);
    auto f0 = [&]() {
        sumc = 0;
        for (int i = 1; i <=7; i++) for (int j = 1; j <=12; j++) if (cho[i * 13 + j]) sumc++;
        if (sumc > 0) {
            if(classname->text().trimmed() ==""){
                hint = new QMessageBox();
                hint->setWindowTitle("提示");
                hint->setText(tr("请输入课程名称"));
                hint->addButton("确认", QMessageBox::AcceptRole);
                hint->exec();
                return;
            }
            for (int i = 1; i <=7; i++) for (int j =1; j <= 12; j++) if (cho[i * 13 + j]) TableWidget->setItem(j, i, new myqwitem(classname->text().trimmed(), i * 13 + j, classroom->text().trimmed(), teacher->text().trimmed(), rmk->text().trimmed(),C0));
            flush();
            edit->setChecked(0);
            edit->setChecked(1);
            return;
        }
        else {
            hint = new QMessageBox();
            hint->setWindowTitle("提示");
            hint->setText(tr("请点击表格以选择"));
            hint->addButton("确认", QMessageBox::AcceptRole);
            hint->exec();
        }
    };
    QObject::connect(def, &QPushButton::clicked, this, f0);
    auto f2 = [&]() {
        sumc = 0;
        for (int i = 1; i <= 7; i++) for (int j = 1; j <=12; j++) if (cho[i * 13 + j]) sumc++;
        if (sumc > 0) {
            for (int i = 1; i <= 7; i++) for (int j = 1; j <= 12; j++) if (cho[i * 13 + j]) TableWidget->setItem(j, i, new myqwitem(0, i * 13 + j));
            flush();
            edit->setChecked(0);
            edit->setChecked(1);
            return;
        }
        else {
            hint = new QMessageBox();
            hint->setWindowTitle("提示");
            hint->setText(tr("请点击表格以选择"));
            hint->addButton("确认", QMessageBox::AcceptRole);
            hint->exec();
        }
    };
    QObject::connect(era, &QPushButton::clicked, this, f2);
    QObject::connect(choose, &QPushButton::clicked, this, [&]() {
        if (!Cho) {
            Cho = 1;
            Edit = 0;
        }
        else {
            Cho = 0;
            Edit = 1;
        }
    });
    QObject::connect(TableWidget, &QTableWidget::itemClicked, this, [&](QTableWidgetItem* item){
        if(item->row()==0||item->column()==0) return ;
        lab->rsetText(item);
    });
    //QObject::connect(TableWidget, &QTableWidget::itemClicked, lab, &myqlabel::rsetText);
    QObject::connect(TableWidget, &QTableWidget::itemClicked, this, [&](QTableWidgetItem* item) {
        if(item->row()==0||item->column()==0) return ;
        if (!Edit&&!Cho) return;
        if (Cho) {
            latest = ((myqwitem*)item)->pos;
            if (item->text() != "") {
                classname->setText(((myqwitem*)item)->Classname);
                teacher->setText(((myqwitem*)item)->Teacher);
                classroom->setText(((myqwitem*)item)->Classroom);
                rmk->setText(((myqwitem*)item)->Rmk);
                C0 = ((myqwitem*)item)->realcolor;
                show0();
                choose->click();
            }
            return;
        }
        cho[((myqwitem*)item)->pos] ^= 1;

        if (cho[((myqwitem*)item)->pos]) {
            ((myqwitem*)item)->realcolor = item->background().color();
            item->setBackground(QColor("blue"));
        }
        else {
            auto s=QColor(((myqwitem*)item)->realcolor.name()+"80");
            item->setBackground(QColor(255,255,255,128));
        }
    });
    Edit = 1;
    auto f1 = [&]() {
        if (Edit||Cho) {
            def->setVisible(false);
            era->setVisible(false);
            choose->hide();
            reset0();
            ((myqlabel*)lab)->setText ("点击课表查看详情");
            lab->show();
            Cho = 0;
            Edit = 0;
        }
        else {
            def->show();
            era->show();
            choose->show();
            era->setChecked(false);
            def->setChecked(false);
            choose->setChecked(false);
            memset(cho, 0, sizeof(cho));
            lab->setVisible(false);
            Qs.clear();
            for (int i = 1; i <=7; i++) for (int j = 1; j <=12; j++) {
                    Qs.insert(((myqwitem*)TableWidget->item(j, i))->realcolor.name());
                }
            C0 = "white";
            getc();
            for (int i = 0; i < 16; i++) {
                if (!Qs.contains(c[i].name())) C0 = c[i];
            }
            show0();
            latest = -1;
            Edit = 1;
        }
        //Edit ^= 1;
        flush();
    };
    f1();
    assert(Edit == 0);
    QObject::connect(edit, &QCheckBox::stateChanged, this, f1);
    def->setFixedSize(100,30);
    def->setStyleSheet("QPushButton{background-color:#5FC523;border-radius: 6px;color:white;font-size:10pt;}");
    era->setFixedSize(100,30);
    era->setStyleSheet("QPushButton{background-color:#E8DA43;border-radius: 6px;color:white;font-size:10pt;}");
    choose->setFixedSize(100,30);
    choose->setStyleSheet("QPushButton{background-color:#C52A6E;border-radius: 6px;color:white;font-size:6pt;}");
    setStyleSheet("QMainWindow{background-image: url(:/p01.jpg);}");
    TableWidget->setCornerWidget(new QTableWidget());
    setStyleSheet("QHeaderView::section{background-color: rgba(255,255,255,0.5); color: black}\n"
                  "QTableCornerButton::section{background-color: rgba(255,255,255,0.5);\n}"
                  "QMainWindow{background-image: url(:/p01.jpg);}");
    TableWidget->setItem(0,0,new QTableWidgetItem());
    for(int i=0;i<=7;i++) TableWidget->item(0,i)->setBackground(QColor(255,255,255,128));
    for(int i=1;i<=12;i++) TableWidget->item(i,0)->setBackground(QColor(255,255,255,128));
}

timetable::~timetable()
{
    delete ui;
}
