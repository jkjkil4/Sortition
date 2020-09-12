#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QRegExp>

//检测一个字符串是否是合法的文件名
inline bool isLegalFileName(const QString& name) {
    if(name.isEmpty())
        return false;
    QRegExp regExp("[\\\\/:*?\"<>]");
    return name.indexOf(regExp) < 0;
}

//对widget的大小进行限定
inline void limitSize(QWidget *widget, int w, int h) {
    widget->setMaximumSize(w, h);
    widget->setMinimumSize(w, h);
}
inline void limitSize(QWidget *widget, QSize size) {
    widget->setMaximumSize(size);
    widget->setMinimumSize(size);
}

inline void limitWidth(QWidget *widget, int w) {
    widget->setMaximumWidth(w);
    widget->setMinimumWidth(w);
}
inline void limitHeight(QWidget *widget, int h) {
    widget->setMaximumHeight(h);
    widget->setMinimumHeight(h);
}

//字体相关
template<typename T>
inline void jqSetPointSize(T *t, int size) {
    QFont font = t->font();
    font.setPointSize(size);
    t->setFont(font);
}

#endif // HEADER_H
