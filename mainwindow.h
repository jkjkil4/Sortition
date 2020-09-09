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

public slots:
    void onListWidgetRowChanged(int row);
    void onAppend();
    void onRemove();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
