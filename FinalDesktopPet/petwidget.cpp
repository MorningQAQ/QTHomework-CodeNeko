#include "petwidget.h"
#include "ui_petwidget.h"
#include "toolbag.h"
#include "galsystem.h"
#include <QPushButton>

PetWidget::PetWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PetWidget)
{
    ui->setupUi(this);
    QPushButton* toolbag_button=new QPushButton;
    toolbag_button->setParent(this);
    toolbag_button->resize(100,100);
    toolbag_button->setText("ToolBag");
    connect(toolbag_button,&QPushButton::clicked,[=](){
        ToolBag * new_bag = new ToolBag;
        new_bag->show();
        this->close();
    });
    QPushButton* gal_button=new QPushButton;
    gal_button->setParent(this);
    gal_button->resize(100,100);
    gal_button->move(200,200);
    gal_button->setText("GalGame");
    connect(gal_button,&QPushButton::clicked,[=](){
        GalSystem * new_gal = new GalSystem;
        new_gal->show();
        this->close();
    });
}

PetWidget::~PetWidget()
{
    delete ui;
}

