#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include<QScrollBar>
#include <QWidget>
#include<QTableWidget>
#include <QScrollArea>
#include<QGroupBox>
#include<datamanager.h>
#include<datamanager.h>
#include<addfiledialog.h>
#include<mainwindow.h>

class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QHBoxLayout* head_layout;
    QHBoxLayout* table_layout;
    QHBoxLayout* combo_layout;
    QPushButton* filter_button;
    QLineEdit* name_edit;
    QComboBox* sub_filter;
    QComboBox* time_filter;
    QComboBox* type_filter;
    QComboBox* prior_filter;
//    QScrollArea* filter_area;
    QTableWidget* file_table;
    QStringList subjects;
    QStringList types;
    void show_result(); //显示筛选结果
    void init_combo();
    void init_result(); //显示所有文件
    void click_cell_slot(int row , int colum);
signals:

};

#endif // FILTERWIDGET_H
