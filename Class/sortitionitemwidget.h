#ifndef SORTITIONITEM_H
#define SORTITIONITEM_H

#include <QLabel>

#include <QWidget>
#include <QHBoxLayout>

#include "ignoredmousewidget.h"

#include <QDebug>

class SortitionItemWidget : public QWidget
{
    Q_OBJECT
public:
    SortitionItemWidget();
    ~SortitionItemWidget() override = default;

    LineEdit_IgnoredMouse* lineEdit = new LineEdit_IgnoredMouse;
    SpinBox_IgnoredMouse* weightEdit = new SpinBox_IgnoredMouse;

signals:
    void changed();

public slots:
    void onEmitChanged();
};

#endif // SORTITIONITEM_H
