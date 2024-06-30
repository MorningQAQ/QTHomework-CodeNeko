#include "galshop.h"
#include "ui_galshop.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QDesktopServices>
#include <algorithm>
#include "galshop.h"

galShop::galShop(int& hungry,int& money,int& mood,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::galShop)
{
    ui->setupUi(this);
    setWindowTitle("燕南勺艺家农园");
    QIcon icon(":/logo.jpg");
    setWindowIcon(icon);
    this->setStyleSheet("background-color: white;");

    connect(ui->pushButton_1,&QPushButton::clicked,[&](){
        if(money<10){
            QMessageBox::warning(this,"好穷","买不起了TAT");
            return;
        }
        int cost=QRandomGenerator::global()->bounded(10,qMin(money,30));
        money-=cost;
        hungry+=QRandomGenerator::global()->bounded(25,55);
        if(hungry>100)hungry=100;
        mood+=QRandomGenerator::global()->bounded(1,5);
        if(mood>100)mood=100;
        this->close();
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[&](){
        if(money<3){
            QMessageBox::warning(this,"好穷","买不起了TAT");
            return;
        }
        money-=3;
        hungry+=QRandomGenerator::global()->bounded(20,30);
        if(hungry>100)hungry=100;
        this->close();
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[&](){
        if(money<18){
            QMessageBox::warning(this,"好穷","买不起了TAT");
            return;
        }
        money-=18;
        hungry+=QRandomGenerator::global()->bounded(30,40);
        if(hungry>100)hungry=100;
        this->close();
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[&](){
        if(money<22){
            QMessageBox::warning(this,"好穷","买不起了TAT");
            return;
        }
        money-=22;
        hungry+=QRandomGenerator::global()->bounded(40,50);
        if(hungry>100)hungry=100;
        this->close();
    });
}

galShop::~galShop()
{
    delete ui;
}

void galShop::FoodShop(int& hungry,int& money,int& mood){
    galShop* shop=new galShop(hungry,money,mood);
    shop->exec();
}
