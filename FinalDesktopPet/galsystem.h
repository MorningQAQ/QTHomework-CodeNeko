#ifndef GALSYSTEM_H
#define GALSYSTEM_H

#include <QWidget>
#include <QString>
#include "galshop.h"

namespace Ui {
class GalSystem;
}

class GalSystem : public QWidget
{
    Q_OBJECT

public:
    explicit GalSystem(QWidget *parent = nullptr);
    ~GalSystem();

    int valueMood;
    int valueHungry;
    int valueEnergy;
    int valueMoney;

    int remainTime;

    QString PLAY_WORD[4]={
        "在玩偶猫的海洋中遨游",
        "与又菜又爱玩小队五排中",
        "正在考察人类物种多样性",
        "🎵新的风暴已经出现🎵"
    };
    QString STUDY_WORD[4]={
        "奋斗100天，我要上清华",
        "正在研读《一个桌宠的自我修养》",
        "在桌宠研讨会上作《关于如何让主人多喂饭的报告》",
        "地表最强桌宠，绝赞摸鱼中"
    };
    QString WORK_WORD[4]={
        "很忙，在给草莓镶籽",
        "一刻都没有为996感到悲伤，立刻赶到公司的是：周天的加班",
        "在给其他桌宠改bug",
        "正在为了生计直播带货"
    };

private:
    Ui::GalSystem *ui;
};

#endif // GALSYSTEM_H
