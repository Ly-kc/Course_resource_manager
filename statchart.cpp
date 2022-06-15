#include "statchart.h"
using namespace QtCharts;

StatChart::StatChart(QWidget *parent) : QWidget(parent)
{

    whole_layout = new QVBoxLayout;
    head_layout = new QHBoxLayout;
    body_layout = new QStackedLayout;

    switch_combo = new QComboBox;

    chart = new QChart;
    chartview = new QChartView;
    QValueAxis* mAxY = new QValueAxis;
    QValueAxis* mAxX = new QValueAxis;
    QLineSeries* mLineSeries = new QLineSeries();
    //y轴范围
    mAxY->setRange(0, 10);
    // Y轴分等份
    mAxY->setTickCount(11);
    mAxX->setRange(0,10);
    mAxX->setTickCount(11);
    // 将系列添加到图表
    chart->addSeries(mLineSeries);
    chart->setTheme(QtCharts::QChart::ChartThemeBrownSand);
    mAxX->setTitleText(QString(tr("ImageNumber")));
    mAxY->setTitleText(QString(tr("ReadRate(%)")));
    chart->addAxis(mAxY, Qt::AlignLeft);
    chart->addAxis(mAxX, Qt::AlignBottom);
    mLineSeries->attachAxis(mAxY);
    mLineSeries->attachAxis(mAxX);
    //背景
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    //chart->setBackgroundVisible(false);

    //设置外边界全部为0
    chart->setContentsMargins(0, 0, 0, 0);
    //设置内边界全部为0
    chart->setMargins(QMargins(0, 0, 0, 0));
    //设置背景区域无圆角
    chart->setBackgroundRoundness(0);
    //突出曲线上的点
    mLineSeries->setPointsVisible(true);
    //图例
    QLegend *mlegend = chart->legend();
    mLineSeries->setName("testname");


    mLineSeries->setColor(QColor(255,0,0));
    //在底部显示
    mlegend->setAlignment(Qt::AlignBottom);
    mlegend->show();
    // 将图表绑定到视图 wiget 为 QChartView
    chartview->setRenderHint(QPainter::Antialiasing); //抗锯齿
    chartview->setChart(chart);
    for(int i = 0 ;i < 10;i++){
        mLineSeries->append(i+1, i);
    }

    body_layout->addWidget(chartview);
    head_layout->addWidget(switch_combo);
    head_layout->addStretch(4);
    whole_layout->addLayout(head_layout);
    whole_layout->addLayout(body_layout,1);
    whole_layout->addLayout(body_layout);

    this->setLayout(whole_layout);
}

StatChart::~StatChart()
{

}
