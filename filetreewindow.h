#ifndef FILETREEWINDOW_H
#define FILETREEWINDOW_H

#include <QWidget>

namespace Ui {
class FileTreeWindow;
}

class FileTreeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FileTreeWindow(QString file_name,QString dir_path,QDataStream& writeInfoStr,QWidget *parent = nullptr);
    ~FileTreeWindow();

private:
    Ui::FileTreeWindow *ui;
};

#endif // FILETREEWINDOW_H
