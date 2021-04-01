#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //加载样式表
    QFile file(":others/mainSheet");
    if(file.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
    //调整UI
    isConnected = false;
    connID = 0;
    ui->tabWidget->setCurrentIndex(0);
    ui->btnAddServer->move(ui->btnAddServer->x(),ui->btnDelServer->y()-ui->btnAddServer->height());
    //tab_2
    lblTitle->setParent(tab_2);
    lblSubTitle->setParent(tab_2);
    lblPing->setParent(tab_2);
    lblPlayer->setParent(tab_2);
    lblVersion->setParent(tab_2);
    lblPingIcon->setParent(tab_2);
    lblPlayerIcon->setParent(tab_2);
    lblVersionIcon->setParent(tab_2);
    lblPingTitle->setParent(tab_2);
    lblPlayerTitle->setParent(tab_2);
    lblVersionTitle->setParent(tab_2);
    widgetPing->setParent(tab_2);
    widgetPlayer->setParent(tab_2);
    widgetVersion->setParent(tab_2);
    btnGetHelp->setParent(tab_2);
    btnDisconnect->setParent(tab_2);
    //
    widgetPing->resize(160,160);
    widgetPlayer->resize(160,160);
    widgetVersion->resize(160,160);
    widgetPing->move(50,111);
    widgetPlayer->move(225,111);
    widgetVersion->move(400,111);
    widgetPing->setStyleSheet("border:1px solid #ccc;border-radius:10px;background-color:rgba(220,220,220,0.3);");
    widgetPlayer->setStyleSheet("border:1px solid #ccc;border-radius:10px;background-color:rgba(220,220,220,0.3);");
    widgetVersion->setStyleSheet("border:1px solid #ccc;border-radius:10px;background-color:rgba(220,220,220,0.3);");
    lblTitle->setAlignment(Qt::AlignCenter);
    lblSubTitle->setAlignment(Qt::AlignCenter);
    lblTitle->setStyleSheet("font-size:16px;font-family:'YouYuan';font-weight:bold;color:rgb(0, 160, 230);");
    lblSubTitle->setStyleSheet("font-size:13px;font-family:'Helvetica';color:#a9a9a9");
    lblPing->setAlignment(Qt::AlignCenter);
    lblPlayer->setAlignment(Qt::AlignCenter);
    lblVersion->setAlignment(Qt::AlignCenter);
    lblPing->setStyleSheet("font-size:45px;font-family:'Helvetica';font-weight:bold;color:#00a0e6;"); //#00a0e6
    lblPlayer->setStyleSheet("font-size:45px;font-family:'Helvetica';font-weight:bold;color:#00a0e6;");
    lblVersion->setStyleSheet("font-size:35px;font-family:'Helvetica';font-weight:bold;color:#00a0e6;");
    lblPing->setText("00");
    lblPlayer->setText("00");
    lblVersion->setText("0.0.0");
    lblPing->adjustSize();
    lblPlayer->adjustSize();
    lblVersion->adjustSize();
    lblPing->move(widgetPing->x()+widgetPing->width()/2-lblPing->width()/2,widgetPing->y()+45);
    lblPlayer->move(widgetPlayer->x()+widgetPlayer->width()/2-lblPlayer->width()/2,widgetPlayer->y()+45);
    lblVersion->move(widgetVersion->x()+widgetVersion->width()/2-lblVersion->width()/2,lblPlayer->y()+lblPlayer->height()/2-lblVersion->height()/2);
    lblPingIcon->setMaximumSize(25,25);
    lblPlayerIcon->setMaximumSize(25,25);
    lblVersionIcon->setMaximumSize(25,25);
    lblPingIcon->setPixmap(QPixmap(":/images/icon_Ping"));
    lblPlayerIcon->setPixmap(QPixmap(":/images/icon_PlayerCount"));
    lblVersionIcon->setPixmap(QPixmap(":/images/icon_Version"));
    lblPingIcon->setScaledContents(true);
    lblPlayerIcon->setScaledContents(true);
    lblVersionIcon->setScaledContents(true);
    lblPingIcon->move(widgetPing->x()+35,widgetPing->y()+widgetPing->height()-40);
    lblPlayerIcon->move(widgetPlayer->x()+35,widgetPlayer->y()+widgetPlayer->height()-40);
    lblVersionIcon->move(widgetVersion->x()+30,widgetVersion->y()+widgetVersion->height()-40);
    lblPingTitle->setText("Ping(ms)");
    lblPlayerTitle->setText("在线人数");
    lblVersionTitle->setText("服务器版本");
    lblPingTitle->setStyleSheet("color:#a9a9a9;font-size:13px;");
    lblPlayerTitle->setStyleSheet("color:#a9a9a9;font-size:13px;");
    lblVersionTitle->setStyleSheet("color:#a9a9a9;font-size:13px;");
    lblPingTitle->adjustSize();
    lblPlayerTitle->adjustSize();
    lblVersionTitle->adjustSize();
    lblPingTitle->move(lblPingIcon->x()+lblPingIcon->width()+5,lblPingIcon->y()+lblPingIcon->height()/2-lblPingTitle->height()/2);
    lblPlayerTitle->move(lblPlayerIcon->x()+lblPlayerIcon->width()+5,lblPingTitle->y());
    lblVersionTitle->move(lblVersionIcon->x()+lblVersionIcon->width()+5,lblPingTitle->y());

    btnGetHelp->resize(120,40);
    btnDisconnect->resize(120,40);
    btnGetHelp->move(150,316);
    btnDisconnect->move(341,316);
    btnGetHelp->setText("连接帮助");
    btnDisconnect->setText("断开连接");
    btnGetHelp->setStyleSheet("QPushButton{font-size:13px;font-weight:bold;color:#03cbbe;border:2px solid #03cbbe;border-radius:20px;}QPushButton::pressed{color:#03b4be;border:2px solid #03b4be;}QPushButton::hover{background-color:rgba(220,220,220,0.5);}");
    btnDisconnect->setStyleSheet("QPushButton{font-size:13px;font-weight:bold;color:#03cbbe;border:2px solid #03cbbe;border-radius:20px;}QPushButton::pressed{color:#03b4be;border:2px solid #03b4be;}QPushButton::hover{background-color:rgba(220,220,220,0.5);}");
    connect(btnDisconnect,&QPushButton::clicked,this,&MainWindow::btnDisconnect_Clicked);
    connect(btnGetHelp,&QPushButton::clicked,this,&MainWindow::btnGetHelp_Clicked);
    //
    //加载系统类型
#if defined(Q_OS_WIN32)
    qDebug()<<"Debug - WIN32";
    ui->sysLabel->setText("Win32");
    this->setWindowTitle(softName + " " + QString::number(localVersion,10,1) + "." + QString::number(localSubVersion) + " for Windows");
#elif defined(Q_OS_MACOS)
    qDebug()<<"Debug - MACOS";
    ui->sysLabel->setText("macOS");
    this->setWindowTitle(softName + " " + QString::number(localVersion,10,1) + "." + QString::number(localSubVersion) + " alpha 6 for macOS");
#elif defined(Q_OS_LINUX)
    qDebug()<<"Debug - LINUX";
    ui->sysLabel->setText("Linux");
    this->setWindowTitle(softName + " " + QString::number(localVersion,10,1) + "." + QString::number(localSubVersion) + " alpha 6 for Linux");
#endif
    //初始化状态栏
#if !defined(Q_OS_MACOS)
    ui->menubar->setVisible(false);
    ui->menubar->setEnabled(false);
#else
    QAction* actAddServer = new QAction("添加服务器",this); //状态栏
    ui->menubar->addAction(actAddServer);
    connect(actAddServer,&QAction::triggered,this,&MainWindow::on_btnAddServer_clicked);
#endif
    ui->statusbar->addWidget(statusBarUpd);
    ui->statusbar->addPermanentWidget(statusBarConnState);
    //
    ui->logBox->setText("VLAN Online Platform Init");
    ui->sysLabel->adjustSize();
    //初始化服务器列表
    ui->serverList->setModel(model);
    model->setHorizontalHeaderItem(0,new QStandardItem("服务器"));
    model->setHorizontalHeaderItem(1,new QStandardItem("状态"));
    model->setHorizontalHeaderItem(2,new QStandardItem("在线"));
    model->setHorizontalHeaderItem(3,new QStandardItem("版本"));
    model->setHorizontalHeaderItem(4,new QStandardItem("延迟"));
    model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
    ui->serverList->setColumnWidth(0,230);
    ui->serverList->setColumnWidth(1,45);
    ui->serverList->setColumnWidth(2,50);
    ui->serverList->setColumnWidth(3,130);
    ui->serverList->setColumnWidth(4,45);
    ui->serverList->setColumnWidth(5,109);
    //读取服务器配置文件
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
//    QSslConfiguration config;
//    QSslConfiguration conf = request.sslConfiguration();
//    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
//    conf.setProtocol(QSsl::TlsV1_2);
//    request.setSslConfiguration(conf);
    request.setUrl(QUrl(configLink));
    connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onGotServerConfig(QNetworkReply*)));
