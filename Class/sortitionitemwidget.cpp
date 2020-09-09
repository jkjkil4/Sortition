#include "sortitionitemwidget.h"

SortitionItemWidget::SortitionItemWidget()
{
    QHBoxLayout* layMain = new QHBoxLayout;
    layMain->setMargin(0);
    layMain->setSpacing(0);
    layMain->addWidget(lineEdit);
    lineEdit->setPlaceholderText("请输入内容");
    layMain->addWidget(new QLabel(" 权重:"));
    layMain->addWidget(weightEdit);
    weightEdit->setValue(1);
    weightEdit->setMinimum(1);

    setLayout(layMain);
}
