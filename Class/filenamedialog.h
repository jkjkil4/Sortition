#ifndef FILENAMEDIALOG_H
#define FILENAMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QRegExpValidator>

#include "header.h"

class FileNameDialog : public QDialog
{
    Q_OBJECT
public:
    FileNameDialog(QWidget *parent = nullptr);

    QString text();

private slots:
    void onBtnAccpetClicked();
    void onBtnCancelClicked();

private:
    QLineEdit *edit = new QLineEdit;
    QString outputText;
};

#endif // FILENAMEDIALOG_H
