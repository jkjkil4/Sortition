#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //信号与槽
    connect(ui->actAboutQt, &QAction::triggered, [=]{ QMessageBox::aboutQt(this); });
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onListWidgetRowChanged(int)));
    connect(ui->actAppendItem, SIGNAL(triggered()), this, SLOT(onAppend()));
    connect(ui->actRemoveItem, SIGNAL(triggered()), this, SLOT(onRemove()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::appendItem() {
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(item->sizeHint().width(), 24));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, new SortitionItemWidget);
}


void MainWindow::onListWidgetRowChanged(int row) {
    ui->actRemoveItem->setEnabled(row >= 0);
}

void MainWindow::onAppend() {
    appendItem();
}

void MainWindow::onRemove() {
    int row = ui->listWidget->currentRow();
    if(row >= 0) {
        QListWidgetItem *item = ui->listWidget->takeItem(row);
        delete item;
    }
}

