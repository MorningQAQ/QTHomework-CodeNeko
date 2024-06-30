#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QFont>
#include <fstream>
#include <QByteArray>
#include <qcolordialog.h>
#include <qframe.h>
#include "itembox.h"
#include "cmp3.h"
#include "cmp2.h"
#include "cmp1.h"
class itemsbox :
                 public QWidget
{
public:
    QPushButton* add;
    QVector<itembox*>items;
    int s0,s1;
    itemsbox(QWidget* parent) :QWidget(parent) {
        resize(590, 100);
        setStyleSheet("QWidget{background-color:transparent;}");
        //setStyleSheet("QWidget{background-color:yellow;}");
        setWindowOpacity(0.5);
        add = new QPushButton("+", this);
        add->move(260, 0);
        add->resize(70, 50);
        QObject::connect(add, &QPushButton::clicked, this, [&]() {
            auto y = add->pos().y();
            itembox *i=new itembox(this);
            i->move(0, y);
            add->move(260, y + 100);
            resize(590, size().height() + 100);
            items.push_back(i);
        });
        reset(3, 1);
    }
    void save();
    void reset(int f, int k);
};

