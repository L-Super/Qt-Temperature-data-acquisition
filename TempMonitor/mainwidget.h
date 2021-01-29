#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QtChartView>
QT_CHARTS_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    bool startServer();

    QTcpServer *server;
    QTcpSocket *dataSocket;
    //定义槽函数
private slots:
    void newConnectionAccept();

};
#endif // MAINWIDGET_H