//    naManager->connectToHostEncrypted(configLink);
    QNetworkReply* gotData = naManager->get(request);
    //初始化程序
    QThread* thread = new QThread(this);
    QTimer* timer = new QTimer(0);
    timer->moveToThread(thread);
    timer->setInterval(150);
    connect(timer,&QTimer::timeout,this,[=](){
        thread->quit();
        appAutoFail();
        loadLocalConfig();
        if(lSetttings->ifShowUpdateLog){
            localConfig->beginGroup("settings");
            localConfig->setValue("ifShowUpdateLog","false");
            localConfig->endGroup();
            QMessageBox::information(this,"版本信息","版本号：" + QString::number(localVersion,10,1) + "." + QString::number(localSubVersion) + "\n\n" + lSetttings->updateContent);
            QMessageBox::information(this,"声明","本软件由绿胡子大叔开发，作为Github-spacemeowx2的开源项目switch-lan-play的图形界面，仅供技术研究，不得用于任何商业用途，下载试用后请24小时内删除。\n"
                                               "根据二〇〇二年一月一日《计算机软件保护条例》规定：为了学习和研究软件内含的设计思想和原理，"
                                               "通过安装、显示、传输或者存储软件等方式使用软件的，可不经软件著作权人许可，无需向其支付报酬！\n");
        }
        checkLanPlayRuntime();
        if(lSetttings->ifFirstCheckServerList){
#if defined (Q_OS_WIN32)
            localConfig->beginGroup("settings");
            localConfig->setValue("ifFirstCheckServerList","false");
            localConfig->endGroup();
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_LINUX)
#endif
            firstGetOnlineServerList();
        }else
            refreshServerListAll();
        //定时刷新服务器列表
        refreshListTimer->moveToThread(refreshListThread);
        refreshListTimer->setInterval(10000);
        connect(refreshListTimer,&QTimer::timeout,this,[=](){
            refreshServerListAll();
        },Qt::QueuedConnection);
        connect(refreshListThread,SIGNAL(finished()),refreshListTimer,SLOT(deleteLater()));
        refreshListThread->start();
        connect(refreshListThread, SIGNAL(started()), refreshListTimer,SLOT(start()));
        //
    },Qt::QueuedConnection);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(thread,SIGNAL(finished()),timer,SLOT(deleteLater()));
    thread->start();
    connect(thread, SIGNAL(started()), timer,SLOT(start()));
}

