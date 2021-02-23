#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QChartView>
#include<QChart>
//点状图
#include<QtCharts/QScatterSeries>
//折线图
#include<QtCharts/QLineSeries>
#include<QLabel>
//数字显示器
#include<QLCDNumber>
//多媒体播放器
#include<QMediaPlayer>

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
    //警戒线
    QLineSeries *alertLineSeries;
    //连接线
    QLineSeries *connectLineSeries;
    QLabel *currentTempLabel;
    QLCDNumber *currentLcdNumber;
    //报警音
    QMediaPlayer *alertplayer;
    //定义槽函数
private slots:
    void newConnectionAccept();

};
#endif // MAINWIDGET_H
