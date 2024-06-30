#ifndef ROLE_H
#define ROLE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QMovie>
#include <QPalette>
#include <QMediaPlayer>

#include "mypushbutton.h"
#include "toolbag.h"
#include "galsystem.h"
#include "timetable.h"
#include "entry.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Role;
}
QT_END_NAMESPACE

class Role : public QWidget
{
    Q_OBJECT

public:
    Role(QWidget *parent = nullptr);
    ~Role();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);

    void closeEvent(QCloseEvent *event);

    void startAnimation();

private:
    int state = 0;

    bool ingAnimation = false;
    struct GIF{
        int w;
        int h;
        QString Action;
    };
    GIF normal_gif[3];
    GIF fight_gif[3];

    bool is_saying = false;
    struct Voice{
        QString text;
        QString voicePath;
        double time;
    }voice[6];

    QLabel* myRoleLable;

    QPoint lastPos;
    QPoint windowPos;

    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *quitAction;

    QTimer* timer;
    QTimer* mouseTimer;
    QTimer* textTimer;

    bool is_dragging = false;
    int min = 0;
    int max = 119;

    MyPushButton* plusBtn;
    MyPushButton* subBtn;
    MyPushButton* changeBtn;
    MyPushButton* timeTableBtn;
    MyPushButton* toolBtn;
    MyPushButton* ddlBtn;
    MyPushButton* galBtn;

    QLabel* textlabel;

    QMovie* myAnimation;

    ToolBag* myToolBug;

    GalSystem* myGal;

    timetable* myTimeTable;

    entry* myDDL;

    QMediaPlayer* player;

    Ui::Role *ui;

private:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void restoreWindow();
};
#endif // ROLE_H
