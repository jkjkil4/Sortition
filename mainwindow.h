#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDialog>

#include <QRegExpValidator>
#include <QCloseEvent>
#include <QProcess>

#include <QDebug>

#include "Class/sortitionitemwidget.h"
#include "Class/choosefiledialog.h"
#include "Class/filenamedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *ev) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    //添加元素
    void appendItem(const QString& text = "", int weight = 1);

    //检查并创建目录
    void checkAndMkpath(const QString& path);

    //设置文件是否被保存，若saved为false，同时会让状态栏显示出"文件未保存"的字样
    void setFileSavedState(bool saved);
    //检查能否继续和文件有关的操作，调用后将会弹出一个确认窗口，若返回值为false，则用户取消了操作
    bool checkSaveFile();
    //读取
    bool load(const QString& name);
    //保存
    bool save(const QString& name);

private slots:
    void onListWidgetRowChanged(int row);   //当ListWidget所选行改变时调用的槽

    void onAppend();    //当需要添加元素时调用的槽
    void onRemove();    //当需要移除元素时调用的槽

    void onNewFile();
    void onLoadFile();
    void onSaveFile();
    void onSaveAnother();

    void onSortition();

private:
    Ui::MainWindow *ui;

    //和文件是否保存相关的东西
    QString fileName;
    bool fileSaved = true;
    QLabel *labShowFileSaved = new QLabel("文件未保存");
};

#endif // MAINWINDOW_H
