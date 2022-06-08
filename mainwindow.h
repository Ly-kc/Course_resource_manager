#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fileinfo.h>
#include <QFile>
#include <QDir>
#include <QDebug>
#include<addfiledialog.h>
#include<filetree.h>
#include <filetreewindow.h>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include<filterwidget.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FilterWidget;
class FileTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FilterWidget* filter_widget;
    FileTree* file_tree;
    QWidget* central_widget;
};
#endif // MAINWINDOW_H