void MainWindow::closeEvent(QCloseEvent*)
{
    refreshListThread->quit();
    saveLog();
}

void MainWindow::loadLocalConfig()
{
    int count=0; //读取到的服务器数量
#if defined(Q_OS_WIN32)
    localConfig->setIniCodec(QTextCodec::codecForName("GB2312"));
    localConfig->beginGroup("servers");
    QString result;
    for(int i=0;i<15;i++){
        result = localConfig->value(QString::number(i)).toString();
        if(result != ""){
            serverIP[i] = result;
            count++;
        }
        else
            break;
    }
    localConfig->endGroup();
    localConfig->beginGroup("remarks");
    for(int i=0;i<15;i++){
        result = localConfig->value(QString::number(i)).toString();
        if(result != "" && i<count)
            serverName[i] = result;
        else
            continue;
    }
    localConfig->endGroup();
    localConfig->beginGroup("settings");
    if(localConfig->value("ifShowUpdateLog").toString() == "true")
        lSetttings->ifShowUpdateLog = true;
    else
        lSetttings->ifShowUpdateLog = false;
    lSetttings->updateContent = localConfig->value("updateContent").toString();
    if(localConfig->value("ifFirstCheckServerList").toString() == "true")
        lSetttings->ifFirstCheckServerList = true;
    else
        lSetttings->ifFirstCheckServerList = false;
    localConfig->endGroup();
#elif defined(Q_OS_MACOS)

#elif defined(Q_OS_LINUX)

#endif
    QStringList updCont = lSetttings->updateContent.split("|");
    lSetttings->updateContent = "";
    QList<QString>::Iterator iter = updCont.begin();
    for(int i=1;iter!=updCont.end();++iter,i++)
        lSetttings->updateContent += QString::number(i,10) + "." + *iter + "\n";
    for(int i=0;i<count;i++){
        if(serverName[i] == ""){
            addServerListItem(serverIP[i]);
        }else{
            addServerListItem(serverIP[i],serverName[i]);
        }
    }
    printLog("成功读取本地设置");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGotServerConfig(QNetworkReply* gotData)
{
    QVariant statusCode = gotData->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariant reason = gotData->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    QNetworkReply::NetworkError err = gotData->error();
    if(err == QNetworkReply::NoError) {
        printLog("成功获取配置文件");
        loadServerConfigJson(loadJsonFromHTML((QString)gotData->readAll()));
    }
    else {
        printLog("无法获取配置文件\n错误代码： " + statusCode.toString());
        statusBarUpd->setText("检查更新失败");
        loadServerConfigJson("null");
    }
}

inline void MainWindow::printLog(QString content)
{
    QTime* time = new QTime();
    ui->logBox->setText(QString(ui->logBox->toPlainText() + "\n" + "[" + time->currentTime().toString("hh:mm:ss") + "]" +content));
}

void MainWindow::getRequestS(QString IP)
{
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QMetaObject::Connection connRet = QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    Q_ASSERT(connRet);
    request.setUrl(QUrl(IP));
    QNetworkReply* reply = naManager->get(request);
}

void MainWindow::requestFinished(QNetworkReply* reply)
{
//    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
//    if(statusCode.isValid())
//        qDebug() << "status code=" << statusCode.toInt();

//    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
//    if(reason.isValid())
//        qDebug() << "reason=" << reason.toString();

//    QNetworkReply::NetworkError err = reply->error();
//    if(err != QNetworkReply::NoError) {
//        qDebug() << "Failed: " << reply->errorString();
//    }
//    else {
//        // 获取返回内容
//        qDebug() << QString(reply->readAll());
//    }
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        printLog("status=" + QString(statusCode.toString()));

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        printLog("reason=" + reason.toString());

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        printLog("Failed: " + reply->errorString());
    }
    else {
        // 获取返回内容
        printLog(QString(reply->readAll()));
    }
}

