#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QPushButton>
#include "ui_timetable.h"
class myqwitem :
                 public QObject,public  QTableWidgetItem
{
    Q_OBJECT
public:
    QString infrom,Classname,Classroom,Teacher,Rmk;
    int pos;
    QColor realcolor;
    myqwitem(const QString& s = 0, const int& id = 0, const QString& classroom = 0, const QString& teacher = 0,const QString &rmk=0,const QColor &c="white") :QTableWidgetItem(s) {
        pos = id;
        setFlags(flags() & ~Qt::ItemIsSelectable);
        if (s == "") {
            infrom = Classname = Classroom = Teacher =Rmk= s;
            return;
        }
        infrom = "课程："+s;
        Classroom = classroom;
        Teacher = teacher;
        Rmk = rmk;
        Classname = s;
        if (classroom != "") infrom += " 教室：" + classroom;
        //infrom += "\n";
        if (teacher != "") infrom += " 教师：" + teacher+"\n";
        infrom += rmk;
        realcolor = c;
    }
    virtual QString text();
};

