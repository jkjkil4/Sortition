#ifndef CHOOSEFILEDIALOG_H
#define CHOOSEFILEDIALOG_H

#include <QDialog>
#include <QListWidget>

#include <QHBoxLayout>
#include <QDir>
#include <QTextStream>

class ChooseFileDialog : public QDialog
{
    Q_OBJECT
public:
    ChooseFileDialog(QWidget *parent = nullptr);

    QString text();

private slots:
    void onListWidgetDoubleClicked(QListWidgetItem* item);

private:
    QListWidget *listWidget = new QListWidget;
    QString result;
};

#endif // CHOOSEFILEDIALOG_H