QString MainWindow::getRequest(QString Url)
{
    QByteArray strUrl = Url.toStdString().c_str();
    assert(!strUrl.isEmpty());
    const QUrl url = QUrl::fromUserInput(strUrl);
    assert(url.isValid());
    QNetworkRequest qnr(url);
    QNetworkAccessManager m_qnam;
    QNetworkReply* reply = m_qnam.get(qnr);
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    QByteArray replyData = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QVariant redirectAttr = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error() || 300 == statusCode || !redirectAttr.isNull())
    {
        QString errString = reply->error() ? reply->errorString() : QString("发生重定向(%1)，不允许此情况").arg(statusCode);
        printLog(QString("发送get请求时出现错误：\n网址：%1\n错误信息：%2").arg(reply->request().url().toDisplayString(), errString));
        replyData.clear();
    }
    reply->deleteLater();
    reply = nullptr;
    return QString(replyData);
}

void MainWindow::addServerListItem(QString IP,QString note)
{
    int listCount = model->rowCount();
    model->setItem(listCount,0,new QStandardItem(IP));
    model->setItem(listCount,5,new QStandardItem(note));
    saveServerList();
}

void MainWindow::delServerListItem(int id)
{
    model->removeRow(id);
    saveServerList();
}

void MainWindow::setServerListItem(int id,int ping)
{
    if(ping != 999)
        model->setData(model->index(id,4),ping);
    else{
        model->setData(model->index(id,4),"-");
        model->item(id,4)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::setServerListItem(int id,QString version,int playerCount)
{
    model->setData(model->index(id,2),QString::number(playerCount) +"/26");
    model->setData(model->index(id,3),version);
}

void MainWindow::setServerListItem(int id,bool enable)
{
    if(enable)
        model->setData(model->index(id,1),"正常");
    else{
        model->setData(model->index(id,1),"错误");
        model->setData(model->index(id,2),"-");
        model->setData(model->index(id,3),"-");
        model->setData(model->index(id,4),"-");
        model->item(id,2)->setTextAlignment(Qt::AlignCenter);
        model->item(id,3)->setTextAlignment(Qt::AlignCenter);
        model->item(id,4)->setTextAlignment(Qt::AlignCenter);
    }
}

QString MainWindow::loadJsonFromHTML(QString originJson)
{
    int firstIndex = originJson.indexOf('{');
    int lastIndex = originJson.lastIndexOf('}');
    originJson = originJson.mid(firstIndex,lastIndex-firstIndex+1);
    int tempIndex;
    while(originJson.contains("\r\n\t"))
    {
        tempIndex = originJson.indexOf("\r\n\t");
        originJson.remove(tempIndex,3);
    }
    return originJson;
}

void MainWindow::loadServerConfigJson(QString gotJson)
{
    sConfig->title = "";
    sConfig->enable = false;
    sConfig->updUrl = "null";
    sConfig->version = -1;
    sConfig->subVersion = -1;
    sConfig->updLevel = -1;
    sConfig->updDate = "null";
    sConfig->updContent = "null";
    if(gotJson != "null"){
        QJsonParseError jsonError;
        const char* gotData = gotJson.toUtf8();
        QJsonDocument doucment = QJsonDocument::fromJson(gotData, &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if (doucment.isObject())
            {
                QJsonObject object = doucment.object();
                if (object.contains("Version"))
                {
                    QJsonValue value = object.value("Version");
                    if (value.isDouble())
                        sConfig->version = value.toVariant().toDouble();
                }
                if (object.contains("SubVersion"))
                {
                    QJsonValue value = object.value("SubVersion");
                    if (value.isDouble())
                        sConfig->subVersion = value.toVariant().toInt();
                }
                if (object.contains("UpdUrl"))
                {
                    QJsonValue value = object.value("UpdUrl");
                    if (value.isString())
                        sConfig->updUrl = value.toVariant().toString();
                }
                if (object.contains("Content"))
                {
                    QJsonValue value = object.value("Content");
                    if (value.isString())
                        sConfig->updContent = value.toVariant().toString();
                }
                if (object.contains("Enable"))
                {
                    QJsonValue value = object.value("Enable");
                    if (value.isDouble())
                    {
                        int temp = value.toVariant().toInt();
                        if(temp == 0)
                            sConfig->enable = false;
                        else
                            sConfig->enable = true;
                    }
                }
                if (object.contains("UpdLevel"))
                {
                    QJsonValue value = object.value("UpdLevel");
                    if ( value.isDouble())
                        sConfig->updLevel = value.toVariant().toInt();
                }
                if (object.contains("UpdDate"))
                {
                    QJsonValue value = object.value("UpdDate");
                    if ( value.isString())
                        sConfig->updDate = value.toString();
                }
                if (object.contains("Title"))
                {
                    QJsonValue value = object.value("Title");
                    if (value.isString())
                        sConfig->title = value.toString();
                }
            }
        }
    }
    ui->bannerLabel->setText(sConfig->title);
    if(sConfig->enable == false){
        QMessageBox::warning(this,"启动失败","请访问http://bbs.818lanplay.com/\n获取更多信息");
        printLog("启动失败");
        qApp->quit();
    }
    checkUpdate();
}

void MainWindow::checkUpdate()
{
    if(sConfig->version == (double)-1 || sConfig->subVersion == -1)
        printLog("检查更新失败");
    else{
        int msgRetCode=QMessageBox::NoAll;
        if(localVersion < sConfig->version){ //检测到主版本更新
            printLog("检测到新版本\n版本号："+QString::number(sConfig->version,10,1)+".0\n更新时间："+sConfig->updDate);
            statusBarUpd->setText("检测到新版本");
            QStringList updCont = sConfig->updContent.split("|");
            QString updConte = "";
            QList<QString>::Iterator iter = updCont.begin();
            for(int i=1;iter!=updCont.end();++iter,i++)
                updConte += QString::number(i,10) + "." + *iter + "\n";
            msgRetCode = QMessageBox::question(this,"更新",
                                           "检测到新版本！\n版本号："+QString::number(sConfig->version,10,1)+".0\n更新时间："+sConfig->updDate+"\n更新说明：\n"+updConte+"\n是否更新？"
                                           ,QMessageBox::Yes | QMessageBox::No);
        }else if(localVersion == sConfig->version && localSubVersion < sConfig->subVersion){ //检测到子版本更新
            printLog("检测到新版本\n版本号："+QString::number(sConfig->version,10,1)+ "." + QString::number(sConfig->subVersion) +"\n更新时间："+sConfig->updDate);
            statusBarUpd->setText("检测到新版本");
            QStringList updCont = sConfig->updContent.split("|");
            QString updConte = "";
            QList<QString>::Iterator iter = updCont.begin();
            for(int i=1;iter!=updCont.end();++iter,i++)
                updConte += QString::number(i,10) + "." + *iter + "\n";
            msgRetCode = QMessageBox::question(this,"更新",
                                           "检测到新版本！\n版本号："+QString::number(sConfig->version,10,1)+ "." + QString::number(sConfig->subVersion) +"\n更新时间："+sConfig->updDate+"\n更新说明：\n"+updConte+"\n是否更新？"
                                           ,QMessageBox::Yes | QMessageBox::No);
        }
        if(msgRetCode == QMessageBox::Yes){
            QDesktopServices::openUrl(QUrl(sConfig->updUrl));
            qApp->quit();
        }else if(msgRetCode == QMessageBox::Close || msgRetCode == QMessageBox::No){
            if(sConfig->updLevel == 1){
                QMessageBox::warning(this,"必要更新","此版本为必要更新\n拒绝更新将无法继续使用软件");
                printLog("用户拒绝了必要更新");
                qApp->quit();
            }
        }
    }
}

bool MainWindow::is64bitOperatorSystem()
{
#if defined (Q_OS_WIN32)
    typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
    PGNSI pGNSI;
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(SYSTEM_INFO));
    pGNSI =(PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
    if (pGNSI)
    {
        pGNSI(&si);
        if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
        {
            return true;
        }
    }
    return false;
#elif defined(Q_OS_MACOS)
    return true;
#elif defined(Q_OS_LINUX)
#endif
}

void MainWindow::checkLanPlayRuntime()
{
#if defined (Q_OS_WIN32)
    QDir* dir = new QDir();
    if(!dir->exists("C:\\Windows\\System32\\wpcap.dll")){
        QMessageBox::warning(this,"修复WinPcap环境","检测到您未安装WinPcap，将无法正常运行程序\n程序将启动WinPcap安装程序\n请安装后重新打开本程序");
        printLog("WinPcap未安装");
        QProcess::startDetached(QDir::currentPath() + "\\data\\winpcap413.exe",QStringList());
        qApp->quit();
    }else{
        printLog("已检测到WinPcap");
    }
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_LINUX)
#endif
}

void MainWindow::appAutoFail()
{
    QDateTime time = QDateTime::currentDateTime();
    int currYear,currMonth;
    currYear = time.toString("yyyy").toInt();
    currMonth = time.toString("MM").toInt();
    if(currYear != appAutoFailYear || (currMonth < appAutoFailMinMonth && currYear == appAutoFailYear) || (currMonth > appAutoFailMaxMonth && currYear == appAutoFailYear)){
        printLog("当前版本已失效，请下载最新版本");
        QMessageBox::warning(this,"版本失效","当前版本已失效，将为您检查更新\n如检查失败请重新下载");
        checkUpdate();
        qApp->quit();
    }
}

void MainWindow::on_btnDelServer_clicked()
{
    if(ui->serverList->selectionModel()->hasSelection()){
        printLog("删除了服务器：" + model->index(ui->serverList->currentIndex().row(),0).data().toString());
        delServerListItem(ui->serverList->currentIndex().row());
    }
}

void MainWindow::saveServerList()
{
#if defined (Q_OS_WIN32)
    localConfig->beginGroup("servers");
    for(int i=0;i<15;i++)
        localConfig->setValue(QString::number(i),"");
    for(int i=0;i<model->rowCount();i++)
        localConfig->setValue(QString::number(i),model->index(i,0).data().toString());
    localConfig->endGroup();
    localConfig->beginGroup("remarks");
    for(int i=0;i<15;i++)
        localConfig->setValue(QString::number(i),"");
    for(int i=0;i<model->rowCount();i++)
        localConfig->setValue(QString::number(i),model->index(i,5).data().toString());
    localConfig->endGroup();
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_LINUX)
#endif
}

