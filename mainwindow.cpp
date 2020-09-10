#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labShowFileSaved->setStyleSheet("color:rgb(220, 50, 50)");
    labShowFileSaved->setVisible(false);
    ui->statusBar->addPermanentWidget(labShowFileSaved);

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
    SortitionItemWidget* widget = new SortitionItemWidget;
    ui->listWidget->setItemWidget(item, widget);
    connect(widget, &SortitionItemWidget::changed, [=]{ setFileSavedState(false); });
}

void MainWindow::setFileSavedState(bool saved) {
    fileSaved = saved;
    labShowFileSaved->setVisible(!saved);
}


void MainWindow::onListWidgetRowChanged(int row) {
    ui->actRemoveItem->setEnabled(row >= 0);
}

void MainWindow::onAppend() {
    appendItem();
    setFileSavedState(false);
}

void MainWindow::onRemove() {
    int row = ui->listWidget->currentRow();
    if(row >= 0) {
        QListWidgetItem *item = ui->listWidget->takeItem(row);
        delete item;
        setFileSavedState(false);
    }
}

