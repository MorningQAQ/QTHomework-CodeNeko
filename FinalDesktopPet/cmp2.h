#pragma once
#include"itembox.h"
class cmp2
{
public:
    bool operator ()(const itembox* b1, const  itembox* b2) {
        if(b1->ddl_y->text().toInt() ^ b2->ddl_y->text().toInt()) return  b1->ddl_y->text().toInt() < b2->ddl_y->text().toInt();
        if (b1->ddl_m->text().toInt() ^ b2->ddl_m->text().toInt()) return  b1->ddl_m->text().toInt() < b2->ddl_m->text().toInt();
        return  b1->ddl_d->text().toInt() < b2->ddl_d->text().toInt();
    }
};

