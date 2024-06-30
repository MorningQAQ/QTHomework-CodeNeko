#pragma once
#include"itembox.h"
class cmp3
{
public:
    bool operator ()(const itembox* b1, const  itembox* b2) {
        return  b1->imp->text().toInt() > b2->imp->text().toInt();
    }
};

