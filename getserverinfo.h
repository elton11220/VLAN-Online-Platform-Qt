#ifndef GETSERVERINFO_H
#define GETSERVERINFO_H

#include <QThread>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QEventLoop>
#include <QProcess>

class getServerInfo : public QThread
{
    Q_OBJECT
public:
    getServerInfo(QString ServerUrl,int id);
    void run();
private:
    QString url;
    QString pureUrl;
    int classID;
    bool ifError;
    int Ping;
    QString responseText;
signals:
    void requestDone(QString, int, bool, int);
};

#endif // GETSERVERINFO_H
