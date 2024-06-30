#ifndef PETWIDGET_H
#define PETWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PetWidget; }
QT_END_NAMESPACE

class PetWidget : public QWidget
{
    Q_OBJECT

public:
    PetWidget(QWidget *parent = nullptr);
    ~PetWidget();

private:
    Ui::PetWidget *ui;
};
#endif // PETWIDGET_H
