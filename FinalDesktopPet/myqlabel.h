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
#include "myqwitem.h"
class myqlabel :
                 public QObject,public QLabel
{
public slots:
    void rsetText(QTableWidgetItem* item);
public :
    myqlabel(const QString& text, QWidget* parent = 0) :QLabel(text,parent) {}
};

