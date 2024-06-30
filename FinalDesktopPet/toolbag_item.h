#ifndef TOOLBAG_ITEM_H
#define TOOLBAG_ITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class toolbag_item;
}

class toolbag_item : public QWidget
{
    Q_OBJECT

public:
    explicit toolbag_item(QWidget *parent = nullptr);
    ~toolbag_item();
    void setName();

    QString http;
    QString name;
    int state=0;
    int index;
private:
    Ui::toolbag_item *ui;
};

#endif // TOOLBAG_ITEM_H
