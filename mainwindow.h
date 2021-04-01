#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QEvent>
#include <QLabel>
#include <QSettings>
#include <QFile>
#include <QTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextCodec>
#include <QTimer>
#include <QThread>
#include <QUrl>
#include <QDesktopServices>
#include <Windows.h>
#include <QProcess>
#include <QDateTime>
#include <QItemSelectionModel>
#include <QPushButton>

//#include <openssl/ssl.h>
#include "getserverinfo.h"
#include "getonlineserverlist.h"

#if defined(Q_OS_WIN32)
const QString configLink = "http://elton11220.gitee.io/vlan-online-platform-qt/config_win.html";
#elif defined(Q_OS_MACOS)
const QString configLink = "http://elton11220.gitee.io/vlan-online-platform-qt/config_mac.html";
#elif defined(Q_OS_LINUX)
#endif
const QString serverListLink = "http://elton11220.gitee.io/vlan-online-platform-qt/serverList.html";
const double localVersion = 2.0; //主版本号a.a
const int localSubVersion = 2; //子版本号<=>a.a.b
const QString softName = "VLAN Online Platform";
const int appAutoFailYear = 2021; //程序过期自动退出年
const int appAutoFailMinMonth = 3; //程序过期自动退出最小月
const int appAutoFailMaxMonth = 6; //程序过期自动退出最大月

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct serverInfo{ //服务器信息
    QString IP;
    bool enable;
    int playerCount;
    QString version;
    int ping;
    QString note;
};

struct serverConfig{ //读取服务器配置文件
    double version;
    int subVersion;
    QString updUrl;
    QString updContent;
    bool enable;
    int updLevel;
    QString updDate;
    QString title;
};

struct localSettings{ //本地程序设置
    bool ifShowUpdateLog;
    QString updateContent;
    bool ifFirstCheckServerList;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel* statusBarUpd = new QLabel("暂无更新");
    QLabel* statusBarConnState = new QLabel("双击选中的服务器项进行连接");
    QThread* refreshListThread = new QThread(this); //定时刷新服务器信息
    QTimer* refreshListTimer = new QTimer(0); //定时刷新服务器信息
    //Functions
    void firstGetOnlineServerList();
    void connectServer(int id); //连接服务器
    void disconnectServer(); //与服务器断开连接
    void lanPlay(int id); //启动LanPlay
    void shutLanPlay(quint64 pid); //关闭LanPlay
    QProcess* lanPlayProcess = new QProcess;
    inline void printLog(QString contsent);
    void saveLog(); //保存Log到本地
    void getRequestS(QString IP); //异步GET
    QString getRequest(QString Url); //同步GET 阻塞线程
    void checkUpdate();
    void checkLanPlayRuntime(); //检查LanPlay运行环境 winpcap libpcap
    bool is64bitOperatorSystem(); //判断是否为64位操作系统
    void appAutoFail(); //程序过期自动关闭
    void refreshServerListAll();
    //listView
    QStandardItemModel* model = new QStandardItemModel();
    void addServerListItem(QString IP,QString note="");
    void setServerListItem(int id,int ping);
    void setServerListItem(int id,QString version,int playerCount);
    void setServerListItem(int id,bool enable);
    void delServerListItem(int id);
    void saveServerList(); //保存当前服务器列表
    //Json
    serverConfig* sConfig = new serverConfig; //读取服务器配置文件
    void loadServerConfigJson(QString gotJson); //读取服务器配置文件
    QString loadJsonFromHTML(QString originJson); //将获取到的网页格式的JSON转化为标准JSON
    //加载本地设置、服务器列表
    void loadLocalConfig();
    QSettings* localConfig = new QSettings ("./data/config.ini", QSettings::IniFormat); //本地配置文件
    QString serverIP[15];
    QString serverName[15];
    localSettings* lSetttings = new localSettings; //读取本地设置
    void initFinished();
    //显示、隐藏连接服务器后的菜单
    void showPlayTab();
    void hidePlayTab();
    QWidget* tab_2 = new QWidget();
    QLabel* lblTitle = new QLabel();
    QLabel* lblSubTitle = new QLabel();
    QLabel* lblPing = new QLabel();
    QLabel* lblPlayer = new QLabel();
    QLabel* lblVersion = new QLabel();
    QLabel* lblPingIcon = new QLabel();
    QLabel* lblPlayerIcon = new QLabel();
    QLabel* lblVersionIcon = new QLabel();
    QLabel* lblPingTitle = new QLabel();
    QLabel* lblPlayerTitle = new QLabel();
    QLabel* lblVersionTitle = new QLabel();
    QWidget* widgetPing = new QWidget();
    QWidget* widgetPlayer = new QWidget();
    QWidget* widgetVersion = new QWidget();
    QPushButton* btnGetHelp = new QPushButton;
    QPushButton* btnDisconnect = new QPushButton();
    bool isConnected; //是否处于连接状态
    int connID; //连接的服务器序号
    //

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void requestFinished(QNetworkReply* reply);
    void onGotServerConfig(QNetworkReply* gotData); //读取服务器配置文件
    void on_btnDelServer_clicked();
    void on_btnAddServer_clicked();
    void getServerInfoFinished(QString,int,bool,int);
    void getOnlineServerListFinished(QString,bool);
    void firstGetOnlineServerListFinished(QString,bool);
    void on_btnUpdServerList_clicked();
    void on_serverList_doubleClicked(const QModelIndex &index);
    void btnDisconnect_Clicked();
    void btnGetHelp_Clicked();
};
#endif // MAINWINDOW_H
