#include "getonlineserverlist.h"

getOnlineServerList::getOnlineServerList(QString ServerUrl):url(ServerUrl)
{
    ifError=false;
}

void getOnlineServerList::run()
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
        ifError = true;
        replyData.clear();
    }
    reply->deleteLater();
    reply = nullptr;
    if(!ifError)
        emit gotOnlineServerListSingal(QString(replyData),ifError);
    else
        emit gotOnlineServerListSingal("",ifError);
}
