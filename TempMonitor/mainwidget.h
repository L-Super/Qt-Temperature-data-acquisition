#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QChartView>
#include<QChart>
#include<QtCharts/QScatterSeries>


QT_CHARTS_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    bool startServer();
    void createChart();

    QTcpServer *server;
    QTcpSocket *dataSocket;
    //图表视图
    QChartView *chartview;
    //主图表
    QChart *mainChart;
    //图类型 点状图
    QScatterSeries *dotSeries;
    //定义槽函数
private slots:
    void newConnectionAccept();

};
#endif // MAINWIDGET_H
