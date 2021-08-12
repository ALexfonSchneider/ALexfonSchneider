#ifndef SORTINGCLASS_H
#define SORTINGCLASS_H

#include <QMainWindow>
#include "header.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SortingClass; }
QT_END_NAMESPACE

class SortingClass : public QMainWindow
{
    Q_OBJECT
private:
    QFileDialog FileDialog;
    QString str_primalDirectoryPath; //directory path
public:

public:
    SortingClass(QWidget *parent = nullptr);
    ~SortingClass();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SortingClass *ui;
};
#endif // SORTINGCLASS_H
