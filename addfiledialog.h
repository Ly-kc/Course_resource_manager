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
#include<datamanager.h>
#include<QDebug>

CourseFile get_course_file(QString name);

namespace Ui {
class AddFileDialog;
}

class AddFileDialog : public QDialog
{
    Q_OBJECT
    friend CourseFile get_course_file(QString name);
public:
    explicit AddFileDialog(QWidget *parent = nullptr);
    ~AddFileDialog();
    void save();
    void set_file(QString name);
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

