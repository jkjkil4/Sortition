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

    //快捷键
    ui->actNewFile->setShortcut(QKeySequence("Ctrl+N"));
    ui->actOpenFile->setShortcut(QKeySequence("Ctrl+O"));
    ui->actSaveFile->setShortcut(QKeySequence("Ctrl+S"));

    //信号与槽
    connect(ui->actAboutQt, &QAction::triggered, [=]{ QMessageBox::aboutQt(this); });
    //
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onListWidgetRowChanged(int)));
    //
    connect(ui->actAppendItem, SIGNAL(triggered()), this, SLOT(onAppend()));
    connect(ui->actRemoveItem, SIGNAL(triggered()), this, SLOT(onRemove()));
    //
    connect(ui->actNewFile, SIGNAL(triggered()), this, SLOT(onNewFile()));
    connect(ui->actOpenFile, SIGNAL(triggered()), this, SLOT(onLoadFile()));
    connect(ui->actSaveFile, SIGNAL(triggered()), this, SLOT(onSaveFile()));
    connect(ui->actSaveAnother, SIGNAL(triggered()), this, SLOT(onSaveAnother()));
    //
    connect(ui->btnSortition, SIGNAL(clicked()), this, SLOT(onSortition()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *ev) {
    if(!fileSaved && !checkSaveFile())
        ev->ignore();
}


void MainWindow::appendItem(const QString &text, int weight) {
    QListWidgetItem *item = new QListWidgetItem;    //new一个QListWidgetItem的对象
    item->setSizeHint(QSize(item->sizeHint().width(), 24)); //设置item的高度
    ui->listWidget->addItem(item);  //向ListWidget中添加该item

    SortitionItemWidget* widget = new SortitionItemWidget;  //new一个与item对应的widget
    widget->lineEdit->setText(text);
    widget->weightEdit->setValue(weight);
    ui->listWidget->setItemWidget(item, widget);    //设置item和widget的对应关系
    connect(widget, &SortitionItemWidget::changed, [=]{ setFileSavedState(false); });   //绑定信号与槽
}


void MainWindow::checkAndMkpath(const QString &path) {
    QDir dir;
    if(!dir.exists(path))
        dir.mkpath(path);
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

void MainWindow::onSortition() {
    int count = ui->listWidget->count();
    if(count == 0) {
        QMessageBox::information(this, "提示", "没有可抽取的元素");
        return;
    }

    struct Element { QString text; int weight; };
    QList<Element> lElement;

    int totalWeight = 0;
    for(int i = 0; i < count; i++) {
        SortitionItemWidget* widget = (SortitionItemWidget*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        lElement.append({widget->lineEdit->text(), widget->weightEdit->value()});
        totalWeight += widget->weightEdit->value();
    }

    int random = rand() % totalWeight;
    for(Element& element : lElement) {
        random -= element.weight;
        if(random < 0) {
            QMessageBox::information(this, "抽取结果", "结果: " + element.text);
            break;
        }
    }

    if(random >= 0)
        QMessageBox::critical(this, "警告", "在进行抽取时发生了未知的错误");
}


bool MainWindow::load(const QString &name) {
    ui->listWidget->clear();

    QFile file("Documents/" + name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "警告", "打开项目 \"" + name + "\" 失败");
        return false;
    }
    QTextStream in(&file);
    in.readLine();  //跳过第一行(是time_t)
    while(!in.atEnd()) {    //读取剩下的行
        QString line = in.readLine();
        int indexOfSpace = line.indexOf(' ');
        if(indexOfSpace == -1) {
            appendItem(line);
        } else {
            int weight = line.left(indexOfSpace).toInt();
            if(weight <= 0) weight = 1;
            QString strText = line.right(line.length() - indexOfSpace - 1);
            appendItem(strText, weight);
        }
    }
    file.close();

    srand((uint)time(nullptr));

    return true;
}

bool MainWindow::save(const QString &name) {
    checkAndMkpath("Documents");

    QFile file("Documents/" + name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "警告", "保存项目 \"" + name + "\" 失败");
        return false;
    }
    QTextStream out(&file);
    //输出time_t
    out << time(nullptr);
    //输出所有的元素
    int count = ui->listWidget->count();
    for(int i = 0; i < count; i++) {
        SortitionItemWidget *widget = (SortitionItemWidget*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        out << '\n' << widget->weightEdit->value() << ' ' << widget->lineEdit->text();
    }
    file.close();
    return true;
}

bool MainWindow::checkSaveFile() {
    if(fileSaved)
        return true;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("提示");
    msgBox.setText(fileName.isEmpty() ? "是否保存该文件?" : "是否将更改保存到 \"" + fileName + "\" 中?");
    msgBox.addButton("是(&Y)", QMessageBox::ButtonRole::YesRole);
    msgBox.addButton("否(&N)", QMessageBox::ButtonRole::NoRole);
    msgBox.addButton("取消", QMessageBox::ButtonRole::NoRole);
    msgBox.setIcon(QMessageBox::Icon::Warning);

    int res = msgBox.exec();
    //取消
    if(res == 2)
        return false;
    //是
    if(res == 0) {
        QString name = fileName;
        if(name.isEmpty()) {
            FileNameDialog dialog;
            dialog.exec();
            name = dialog.text();
        }
        if(name.isEmpty())
            return false;
        save(name);
        fileName = name;
    }

    return true;
}


void MainWindow::onNewFile() {
    if(!checkSaveFile())
        return;
    ui->listWidget->clear();
    fileName = "";
    setFileSavedState(true);
}

void MainWindow::onLoadFile() {
    if(!checkSaveFile())
        return;

    ChooseFileDialog dialog;
    dialog.exec();
    QString result = dialog.text();
    if(result.isEmpty())
        return;

    if(!load(result))
        return;
    fileName = result;

    setFileSavedState(true);
}

void MainWindow::onSaveFile() {
    QString name = fileName;
    if(name.isEmpty()) {
        FileNameDialog dialog;
        dialog.exec();
        name = dialog.text();
    }
    if(name.isEmpty())
        return;

    if(!save(name))
        return;

    setFileSavedState(true);
}

void MainWindow::onSaveAnother() {
    FileNameDialog dialog;
    dialog.exec();
    QString result = dialog.text();
    if(result.isEmpty())
        return;

    if(!save(result))
        return;
    fileName = result;

    setFileSavedState(true);
}

