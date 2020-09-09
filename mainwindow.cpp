#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SortitionItem* item = new SortitionItem;
    ui->listWidget->addItem(item);
    item->initWidget(ui->listWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

