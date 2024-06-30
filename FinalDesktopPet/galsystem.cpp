#include "galsystem.h"
#include "ui_galsystem.h"
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

GalSystem::GalSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalSystem)
{
    ui->setupUi(this);
    setWindowTitle("养成系统");

    this->resize(550,200);
    this->setStyleSheet("background-color: white;");
    ui->infoTable->setStyleSheet("background-color: white;");

    ui->infoTable->setItem(0,0,new QTableWidgetItem("心情"));
    ui->infoTable->setItem(0,1,new QTableWidgetItem(QString::number(100)));
    ui->infoTable->setItem(1,0,new QTableWidgetItem("精力"));
    ui->infoTable->setItem(1,1,new QTableWidgetItem(QString::number(100)));
    ui->infoTable->setItem(2,0,new QTableWidgetItem("饥饿度"));
    ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(100)));
    ui->infoTable->setItem(3,0,new QTableWidgetItem("零花钱"));
    ui->infoTable->setItem(3,1,new QTableWidgetItem(QString::number(0)));
    ui->infoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->infoTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->label->setText("空闲中。。。");

    QTimer* timeCounter=new QTimer(this);
    timeCounter->setInterval(1000);

    if(QFile::exists("gal_save.txt")){
        QFile saves("gal_save.txt");
        if(saves.open(QIODevice::ReadOnly)){
            QTextStream file(&saves);
            file>>valueMood>>valueEnergy>>valueHungry>>valueMoney;
            ui->infoTable->setItem(0,1,new QTableWidgetItem(QString::number(valueMood)));
            ui->infoTable->setItem(1,1,new QTableWidgetItem(QString::number(valueEnergy)));
            ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(valueHungry)));
            ui->infoTable->setItem(3,1,new QTableWidgetItem(QString::number(valueMoney)));
        }
        saves.close();
    }
    else{
        QFile saves("gal_save.txt");
        valueMood=100;
        valueEnergy=100;
        valueHungry=100;
        valueMoney=0;
    }
    connect(ui->buttonEat,&QPushButton::clicked,[=](){
        galShop::FoodShop(valueHungry,valueMoney,valueMood);
        ui->infoTable->setItem(0,1,new QTableWidgetItem(QString::number(valueMood)));
        ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(valueHungry)));
        ui->infoTable->setItem(3,1,new QTableWidgetItem(QString::number(valueMoney)));
        QFile saves("gal_save.txt");
        if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
            QTextStream file(&saves);
            file<<valueMood<<endl;
            file<<valueEnergy<<endl;
            file<<valueHungry<<endl;
            file<<valueMoney<<endl;
        }
        saves.close();
        ui->label->setText("好饱。。。");
    });
    connect(ui->buttonPlay,&QPushButton::clicked,[=](){
        disconnect(timeCounter,&QTimer::timeout,0,0);
        remainTime=60;
        QString s=PLAY_WORD[QRandomGenerator::global()->bounded(0,4)];
        ui->label->setText(s+QString("，剩余")+QString::number(remainTime)+QString("s"));
        connect(timeCounter,&QTimer::timeout,[=](){
            remainTime--;
            if(remainTime){
                ui->label->setText(s+QString("，剩余")+QString::number(remainTime)+QString("s"));
            }
            else{
                int changeMood=QRandomGenerator::global()->bounded(20,60);
                valueMood+=changeMood;
                if(valueMood>100)valueMood=100;
                int changeEnergy=QRandomGenerator::global()->bounded(10,30);
                valueEnergy-=changeEnergy;
                if(valueEnergy<0)valueEnergy=0;
                int changeHungry=QRandomGenerator::global()->bounded(10,30);
                valueHungry-=changeHungry;
                if(valueHungry<0)valueHungry=0;
                ui->infoTable->setItem(0,1,new QTableWidgetItem(QString::number(valueMood)));
                ui->infoTable->setItem(1,1,new QTableWidgetItem(QString::number(valueEnergy)));
                ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(valueHungry)));
                QFile saves("gal_save.txt");
                if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                    QTextStream file(&saves);
                    file<<valueMood<<endl;
                    file<<valueEnergy<<endl;
                    file<<valueHungry<<endl;
                    file<<valueMoney<<endl;
                }
                saves.close();
                ui->label->setText(QString("玩耍结束，心情增加%1点，体力减少%2点，饥饿度减少%3点")
                                   .arg(QString::number(changeMood)).arg(QString::number(changeEnergy))
                                   .arg(QString::number(changeHungry)));
                timeCounter->stop();
            }
        });
        timeCounter->start();
    });
    connect(ui->buttonStudy,&QPushButton::clicked,[=](){
        disconnect(timeCounter,&QTimer::timeout,0,0);
        remainTime=300;
        QString s=STUDY_WORD[QRandomGenerator::global()->bounded(0,4)];
        ui->label->setText(s+QString("，剩余")+QString::number(remainTime)+QString("s"));
        connect(timeCounter,&QTimer::timeout,[=](){
            remainTime--;
            if(remainTime){
                ui->label->setText(s+QString("，剩余")+QString::number(remainTime)+QString("s"));
            }
            else{
                int changeMood=QRandomGenerator::global()->bounded(20,30);
                valueMood-=changeMood;
                if(valueMood<0)valueMood=0;
                int changeEnergy=QRandomGenerator::global()->bounded(20,30);
                valueEnergy-=changeEnergy;
                if(valueEnergy<0)valueEnergy=0;
                int changeHungry=QRandomGenerator::global()->bounded(20,30);
                valueHungry-=changeHungry;
                if(valueHungry<0)valueHungry=0;
                ui->infoTable->setItem(0,1,new QTableWidgetItem(QString::number(valueMood)));
                ui->infoTable->setItem(1,1,new QTableWidgetItem(QString::number(valueEnergy)));
                ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(valueHungry)));
                QFile saves("gal_save.txt");
                if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                    QTextStream file(&saves);
                    file<<valueMood<<endl;
                    file<<valueEnergy<<endl;
                    file<<valueHungry<<endl;
                    file<<valueMoney<<endl;
                }
                saves.close();
                ui->label->setText(QString("摸鱼结束，心情减少%1点，体力减少%2点，饥饿度减少%3点")
                                   .arg(QString::number(changeMood)).arg(QString::number(changeEnergy))
                                   .arg(QString::number(changeHungry)));
                timeCounter->stop();
            }
        });
        timeCounter->start();
    });
    connect(ui->buttonWork,&QPushButton::clicked,[=](){
        disconnect(timeCounter,&QTimer::timeout,0,0);
        remainTime=600;
        QString s=WORK_WORD[QRandomGenerator::global()->bounded(0,4)];
        ui->label->setText(s+QString("，剩余")+QString::number(remainTime)+QString("s"));
        connect(timeCounter,&QTimer::timeout,[=](){
            remainTime--;
            if(remainTime){
                ui->label->setText(s+QString("，剩余")+QString::number(remainTime)+QString("s"));
            }
            else{
                int changeMood=QRandomGenerator::global()->bounded(20,30);
                valueMood-=changeMood;
                if(valueMood<0)valueMood=0;
                int changeEnergy=QRandomGenerator::global()->bounded(20,30);
                valueEnergy-=changeEnergy;
                if(valueEnergy<0)valueEnergy=0;
                int changeHungry=QRandomGenerator::global()->bounded(20,30);
                valueHungry-=changeHungry;
                if(valueHungry<0)valueHungry=0;
                int changeMoney=QRandomGenerator::global()->bounded(20,30);
                valueMoney+=changeMoney;
                ui->infoTable->setItem(0,1,new QTableWidgetItem(QString::number(valueMood)));
                ui->infoTable->setItem(1,1,new QTableWidgetItem(QString::number(valueEnergy)));
                ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(valueHungry)));
                ui->infoTable->setItem(3,1,new QTableWidgetItem(QString::number(valueMoney)));
                QFile saves("gal_save.txt");
                if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                    QTextStream file(&saves);
                    file<<valueMood<<endl;
                    file<<valueEnergy<<endl;
                    file<<valueHungry<<endl;
                    file<<valueMoney<<endl;
                }
                saves.close();
                ui->label->setText(QString("下班！心情减少%1点，体力减少%2点，饥饿度减少%3点，零花钱增加%4点")
                                   .arg(QString::number(changeMood)).arg(QString::number(changeEnergy))
                                   .arg(QString::number(changeHungry)).arg(QString::number(changeMoney)));
                timeCounter->stop();
            }
        });
        timeCounter->start();
    });
    connect(ui->buttonSleep,&QPushButton::clicked,[=](){
        disconnect(timeCounter,&QTimer::timeout,0,0);
        remainTime=1800;
        ui->label->setText(QString("晚安，玛卡巴卡，剩余%1s").arg(QString::number(remainTime)));
        connect(timeCounter,&QTimer::timeout,[=](){
            remainTime--;
            if(remainTime){
                ui->label->setText(QString("晚安，玛卡巴卡，剩余%1s").arg(QString::number(remainTime)));
            }
            else{
                int changeEnergy=QRandomGenerator::global()->bounded(20,30);
                valueEnergy+=changeEnergy;
                if(valueEnergy>100)valueEnergy=100;
                int changeHungry=QRandomGenerator::global()->bounded(20,30);
                valueHungry-=changeHungry;
                if(valueHungry<0)valueHungry=0;
                ui->infoTable->setItem(1,1,new QTableWidgetItem(QString::number(valueEnergy)));
                ui->infoTable->setItem(2,1,new QTableWidgetItem(QString::number(valueHungry)));
                QFile saves("gal_save.txt");
                if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                    QTextStream file(&saves);
                    file<<valueMood<<endl;
                    file<<valueEnergy<<endl;
                    file<<valueHungry<<endl;
                    file<<valueMoney<<endl;
                }
                saves.close();
                ui->label->setText(QString("早上好。。体力恢复%1点，饥饿度减少%2点")
                                   .arg(QString::number(changeEnergy)).arg(QString::number(changeHungry)));
                timeCounter->stop();
            }
        });
        timeCounter->start();
    });

    ui->buttonEat->setStyleSheet( "*{color:white;background-color:rgb(14 , 150 , 254);border: 1px solid rgb(11 , 137 , 234);} "
                                  ":hover{color:white;background-color:rgb(44 , 137 , 255);border: 1px solid rgb(11 , 137 , 234);}"
                                  ":pressed{color:white;background-color:rgb(14 , 135 , 228);border: 1px solid rgb(12 , 138 , 235);padding-left:3px;padding-top:3px;}");
    ui->buttonPlay->setStyleSheet( "*{color:white;background-color:rgb(14 , 150 , 254);border: 1px solid rgb(11 , 137 , 234);} "
                                  ":hover{color:white;background-color:rgb(44 , 137 , 255);border: 1px solid rgb(11 , 137 , 234);}"
                                  ":pressed{color:white;background-color:rgb(14 , 135 , 228);border: 1px solid rgb(12 , 138 , 235);padding-left:3px;padding-top:3px;}");
    ui->buttonWork->setStyleSheet( "*{color:white;background-color:rgb(14 , 150 , 254);border: 1px solid rgb(11 , 137 , 234);} "
                                  ":hover{color:white;background-color:rgb(44 , 137 , 255);border: 1px solid rgb(11 , 137 , 234);}"
                                  ":pressed{color:white;background-color:rgb(14 , 135 , 228);border: 1px solid rgb(12 , 138 , 235);padding-left:3px;padding-top:3px;}");
    ui->buttonStudy->setStyleSheet( "*{color:white;background-color:rgb(14 , 150 , 254);border: 1px solid rgb(11 , 137 , 234);} "
                                  ":hover{color:white;background-color:rgb(44 , 137 , 255);border: 1px solid rgb(11 , 137 , 234);}"
                                  ":pressed{color:white;background-color:rgb(14 , 135 , 228);border: 1px solid rgb(12 , 138 , 235);padding-left:3px;padding-top:3px;}");
    ui->buttonSleep->setStyleSheet( "*{color:white;background-color:rgb(14 , 150 , 254);border: 1px solid rgb(11 , 137 , 234);} "
                                  ":hover{color:white;background-color:rgb(44 , 137 , 255);border: 1px solid rgb(11 , 137 , 234);}"
                                  ":pressed{color:white;background-color:rgb(14 , 135 , 228);border: 1px solid rgb(12 , 138 , 235);padding-left:3px;padding-top:3px;}");
}

GalSystem::~GalSystem()
{
    delete ui;
}
