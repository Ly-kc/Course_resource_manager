#ifndef STATCHART_H
#define STATCHART_H

#include <QtCharts>
#include <QChartView>
#include <QChart>
#include <QWidget>
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
    QChartView* chartview;
    QChart* chart;
    ~StatChart();
signals:

};

#endif // STATCHART_H
