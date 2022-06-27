#ifndef STATCHART_H
#define STATCHART_H

#include"QtHeaderFiles.h"
#include<mainwindow.h>

class StatChart : public QWidget
{
    Q_OBJECT
public:
    explicit StatChart(QWidget *parent = nullptr);
    QVBoxLayout* whole_layout;
    QHBoxLayout* head_layout;
    QStackedLayout* body_layout;
    QComboBox* switch_combo;
    QChartView* pie_chartview;
    QChart* pie_chart;
    QChartView* line_chartview;
    QChart* line_chart;
    void paint_pie();
    void paint_line();
    ~StatChart();

    void paintEvent(QPaintEvent *);
signals:

};

#endif // STATCHART_H
