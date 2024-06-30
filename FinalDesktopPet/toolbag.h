#ifndef TOOLBAG_H
#define TOOLBAG_H

#include <QWidget>
#include <QVector>
#include <QListWidgetItem>
#include "toolbag_create.h"
#include "toolbag_item.h"

namespace Ui {
class ToolBag;
}

class ToolBag : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBag(QWidget *parent = nullptr);
    ~ToolBag();

    QVector<toolbag_item*> webPointer;
    int webCount=0;

private:
    Ui::ToolBag *ui;
};

#endif // TOOLBAG_H
