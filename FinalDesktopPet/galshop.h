#ifndef GALSHOP_H
#define GALSHOP_H

#include <QDialog>

namespace Ui {
class galShop;
}

class galShop : public QDialog
{
    Q_OBJECT

public:
    explicit galShop(int& hungry,int& money,int& mood,QWidget *parent = nullptr);
    ~galShop();

    static void FoodShop(int& hungry,int& money,int& mood);

private:
    Ui::galShop *ui;
};

#endif // GALSHOP_H
