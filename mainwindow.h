#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <QDebug>

#include "Class/sortitionitemwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //添加元素
    void appendItem();

    //设置文件是否被保存，若saved为false，同时会让状态栏显示出"文件未保存"的字样
    void setFileSavedState(bool saved);

public slots:
    void onListWidgetRowChanged(int row);   //当ListWidget所选行改变时调用的槽
    void onAppend();    //当需要添加元素时调用的槽
    void onRemove();    //当需要移除元素时调用的槽

private:
    Ui::MainWindow *ui;

    //和文件是否保存相关的东西
    bool fileSaved = false;
    QLabel *labShowFileSaved = new QLabel("文件未保存");
};

#endif // MAINWINDOW_H
