#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include <QDialog>
#include<mainwindow.h>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFormLayout>
#include<QLineEdit>
#include<QPushButton>
#include<QComboBox>
#include<QSlider>

namespace Ui {
class AddFileDialog;
}

class AddFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFileDialog(QString file_name,QString dir_path,QDataStream& writeInfoStr,QWidget *parent = nullptr);
    ~AddFileDialog();
    void save();

private:
    Ui::AddFileDialog *ui;
    QDataStream& write_info;
    QString file_name;
    QString type;
    QString subject;
    int priority;
    int frequency = 0;
    QString file_path;
    QLineEdit * name_edit;
    QComboBox * type_box;
    QComboBox * subject_box;
    QSlider * priority_slider;
    QLineEdit * path_edit;
    QPushButton * submit_button;
    QPushButton * cancel_button;
};

#endif // ADDFILEDIALOG_H
