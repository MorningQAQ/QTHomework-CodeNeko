#include "itemsbox.h"
void itemsbox::save() {
    std::ofstream O("../../item.txt", std::ios::out);
    for (auto i : items) {
        if (i->item->text() != "" && i->ddl_d->text() != "" && i->ddl_m->text() != "" && i->ddl_y->text() != ""&&!i->Del) {
            O << i->item->text().toStdString() << "\n";
            O << i->ddl_y->text().toStdString() << "\n";
            O << i->ddl_m->text().toStdString() << "\n";
            O << i->ddl_d->text().toStdString() << "\n";
            O << i->imp->text().toStdString() << "\n";
            O << i->done << "\n";
            O << i->LT->text().toStdString() << "\n";
            O << i->U->text().toStdString() << "\n";
        }
    }
    //O << "endoffile";
    O.close();
}
void itemsbox::reset(int f, int k) {
    for (auto i : items) delete i;
    items.clear();
    delete add;
    resize(590, 100);
    add = new QPushButton("+", this);
    add->setFixedSize(50,50);
    add->setStyleSheet("QPushButton{background-color:orange;border-radius: 25px;color:white;font-size:18pt;}");//;
    add->move(260, 0);
    add->resize(70, 50);
    add->show();
    show();
    std::ifstream I("../../item.txt", std::ios::in);
    s0=0;s1=0;
    while (1) {
        std::string it, dy, dm, dd, im,don,lt,uu;
        if (!std::getline(I, it)) break;
        std::getline(I, dy);
        std::getline(I, dm);
        std::getline(I, dd);
        std::getline(I, im);
        std::getline(I, don);
        std::getline(I, lt);
        std::getline(I, uu);
        itembox* i = new itembox(this);
        i->item->setText(QString::fromStdString(it));
        i->ddl_y->setText(QString::fromStdString(dy));
        i->ddl_m->setText(QString::fromStdString(dm));
        i->ddl_d->setText(QString::fromStdString(dd));
        i->imp->setText(QString::fromStdString(im));
        i->LT->setText(QString::fromStdString(lt));
        i->U->setText(QString::fromStdString(uu));
        if (don != "1") i->comp->click(),s0++;
        i->comp->click();s1++;
        i->hide();
        i->ri();
        items.push_back(i);
    }
    if(f==3)std::sort(items.begin(), items.end(), cmp3());
    if (f == 2)std::sort(items.begin(), items.end(), cmp2());
    if (f == 1) std::sort(items.begin(), items.end(), cmp1());
    for (auto i : items) if ((1 << i->done) & k) {
            auto y = add->pos().y();
            i->move(0, y);
            i->show();
            add->move(260, y + 100);
            resize(590, size().height() + 100);
        }
    QObject::connect(add, &QPushButton::clicked, this, [&]() {
        auto y = add->pos().y();
        itembox* i = new itembox(this);
        i->move(0, y);
        i->show();
        add->move(260, y + 100);
        resize(590, size().height() + 100);
        items.push_back(i);
    });
}
