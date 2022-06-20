#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include <QDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFormLayout>
#include<QLineEdit>
#include<QPushButton>
#include<QComboBox>
#include<QSlider>
#include<QDebug>
#include<datamanager.h>

CourseFile get_course_file(QString name);

namespace Ui {
class AddFileDialog;
}

class AddFileDialog : public QDialog
{
    Q_OBJECT
    friend CourseFile get_course_file(QString name); //检测到新文件后一条龙
public:
    explicit AddFileDialog(QWidget *parent = nullptr);
    ~AddFileDialog();
    void save();  //获取输入信息
    void set_file(QString name);  //调出窗口
private:
    Ui::AddFileDialog *ui;
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

