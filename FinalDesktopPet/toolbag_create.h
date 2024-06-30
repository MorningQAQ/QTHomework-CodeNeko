#ifndef TOOLBAG_CREATE_H
#define TOOLBAG_CREATE_H

#include <QDialog>
#include <QString>
#include "toolbag_item.h"

namespace Ui {
class ToolBag_create;
}

class ToolBag_create : public QDialog
{
    Q_OBJECT

public:
    explicit ToolBag_create(QWidget *parent = nullptr);
    ~ToolBag_create();
    static toolbag_item* create();
    static void edit(toolbag_item* origin);

private:
    Ui::ToolBag_create *ui;
};

#endif // TOOLBAG_CREATE_H
