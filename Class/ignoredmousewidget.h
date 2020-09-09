#ifndef IGNOREDMOUSEWIDGET_H
#define IGNOREDMOUSEWIDGET_H

#include <QLineEdit>
#include <QSpinBox>

#include <QMouseEvent>

class LineEdit_IgnoredMouse : public QLineEdit
{
protected:
    void mousePressEvent(QMouseEvent* ev) override {
        QLineEdit::mousePressEvent(ev);
        ev->ignore();
    }
public:
    using QLineEdit::QLineEdit;
};

class SpinBox_IgnoredMouse : public QSpinBox
{
protected:
    void mousePressEvent(QMouseEvent* ev) override {
        QSpinBox::mousePressEvent(ev);
        ev->ignore();
    }
public:
    using QSpinBox::QSpinBox;
};


#endif // IGNOREDMOUSEWIDGET_H
