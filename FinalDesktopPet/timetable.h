
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
#include "myqlabel.h"
#include<fstream>
#include<QByteArray>
#include<qcolordialog.h>
#include<qframe.h>
#include <QPalette>
QT_BEGIN_NAMESPACE
namespace Ui {
class timetable;
}
QT_END_NAMESPACE
class timetable :public QMainWindow

{
    Q_OBJECT

public:
    timetable(QWidget *parent = nullptr);
    ~timetable();
    void reset0();
    void flush();
    void show0();
    void flush1();
    void getc();
    QSize sizeHint();
private:
    Ui::timetable *ui;
    QTableWidget *TableWidget;
    myqlabel* lab;
    QCheckBox* edit;
    QLineEdit* classname,*teacher,*classroom,*rmk;
    QPushButton* def;
    QPushButton *era;
    QPushButton* choose,*bcolor,*scolor,*closebut;
    QMessageBox* hint;
    QColor c[16],C0;
    bool cho[1000],Edit,Cho;
    int sumc,latest;
    QColorDialog *fcolor;
    QSet<QString>Qs;
    QString str;
};