void MainWindow::on_btnAddServer_clicked()
{
    if(model->rowCount() >= 15)
        QMessageBox::warning(this,"提示","最多添加15个服务器");
    else{
        QDialog dialog;
        dialog.setWindowTitle("添加服务器");
        dialog.resize(430,180);
        dialog.setMaximumSize(430,180);
        dialog.setMinimumSize(430,180);
        QLabel lblSerUrl("地址：",&dialog);
        QLabel lblSerName("备注：",&dialog);
        lblSerUrl.setFont(QFont("Microsoft YaHei"));
        lblSerName.setFont(QFont("Microsoft YaHei"));
        lblSerUrl.setStyleSheet("font-size:15px;");
        lblSerName.setStyleSheet("font-size:15px");
        lblSerUrl.move(40,60-lblSerUrl.height());
        lblSerName.move(40,110-lblSerUrl.height());
        lblSerUrl.adjustSize();
        lblSerName.adjustSize();
        QTextEdit tEditUrl(&dialog);
        QTextEdit tEditName(&dialog);
        tEditUrl.resize(300,25);
        tEditName.resize(300,25);
        tEditUrl.move(45+lblSerUrl.width(),60-lblSerUrl.height()-tEditUrl.height()/2);
        tEditName.move(45+lblSerName.width(),110-lblSerName.height()-tEditName.height()/2);
        tEditUrl.setStyleSheet("font-size:15px;border:2px solid #ccc;border-radius:4px;outline:none");
        tEditName.setStyleSheet("font-size:15px;border:2px solid #ccc;border-radius:4px;outline:none");
        tEditUrl.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tEditUrl.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tEditName.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tEditName.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QPushButton btnConfirm(&dialog);
        QPushButton btnCancel(&dialog);
        btnConfirm.resize(71,31);
        btnCancel.resize(71,31);
        btnConfirm.move(20+143-btnConfirm.width()/2,tEditName.y() + 20 + tEditName.height());
        btnCancel.move(287-20-btnCancel.width()/2,tEditName.y() + 20 + tEditName.height());
        btnConfirm.setText("保存");
        btnCancel.setText("取消");
        btnConfirm.setStyleSheet("QPushButton{color:#fff;font-weight:bold;border:1px solid #00a0e6;background-color:#00a0e6;border-radius:10px;}"
                                 "QPushButton::pressed{border:2.5px solid #ccc;background-color:#00a0d2;}");
        btnCancel.setStyleSheet("QPushButton{color:#fff;font-weight:bold;border:1px solid #00a0e6;background-color:#00a0e6;border-radius:10px;}"
                                 "QPushButton::pressed{border:2.5px solid #ccc;background-color:#00a0d2;}");
        tEditUrl.setTabChangesFocus(true);
        tEditName.setTabChangesFocus(true);
        dialog.setTabOrder(&tEditUrl,&tEditName);
        dialog.setTabOrder(&tEditName,&btnConfirm);
        dialog.setTabOrder(&btnConfirm,&btnCancel);
        connect(&btnConfirm,&QPushButton::clicked,&dialog,[&](){
            if(tEditUrl.toPlainText() == ""){
                QMessageBox::warning(&dialog,"错误","服务器地址不能为空");
            }else{
                if(tEditName.toPlainText().length() > 8){
                    QMessageBox::warning(&dialog,"错误","服务器备注过长");
                    tEditName.setText("");
                }else{
                    if(tEditName.toPlainText() != ""){
                        addServerListItem(tEditUrl.toPlainText(),tEditName.toPlainText());
                    }else{
                        addServerListItem(tEditUrl.toPlainText());
                    }
                    printLog("成功添加服务器：" + tEditUrl.toPlainText());
                    refreshServerListAll();
                    dialog.close();
                }
            }
        });
        connect(&btnCancel,&QPushButton::clicked,&dialog,&QDialog::close);
        dialog.exec();
    }
}

