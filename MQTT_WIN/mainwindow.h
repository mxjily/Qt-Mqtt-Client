#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"mqtt/qmqtt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void onMQTT_Connectted();
    void onMQTT_Subscribed(const QString &topic);
    void onMQTT_Received(const QMQTT::Message &message);
};

#endif // MAINWINDOW_H
