#ifndef HEADER_H
#define HEADER_H

#include <QRegExp>
#include <QString>


//检测一个字符串是否是合法的文件名
inline bool isLegalFileName(const QString& name) {
    if(name.isEmpty())
        return false;
    QRegExp regExp("[\\\\/:*?\"<>]");
    return name.indexOf(regExp) < 0;
}

#endif // HEADER_H