void MainWindow::refreshServerListAll()
{
    for(int i=0;i<model->rowCount();i++){
        getServerInfo* gSInfo = new getServerInfo(model->index(i,0).data().toString(),i);
        connect(gSInfo,&getServerInfo::requestDone,this,&MainWindow::getServerInfoFinished);
        connect(gSInfo,SIGNAL(finished()),gSInfo,SLOT(deleteLater()));
        gSInfo->start();
    }
}

void MainWindow::getServerInfoFinished(QString content,int id,bool ifError,int Ping)
{
    if(ifError){
        setServerListItem(id,false);
        printLog("无法获取服务器 " + model->index(id,0).data().toString() + "的信息 [" + content + "]");
    }else{
        QJsonParseError jsonError;
        const char* gotData = content.toUtf8();
        QJsonDocument doucment = QJsonDocument::fromJson(gotData, &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if (doucment.isObject())
            {
                QJsonObject object = doucment.object();
                QJsonValue version = object.value("version");
                QJsonValue onlinePlayer = object.value("online");
                setServerListItem(id,version.toVariant().toString(),onlinePlayer.toVariant().toInt());
                setServerListItem(id,true);
                setServerListItem(id,Ping);
                if(isConnected){
                    lblPing->setText(model->index(connID,4).data().toString());
                    lblPlayer->setText(model->index(connID,2).data().toString());
                    lblPing->adjustSize();
                    lblPlayer->adjustSize();
                    lblPing->move(widgetPing->x()+widgetPing->width()/2-lblPing->width()/2,widgetPing->y()+45);
                    lblPlayer->move(widgetPlayer->x()+widgetPlayer->width()/2-lblPlayer->width()/2,widgetPlayer->y()+45);
                }
            }
        }
    }
}

