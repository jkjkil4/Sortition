#include "choosefiledialog.h"

ChooseFileDialog::ChooseFileDialog(QWidget *parent) : QDialog(parent)
{
    //布局
    QHBoxLayout *layMain = new QHBoxLayout;
    layMain->addWidget(listWidget);
    setLayout(layMain);
    setWindowTitle("请选择文件");
    adjustSize();
    limitSize(this, size().width(), 450);


    struct FileInfo { QString file; time_t time; };
    //读取文件
    QList<FileInfo> lInfo;
    QDir dir("Documents");
    if(dir.exists()) {
        QStringList list = dir.entryList(QDir::Files);
        for(QString& strFile : list) {
            QFile file("Documents/" + strFile);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                continue;
#ifdef _USE_32BIT_TIME_T
            time_t time = QTextStream(&file).readLine().toLong();
#else
            time_t time = QTextStream(&file).readLine().toLongLong();
#endif
            lInfo.append({strFile, time});
            file.close();
        }
    }
    //排序
    std::sort(lInfo.begin(), lInfo.end(), [](const FileInfo& a, const FileInfo& b) -> bool { return a.time > b.time; });
    //添加元素至listWidget
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListWidgetDoubleClicked(QListWidgetItem*)));
    for(FileInfo& info : lInfo) {
        listWidget->addItem(new QListWidgetItem(info.file));
    }
}

QString ChooseFileDialog::text() {
    return result;
}

void ChooseFileDialog::onListWidgetDoubleClicked(QListWidgetItem* item) {
    result = item->text();
    close();
}
