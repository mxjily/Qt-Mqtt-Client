#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mqtt/qmqtt.h"
int flag = 0;  //判断是否连接服务器
void MainWindow::onMQTT_Connectted(){
    flag=1;
}
//成功订阅
void MainWindow::onMQTT_Subscribed(const QString &topic){
    //原程序 ui->plainTextEdit->appendPlainText(message.topic());
   //原程序plainTextEdit改为对应的文本框的名字
   //appendPlainText()函数改为append函数，两函数功能一样，可能由于QT版本号不同，导致函数名称不同。
    ui->textEdit->append(topic);
    flag=1;
}

//接收到消息
void MainWindow::onMQTT_Received(const QMQTT::Message &message){
    ui->textEdit_2->append(message.topic());
    ui->textEdit_3->append(message.payload());
    flag=1;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  ////////////////
    this->setMaximumSize(300,355);
    this->setMinimumSize(300,255);

    // 如果没有连接服务器，显示提示信息
    if(!flag){

         ui->textEdit->append("当前未连接");
         ui->textEdit_2->append("当前未连接");
         ui->textEdit_3->append("当前未连接");

    }

    QMQTT::Client *client;
    client = new QMQTT::Client(QHostAddress("127.0.0.1"),1883);  //new client
    client->connectToHost();
    connect(client,SIGNAL(connected()),this,SLOT(onMQTT_Connected()));
    connect(client,SIGNAL(subscribed(const QString &)),this,SLOT(onMQTT_Subscribed(QString)));
    connect(client,SIGNAL(received(const QMQTT::Message &)),this,SLOT(onMQTT_Received(QMQTT::Message)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

