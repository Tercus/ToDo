#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QDebug>
#include <QBuffer>
#include <QDomElement>
#include <QMap>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Request : public QObject
{
    Q_OBJECT

public:
    explicit Request(QObject *parent = 0);
    QNetworkAccessManager manager;
    void send_request(QString transmit_method, QByteArray transmit_body);
private:
    QByteArray body;
    QString request_method;
    QNetworkRequest request;
//    void sendUpdates(QString url, QString etag, QString ics);
};

#endif // REQUEST_H