void MainWindow::on_btnUpdServerList_clicked()
{
    ui->btnUpdServerList->setEnabled(false);
    getOnlineServerList* gOSList = new getOnlineServerList(serverListLink);
    connect(gOSList,&getOnlineServerList::gotOnlineServerListSingal,this,&MainWindow::getOnlineServerListFinished);
    connect(gOSList,SIGNAL(finished()),gOSList,SLOT(deleteLater()));
    gOSList->start();
}

void MainWindow::getOnlineServerListFinished(QString gotOriginJson,bool ifError)
{
    if(ifError){
        QMessageBox::critical(this,"获取失败","无法获取在线服务器列表");
        printLog("获取服务器失败");
        ui->btnUpdServerList->setEnabled(true);
    }else{
        if(QMessageBox::question(this,"成功","成功获取到最新的服务器列表\n是否保存？\n此操作将会覆盖您本地保存的服务器列表",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
            model->clear();
            model->setHorizontalHeaderItem(0,new QStandardItem("服务器"));
            model->setHorizontalHeaderItem(1,new QStandardItem("状态"));
            model->setHorizontalHeaderItem(2,new QStandardItem("在线"));
            model->setHorizontalHeaderItem(3,new QStandardItem("版本"));
            model->setHorizontalHeaderItem(4,new QStandardItem("延迟"));
            model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
            ui->serverList->setColumnWidth(0,230);
            ui->serverList->setColumnWidth(1,45);
            ui->serverList->setColumnWidth(2,45);
            ui->serverList->setColumnWidth(3,130);
            ui->serverList->setColumnWidth(4,45);
            ui->serverList->setColumnWidth(5,109);
            QJsonParseError jsonError;
            const char* gotData = loadJsonFromHTML(gotOriginJson).toUtf8();
            QJsonDocument doucment = QJsonDocument::fromJson(gotData, &jsonError);
            if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
            {
                if (doucment.isObject())
                {
                    QJsonObject object = doucment.object();
                    for(int i=0;i<15;i++){
                        QJsonValue value = object.value("name" + QString::number(i));
                        QJsonValue valueB = object.value("url" + QString::number(i));
                        if(valueB.toVariant().toString() == "")
                            break;
                        else{
                            if(value.toVariant().toString() != ""){
                                addServerListItem(valueB.toVariant().toString(),value.toVariant().toString());
                                refreshServerListAll();
                            }else{
                                addServerListItem(valueB.toVariant().toString());
                                refreshServerListAll();
                            }
                        }
                    }
                }
            }
            printLog("成功更新服务器列表");
        }
        ui->btnUpdServerList->setEnabled(true);
    }
}

void MainWindow::firstGetOnlineServerListFinished(QString gotOriginJson,bool ifError)
{
    if(ifError){
        printLog("获取服务器失败");
    }else{
        model->clear();
        model->setHorizontalHeaderItem(0,new QStandardItem("服务器"));
        model->setHorizontalHeaderItem(1,new QStandardItem("状态"));
        model->setHorizontalHeaderItem(2,new QStandardItem("在线"));
        model->setHorizontalHeaderItem(3,new QStandardItem("版本"));
        model->setHorizontalHeaderItem(4,new QStandardItem("延迟"));
        model->setHorizontalHeaderItem(5,new QStandardItem("备注"));
        ui->serverList->setColumnWidth(0,230);
        ui->serverList->setColumnWidth(1,45);
        ui->serverList->setColumnWidth(2,45);
        ui->serverList->setColumnWidth(3,130);
        ui->serverList->setColumnWidth(4,45);
        ui->serverList->setColumnWidth(5,109);
        QJsonParseError jsonError;
        const char* gotData = loadJsonFromHTML(gotOriginJson).toUtf8();
        QJsonDocument doucment = QJsonDocument::fromJson(gotData, &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if (doucment.isObject())
            {
                QJsonObject object = doucment.object();
                for(int i=0;i<15;i++){
                    QJsonValue value = object.value("name" + QString::number(i));
                    QJsonValue valueB = object.value("url" + QString::number(i));
                    if(valueB.toVariant().toString() == "")
                        break;
                    else{
                        if(value.toVariant().toString() != ""){
                            addServerListItem(valueB.toVariant().toString(),value.toVariant().toString());
                            refreshServerListAll();
                        }else{
                            addServerListItem(valueB.toVariant().toString());
                            refreshServerListAll();
                        }
                    }
                }
            }
        }
        printLog("成功更新服务器列表");
        refreshServerListAll();
    }
}

void MainWindow::saveLog()
{
    QDateTime time = QDateTime::currentDateTime();
    QString filePath = QDir::currentPath() + "\\data\\log\\" + time.toString("yyyy-MM-dd") + "-Log.txt";
    QFile file;
    file.setFileName(filePath);
    file.open(QIODevice::Append);
    file.write(QString(ui->logBox->toPlainText() + "\n\n").toLocal8Bit());
    file.close();
}

void MainWindow::showPlayTab()
{
    ui->tab->setEnabled(false);
//    ui->btnAddServer->setVisible(false);
//    ui->btnDelServer->setVisible(false);
//    ui->btnUpdServerList->setVisible(false);
    ui->btnAddServer->setEnabled(false);
    ui->btnDelServer->setEnabled(false);
    ui->btnUpdServerList->setEnabled(false);
#if defined (Q_OS_MACOS)
    ui->statusbar->setEnabled(false);
#endif
    ui->tabWidget->addTab(tab_2,"连接");
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::hidePlayTab()
{
    ui->tab->setEnabled(true);
//    ui->btnAddServer->setVisible(true);
//    ui->btnDelServer->setVisible(true);
//    ui->btnUpdServerList->setVisible(true);
    ui->btnAddServer->setEnabled(true);
    ui->btnDelServer->setEnabled(true);
    ui->btnUpdServerList->setEnabled(true);
#if defined (Q_OS_MACOS)
    ui->statusbar->setEnabled(true);
#endif

    ui->tabWidget->removeTab(1);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_serverList_doubleClicked(const QModelIndex&)
{
    QString tempstr = model->index(ui->serverList->currentIndex().row(),2).data().toString();
    tempstr.remove(tempstr.length()-3,3);
    if(tempstr.toInt() < 26)
       connectServer(ui->serverList->currentIndex().row());
    else
       QMessageBox::warning(this,"线路满员","该线路人数已满，请尝试连接其他线路");
}

void MainWindow::btnDisconnect_Clicked()
{
    if(QMessageBox::question(this,"断开连接","是否要断开与服务器的连接？",QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        disconnectServer();
}

void MainWindow::btnGetHelp_Clicked()
{
    QMessageBox::information(this,"连接帮助","1.打开设置-互联网-互联网设置\n2.修改配置：\n\nIP:10.13.xx.xx\n子网掩码:255.255.0.0\n网关:10.13.37.1\nMTU:1500\nDNS1:114.114.114.114\nDNS2:8.8.8.8\n\n注：xx为0-255中任意数字 | 除37");
}

void MainWindow::disconnectServer()
{
    isConnected=false;
    statusBarConnState->setText("双击选中的服务器项进行连接");
    shutLanPlay(lanPlayProcess->processId());
    hidePlayTab();
    printLog("与服务器断开连接");
}

void MainWindow::connectServer(int id)
{
    isConnected=true;
    connID = id;
    printLog("连接服务器 " + model->index(id,0).data().toString());
    if(model->index(id,5).data().toString() == "")
        statusBarConnState->setText("已连接到" + model->index(id,0).data().toString());
    else
        statusBarConnState->setText("已连接到" + model->index(id,5).data().toString());
    lblTitle->setText("已连接 " + model->index(id,5).data().toString());
    lblSubTitle->setText(model->index(id,0).data().toString());
    lblTitle->adjustSize();
    lblSubTitle->adjustSize();
    lblTitle->move(tab_2->width()/2 - lblTitle->width()/2,38);
    lblSubTitle->move(tab_2->width()/2 - lblSubTitle->width()/2,lblTitle->y()+lblTitle->height()+5);
    lblVersion->setText(model->index(id,3).data().toString().split("-")[0]);
    lblPing->setText(model->index(id,4).data().toString());
    lblPlayer->setText(model->index(id,2).data().toString());
    lblPlayer->adjustSize();
    lblPlayer->move(widgetPlayer->x()+widgetPlayer->width()/2-lblPlayer->width()/2,widgetPlayer->y()+45);
    lanPlay(id);
    showPlayTab();
}

void MainWindow::lanPlay(int id)
{
#if defined(Q_OS_WIN32)
    if(is64bitOperatorSystem()){
        lanPlayProcess->start(QDir::currentPath()+"\\data\\lan-play-win64.exe",QStringList() <<"--relay-server-addr" << model->index(id,0).data().toString());
    }else{
        lanPlayProcess->start(QDir::currentPath()+"\\data\\lan-play-win32.exe",QStringList() <<"--relay-server-addr" << model->index(id,0).data().toString());
    }
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_LINUX)
#endif
}

void MainWindow::shutLanPlay(quint64 pid)
{
#if defined(Q_OS_WIN32)
    QProcess pro;
    pro.start("cmd");
    pro.waitForStarted();
    pro.write(tr("taskkill /f /pid %1\n").arg(pid).toLatin1());
    pro.closeWriteChannel();
    pro.waitForFinished();
#elif defined(Q_OS_MACOS)
#elif defined(Q_OS_LINUX)
#endif
}

void MainWindow::firstGetOnlineServerList()
{
    getOnlineServerList* gOSList = new getOnlineServerList(serverListLink);
    connect(gOSList,&getOnlineServerList::gotOnlineServerListSingal,this,&MainWindow::firstGetOnlineServerListFinished);
    connect(gOSList,SIGNAL(finished()),gOSList,SLOT(deleteLater()));
    gOSList->start();
}
