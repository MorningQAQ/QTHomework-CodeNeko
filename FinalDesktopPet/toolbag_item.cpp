#include "toolbag_item.h"
#include "ui_toolbag_item.h"

toolbag_item::toolbag_item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toolbag_item)
{
    ui->setupUi(this);
    ui->nameLabel->setText(name);
}

toolbag_item::~toolbag_item()
{
    delete ui;
}

void toolbag_item::setName(){
    ui->nameLabel->setText(name);
}
