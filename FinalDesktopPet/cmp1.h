#pragma once
#include"itembox.h"
class cmp1
{
public:
    bool operator ()(const itembox* b1, const  itembox* b2) {
        return  b1->LT->text().toStdString() > b2->LT->text().toStdString();
    }
};


