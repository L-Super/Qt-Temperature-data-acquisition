#include<iostream>
#include<time.h>
#include<unistd.h>
#include<bitset>
#include<QTcpSocket>
#include<QHostAddress>
#include<QDebug>

using namespace std;

int gTemp;
//16位数据 高8位整数，低8位小数
short makeTemp()
{
    srand(clock());
    short temp=0;
    char high=0;
    char low=0;
    high=34+rand()%9;
    low=34+rand()%100;

    cout<<(int)high<<endl;
    cout<<(int)low<<endl;

    //将产生的数赋值到temp 位运算
    temp=high;
    temp=temp<<8;
    //16进制和二进制输出
    cout<<hex<<temp<<endl;//16位进制输出
    cout<<bitset<16>(temp)<<endl;

    temp+=low;
    cout<<hex<<temp<<endl;//16位进制输出
    cout<<bitset<16>(temp)<<endl;

    while (1) {
        usleep(100*100);
        gTemp=temp;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QTcpSocket *client=new QTcpSocket;
    QHostAddress address("127.0.0.1");
    client->connectToHost(address,8888);
    if(client->waitForConnected())
    {
        //对方地址和端口
        qDebug()<<client->peerAddress();
        qDebug()<<client->peerPort();
        //自己地址和端口
        qDebug()<<client->localAddress();
        qDebug()<<client->localPort();
    }

    makeTemp();



    return 0;
}
