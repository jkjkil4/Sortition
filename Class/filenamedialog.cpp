#include "filenamedialog.h"

FileNameDialog::FileNameDialog(QWidget *parent) : QDialog(parent)
{
    QPushButton *btnAccept = new QPushButton("确认");
    connect(btnAccept, SIGNAL(clicked()), this, SLOT(onBtnAccpetClicked()));
    QPushButton *btnCancel = new QPushButton("取消");
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    QHBoxLayout *layBtn = new QHBoxLayout;
    layBtn->addStretch();
    layBtn->addWidget(btnAccept);
    layBtn->addWidget(btnCancel);

    QVBoxLayout *layMain = new QVBoxLayout;
    layMain->addWidget(edit);
    edit->setValidator(new QRegExpValidator(QRegExp("[^\\\\/:*?\"<>]{64}"), this));
    jqSetPointSize(edit, 10);
    layMain->addLayout(layBtn);

    setLayout(layMain);
    setWindowTitle("请输入文件名");
    adjustSize();
    limitSize(this, 250, size().height());
}

QString FileNameDialog::text() {
    return outputText;
}


void FileNameDialog::onBtnAccpetClicked() {
    QString name = edit->text();
    if(!isLegalFileName(name)) {
        QMessageBox::information(this, "提示", "无效文件名");
        return;
    }
    if(QDir().exists("Documents/" + name)) {
        int res = QMessageBox::warning(this, "提示", "\"" + name + "\" 已经存在，要覆盖吗?", QMessageBox::Yes, QMessageBox::No);
        if(res == 1)    //No
            return;
    }
    outputText = name;
    close();
}

void FileNameDialog::onBtnCancelClicked() {
    close();
}
