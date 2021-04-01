#ifndef GETONLINESERVERLIST_H
#define GETONLINESERVERLIST_H

#include <QThread>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QEventLoop>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class getOnlineServerList : public QThread
{
    Q_OBJECT
public:
    getOnlineServerList(QString);
    void run();

private:
    QString url;
    bool ifError;

signals:
    void gotOnlineServerListSingal(QString,bool);
};

#endif // GETONLINESERVERLIST_H
