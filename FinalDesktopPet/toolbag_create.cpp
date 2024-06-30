#include "toolbag_create.h"
#include "ui_toolbag_create.h"
#include <QLineEdit>
#include <QPushButton>

ToolBag_create::ToolBag_create(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolBag_create)
{
    ui->setupUi(this);
    setWindowTitle("页面");
    this->setStyleSheet("background-color: white;");
}

ToolBag_create::~ToolBag_create()
{
    delete ui;
}

toolbag_item* ToolBag_create::create(){
    toolbag_item* temp_web=new toolbag_item;
    ToolBag_create* createWidget = new ToolBag_create;
    connect(createWidget->ui->yesButton,&QPushButton::clicked,[&](){
        temp_web->name=createWidget->ui->nameLine->text();
        temp_web->http=createWidget->ui->httpLine->text();
        temp_web->setName();
        temp_web->state=1;
        createWidget->close();
    });
    connect(createWidget->ui->noButton,&QPushButton::clicked,[&](){
        temp_web->http = "-1";
        temp_web->name = "-1";
        createWidget->close();
    });
    createWidget->exec();
    return temp_web;
}
void ToolBag_create::edit(toolbag_item* origin){
    ToolBag_create* createWidget = new ToolBag_create;
    createWidget->ui->nameLine->setText(origin->name);
    createWidget->ui->httpLine->setText(origin->http);
    connect(createWidget->ui->yesButton,&QPushButton::clicked,[&](){
        origin->name=createWidget->ui->nameLine->text();
        origin->http=createWidget->ui->httpLine->text();
        origin->setName();
        createWidget->close();
    });
    connect(createWidget->ui->noButton,&QPushButton::clicked,[&](){
        createWidget->close();
    });
    createWidget->exec();
}
