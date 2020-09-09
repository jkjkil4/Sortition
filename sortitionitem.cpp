#include "sortitionitem.h"

SortitionItem::SortitionItem()
{
    QHBoxLayout* layMain = new QHBoxLayout;
    layMain->setMargin(0);
    layMain->setSpacing(0);
    layMain->addWidget(lineEdit);
    lineEdit->setPlaceholderText("请输入内容");
    layMain->addWidget(new QLabel(" 权重:"));
    layMain->addWidget(weightEdit);

    mainWidget->setLayout(layMain);
}

void SortitionItem::initWidget(QListWidget *lw) {
    setSizeHint(QSize(sizeHint().width(), 24));
    lw->setItemWidget(this, mainWidget);
}
