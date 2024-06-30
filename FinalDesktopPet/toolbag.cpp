#include "toolbag.h"
#include "ui_toolbag.h"
#include <QPushButton>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QScroller>
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>

ToolBag::ToolBag(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBag)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");


    setWindowTitle(QString("工具包"));
    QIcon icon(":/logo.jpg");
    setWindowIcon(icon);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //QPushButton* closeBtn= new QPushButton("✕",this);
    //closeBtn->resize(35,35);
    //closeBtn->move(605,0);
    //connect(closeBtn,&QPushButton::clicked,[=](){
        //this->close();
    //});

    ui->webList->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(ui->webList,QScroller::LeftMouseButtonGesture);

    connect(ui->createButton,&QPushButton::clicked,[=](){
        toolbag_item* temp_web = ToolBag_create::create();
        if(temp_web->state==0){
            delete temp_web;
            return;
        }
        QListWidgetItem* pItem = new QListWidgetItem;
        ui->webList->addItem(pItem);
        pItem->setSizeHint(QSize(60,50));
        ui->webList->setItemWidget(pItem,temp_web);
        ui->webList->setCurrentItem(pItem);
        QFile saves("toolbag_save.txt");
        if(saves.open(QIODevice::Append)){
            QTextStream file(&saves);
            file<<temp_web->name<<endl;
            file<<temp_web->http<<endl;
        }
        saves.close();
        webPointer.push_back(temp_web);
        temp_web->index=webCount;
        webCount++;
    });
    connect(ui->editButton,&QPushButton::clicked,[=](){
        QListWidgetItem* pItem = ui->webList->currentItem();
        if(pItem==NULL)return;
        ToolBag_create::edit(dynamic_cast<toolbag_item*>(ui->webList->itemWidget(pItem)));
        ui->webList->setCurrentItem(pItem);
        QFile saves("toolbag_save.txt");
        if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
            QTextStream file(&saves);
            for(toolbag_item* temp_web:webPointer){
                file<<temp_web->name<<endl;
                file<<temp_web->http<<endl;
            }
        }
        saves.close();
    });
    connect(ui->deleteButton,&QPushButton::clicked,[=](){
        QListWidgetItem* pItem = ui->webList->currentItem();
        if(pItem==NULL)return;
        if(QMessageBox::question(this,"警告","您确定要删除吗")==QMessageBox::Yes){
            toolbag_item* temp_web= dynamic_cast<toolbag_item*>(ui->webList->itemWidget(pItem));
            int k=temp_web->index;
            for(int i=k+1;i<webCount;i++){
                webPointer[i]->index--;
            }
            webPointer.erase(webPointer.begin()+k);
            webCount--;
            ui->webList->removeItemWidget(pItem);
            delete pItem;
            QFile saves("toolbag_save.txt");
            if(saves.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                QTextStream file(&saves);
                for(toolbag_item* temp_web:webPointer){
                    file<<temp_web->name<<endl;
                    file<<temp_web->http<<endl;
                }
            }
            saves.close();
        }
    });
    connect(ui->openButton,&QPushButton::clicked,[=](){
        QListWidgetItem* pItem = ui->webList->currentItem();
        if(pItem==NULL)return;
        QDesktopServices::openUrl(QUrl(dynamic_cast<toolbag_item*>(ui->webList->itemWidget(pItem))->http));
    });

    QFile saves("toolbag_save.txt");
    if(saves.open(QIODevice::ReadOnly)){
        QTextStream file(&saves);
        while(!file.atEnd()){
            toolbag_item* temp_web=new toolbag_item;
            temp_web->name=file.readLine();
            temp_web->http=file.readLine();
            temp_web->setName();
            QListWidgetItem* pItem = new QListWidgetItem;
            ui->webList->addItem(pItem);
            pItem->setSizeHint(QSize(60,50));
            ui->webList->setItemWidget(pItem,temp_web);
            webPointer.push_back(temp_web);
            temp_web->index=webCount;
            webCount++;
        }
    }
    saves.close();

    ui->createButton->setStyleSheet( "*{border-image: url(:/icon/res/icons8-add-new-50.png);} :hover{ border-image: url(:/icon/res/add_select.png);}"
                                     ":pressed{ border-image: url(:/icon/res/add_float.png);}");
    ui->editButton->setStyleSheet( "*{border-image: url(:/icon/res/icons8-edit-50.png);} :hover{ border-image: url(:/icon/res/edit_select.png);}"
                                     ":pressed{ border-image: url(:/icon/res/edit_float.png);}");
    ui->deleteButton->setStyleSheet( "*{border-image: url(:/icon/res/icons8-delete-50.png);} :hover{ border-image: url(:/icon/res/delete_select.png);}"
                                     ":pressed{ border-image: url(:/icon/res/delete_float.png);}");
    ui->openButton->setStyleSheet( "*{border-image: url(:/icon/res/icons8-open-64.png);} :hover{ border-image: url(:/icon/res/open_select.png);}"
                                     ":pressed{ border-image: url(:/icon/res/open_float.png);}");
}

ToolBag::~ToolBag()
{
    delete ui;
}
