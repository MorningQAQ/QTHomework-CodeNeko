#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QPushButton>
#include<QCheckBox>
#include <QLineEdit>
#include <QMessageBox>
#include<fstream>
#include<QByteArray>
#include<qcolordialog.h>
#include<qframe.h>
#include<qdatetime.h>
#include<QFont>
class itembox :
                public QWidget
{
    Q_OBJECT
public:
    QLineEdit* item, * ddl_y, * ddl_m, * ddl_d;
    QPushButton *imp,*inc,*dec,*comp,*del,*LT,*simp,*D,*U;
    bool done,Del;
    void ri() {
        int i=this->imp->text().toInt();
        QString str;
        while(i>=2) str+="★",i-=2;
        if(i==1) str+="✰";
        simp->setText(str);
    }
    itembox(QWidget* parent): QWidget(parent) {
        resize(590, 100);
        item = new QLineEdit (this);
        item->setPlaceholderText("事项");
        item->setStyleSheet("font:13px");
        ddl_y = new QLineEdit(this);
        ddl_y->setPlaceholderText("          年");
        ddl_m= new QLineEdit(this);
        ddl_m->setPlaceholderText("   月");
        ddl_d = new QLineEdit(this);
        ddl_d->setPlaceholderText("   日");
        imp = new QPushButton("5",this);
        imp->hide();
        simp=new QPushButton("★★✰",this);
        simp->setStyleSheet("color:red;font:16px");
        simp->resize(80, 40);
        inc = new QPushButton("↑", this);
        dec = new QPushButton("↓", this);
        inc->setStyleSheet("QPushButton{font:22px;color:gray}QPushButton:hover{color:black}");
        dec->setStyleSheet("QPushButton{font:22px;color:gray}QPushButton:hover{color:black}");
        inc->resize(40, 40);
        dec->resize(40, 40);
        item->resize(200, 90);
        ddl_y->resize(57, 30);
        ddl_m->resize(30, 30);
        ddl_d->resize(30, 30);
        item->move(80, 0);
        ddl_y->move(330+3, 10);
        ddl_m->move(390, 10);
        ddl_d->move(420, 10);
        simp->move(450, 10);
        inc->move(450, 40);
        dec->move(490, 40);
        comp = new QPushButton("○", this);
        comp->setStyleSheet("font:45px;color:brown");
        done = 0;
        D=new QPushButton("deadline:",this);
        D->resize(53,30);
        D->move(280,10);
        U=new QPushButton("◆  "+QDateTime::currentDateTime().toString("yyyy/MM/dd/hh:mm:ss"),this);
        U->move(280,40);
        U->resize(170,30);
        QFont font;
        font.setBold(true);
        font.setPointSize(10);
        ddl_y->setFont(font);ddl_m->setFont(font);ddl_d->setFont(font);
        //U->hide();
        LT =new QPushButton( "",this);
        LT->hide();
        auto upd = [&]() {
            LT->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
            U->setText("◆  "+QDateTime::currentDateTime().toString("yyyy/MM/dd/hh:mm:ss"));
        };
        QObject::connect(comp, &QPushButton::clicked, this, [&]() {
            if (!done) comp->setText("☺");
            else {
                comp->setText("○");
                if(ddl_y->text().toInt()<QDateTime::currentDateTime().toString("yyyy").toInt())  comp->setText("☹");
                if(ddl_y->text().toInt()==QDateTime::currentDateTime().toString("yyyy").toInt())  {
                    if(ddl_m->text().toInt()<QDateTime::currentDateTime().toString("MM").toInt()) comp->setText("☹");
                    if(ddl_m->text().toInt()==QDateTime::currentDateTime().toString("MM").toInt()) {
                        if(ddl_d->text().toInt()<QDateTime::currentDateTime().toString("dd").toInt()) comp->setText("☹");
                        if(ddl_d->text().toInt()==QDateTime::currentDateTime().toString("dd").toInt()) comp->setText("!!!");
                    }
                }
                //if(fun())
            }
            done ^= 1;
            //LT->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
        });
        QObject::connect(inc, &QPushButton::clicked, this, [&]() {
            imp->setText(QString::number(std::min(imp->text().toInt() + 1,10)));
            ri();
            LT->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
            U->setText("◆  "+QDateTime::currentDateTime().toString("yyyy/MM/dd/hh:mm:ss"));
        });
        QObject::connect(dec, &QPushButton::clicked, this, [&]() {
            imp->setText(QString::number(std::max(1,imp->text().toInt() - 1)));
            ri();
            LT->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
            U->setText("◆  "+QDateTime::currentDateTime().toString("yyyy/MM/dd/hh:mm:ss"));
        });
        del = new QPushButton("移除", this);
        del->setStyleSheet("QPushButton{color:black;font:18px}QPushButton:hover{color:red;}");
        Del = 0;
        QObject::connect(del, &QPushButton::clicked, this, [&]() {
            Del ^= 1;
            if (Del == 0) del->setText("移除"),del->setStyleSheet("QPushButton{color:black;font:18px}QPushButton:hover{color:red;}");
            else del->setText("恢复"),del->setStyleSheet("QPushButton{color:black;font:18px}QPushButton:hover{color:green;}");
            // LT->setText(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
        });

        QObject::connect(item, &QLineEdit::textEdited, this, upd);
        QObject::connect(ddl_y, &QLineEdit::textEdited, this, upd);
        QObject::connect(ddl_m, &QLineEdit::textEdited, this, upd);
        QObject::connect(ddl_d, &QLineEdit::textEdited, this, upd);
        comp->resize(70, 70);
        del->resize(50, 70);
        comp->move(10, 10);
        del->move(540, 10);
        show();
    }
};

