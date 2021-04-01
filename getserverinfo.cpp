#include "getserverinfo.h"

getServerInfo::getServerInfo(QString ServerUrl,int id):url(ServerUrl+"/info"),classID(id)
{
    ifError = false;
    Ping = 999;
    pureUrl = ServerUrl.split(":")[0];
}

void getServerInfo::run()
{
    QByteArray strUrl = url.toStdString().c_str();
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
        QString errString = reply->error() ? reply->errorString() : QString("发生重定向(%1)").arg(statusCode);
        replyData.clear();
        replyData.append(errString);
        ifError = true;
    }
    reply->deleteLater();
    reply = nullptr;
    if(!ifError){
        //Ping
        QProcess p(0);
    #if defined (Q_OS_WIN32)
        p.start(QString("ping %1 -n 1 -w 300").arg(pureUrl));
    #elif defined(Q_OS_MACOS)
        p.start(QString("ping -c1 %1").arg(pureUrl));
    #elif definde(Q_OS_LINUX)
        p.start(QString("ping -s 1 -c 1 %1").arg(pureUrl));
    #endif
        p.waitForStarted();
        p.waitForFinished();
        QString pingRes = QString::fromLocal8Bit(p.readAllStandardOutput());
    #if defined (Q_OS_WIN32)
        if(pingRes.contains("="))
            Ping = pingRes.mid(pingRes.indexOf("=",pingRes.indexOf("=")+1)+1,pingRes.indexOf("ms")-pingRes.indexOf("=",pingRes.indexOf("=")+1)-1).toInt();
    #elif defined(Q_OS_MACOS)
    #elif defined(Q_OS_LINUX)
    #endif
        //
    }
    emit requestDone(QString(replyData),classID,ifError,Ping);
}
