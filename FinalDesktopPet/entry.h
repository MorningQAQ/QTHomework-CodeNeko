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
#include<QScrollArea>
#include <QMainWindow>
#include "ui_entry.h"
#include"itemsbox.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class entry;
}
QT_END_NAMESPACE
class entry : public QMainWindow
{
    Q_OBJECT

public:
    entry(QWidget *parent = nullptr);
    ~entry();
    itemsbox* a;
    QScrollArea* tab;
    QPushButton* sav, * closebut,*x;
    QCheckBox* las, *ddl, *imp, * all, * com, * ncom;
    QLabel* h1,*h2,*h3;
    int kind, feature;
private:
    Ui::entry *ui;
};
