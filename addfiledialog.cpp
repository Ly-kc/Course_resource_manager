#include "addfiledialog.h"
#include "ui_addfiledialog.h"

AddFileDialog::AddFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFileDialog)
{
   // ui->setupUi(this);
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout 和 QHBoxLayout
     * QFormLayout 中放置多个单行输入框
     * QHBoxLayout 中放置两个按钮
    */

//    setWindowIcon(QIcon(":/logo.ico"));
    setWindowFlags(Qt::Dialog);
    setWindowTitle("set new file information");
    QVBoxLayout * VBox = new QVBoxLayout;
    QFormLayout *FormLayout = new QFormLayout;

    name_edit = new QLineEdit;
//    path_edit = new QLineEdit;
//    path_edit->setPlaceholderText(file_path);
    type_box = new QComboBox;
    subject_box = new QComboBox;
    QStringList type_list;
    QStringList subject_list;
    subject_list << "algebra"<<"analysis"<<"programming"<<"AI"<<"watering"<<"eating"<<"add new";
    type_list<<"ppt"<<"notes"<<"homework"<<"project"<<"watering"<<"eating";
    type_box->addItems(type_list);
    subject_box->addItems(subject_list);
    priority_slider = new QSlider;
    priority_slider->setMaximum(3);
    priority_slider->setPageStep(1);
    priority_slider->setOrientation(Qt::Horizontal);
    FormLayout->addRow("name:",name_edit);
    FormLayout->addRow("subject:",subject_box);
    FormLayout->addRow("type:",type_box);
    FormLayout->addRow("priority:",priority_slider);
    FormLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    QHBoxLayout * HBox = new QHBoxLayout;
    submit_button = new QPushButton("submit");
    cancel_button = new QPushButton("cancel");
    HBox->addWidget(submit_button);
    HBox->addWidget(cancel_button);

    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);
    //点击提交按钮时，存储信息
    QObject::connect(submit_button,&QPushButton::clicked,this,&AddFileDialog::save);
    //点击取消按钮时，关闭添加学生信息窗口
    QObject::connect(cancel_button,&QPushButton::clicked,this,&AddFileDialog::close);
}

void AddFileDialog::set_file(QString name)
{
    name_edit->setPlaceholderText(name);
    file_name = name;
    this->show();
//    QEventLoop loop;
//    connect(this, AddFileDialog::close, &loop, QEventLoop::quit);
//    loop.exec(QEventLoop::ExcludeUserInputEvents);
}

void AddFileDialog::save()
{
    if(name_edit->text()!="") file_name = name_edit->text();
    type = type_box->currentText();
    subject = subject_box->currentText();
    priority = priority_slider->value();
    this->close();
}

CourseFile get_course_file(QString name)
{
     AddFileDialog dia;
     dia.set_file(name);
     dia.exec();
     CourseFile cf(dia.subject.toStdString(),dia.type.toStdString(),dia.file_name.toStdString(),dia.priority);
     return cf;
}

AddFileDialog::~AddFileDialog()
{
    delete ui;
}
