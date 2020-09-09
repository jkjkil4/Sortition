#ifndef SORTITIONITEM_H
#define SORTITIONITEM_H

#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

#include <QListWidget>
#include <QHBoxLayout>

class SortitionItem : public QListWidgetItem
{
public:
    SortitionItem();

    void initWidget(QListWidget* lw);

    QWidget* mainWidget = new QWidget;

    QLineEdit* lineEdit = new QLineEdit;
    QSpinBox* weightEdit = new QSpinBox;
};

#endif // SORTITIONITEM_H
