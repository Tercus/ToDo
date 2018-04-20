#ifndef CONNECTCLASS_H
#define CONNECTCLASS_H

#include <QObject>
#include <QBuffer>
#include <QDomElement>
#include <QMap>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class ConnectClass : public QObject
{
    Q_OBJECT

public:
    explicit ConnectClass(QObject *parent = 0);
private:
    QString url;
    QString requestType;
    QString username = "Test";
    QString password = "Testotest";
    QString createAuth();
    QString requestBody(QString requestType);
    void buildRequest(QString requestType);
    QMap<QString, QString> NodeRunner(QDomNode Node);
    void sendUpdates(QString url, QString etag, QString ics);
public slots:
    void new_Request(QString requestType);
    void requestFinished(QNetworkReply *reply);
};

#endif // CONNECTCLASS_H
