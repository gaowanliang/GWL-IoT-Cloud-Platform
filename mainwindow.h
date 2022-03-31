#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QPainter>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>


#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    void closeThread();

protected:
    virtual void run();
signals:
       void MySignal(QString);

private:
    volatile bool isStop;       //isStop是易失性变量，需要用volatile进行申明
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 绘图事件
    void paintEvent(QPaintEvent *);

private slots:
    void on_btnSwitch_clicked();

    void serialPortRead_Slot();

    void on_btnSend_clicked();

    void on_btnClearRec_clicked();

    void on_btnClearSend_clicked();

    void on_chkRec_stateChanged(int arg1);

    void on_chkSend_stateChanged(int arg1);

    void on_chkTimSend_stateChanged(int arg1);

    void on_lblBaudRate_linkActivated(const QString &link);
    void onGet();

private:
    Ui::MainWindow *ui;

    QSerialPort *mySerialPort;
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    QNetworkAccessManager *mgr1 = new QNetworkAccessManager(this);

    MyThread *thread1;
    QEventLoop loop;

    // 发送、接收字节计数
    long sendNum, recvNum;
    QLabel *lblSendNum;
    QLabel *lblRecvNum;
    void setNumOnLabel(QLabel *lbl, QString strS, long num);
    QString temp,humi,_temp,_humi;
    bool flag=false;
    void post(QString,QJsonObject);


    // 定时发送-定时器
    QTimer *timSend;

};




#endif // MAINWINDOW_H
