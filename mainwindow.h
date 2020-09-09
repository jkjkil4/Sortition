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

    void appendItem();

    void setFileSavedState(bool saved);

public slots:
    void onListWidgetRowChanged(int row);
    void onAppend();
    void onRemove();

private:
    Ui::MainWindow *ui;

    bool fileSaved = false;
    QLabel *labShowFileSaved = new QLabel("文件未保存");
};

#endif // MAINWINDOW_H
