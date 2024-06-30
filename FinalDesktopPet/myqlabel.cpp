#include "myqlabel.h"
void myqlabel::rsetText(QTableWidgetItem* item) {
    if(((myqwitem*)item)->text()!="") this->setText(((myqwitem*)item)->text());
    else this->setText("点击课表查看详情");
}
