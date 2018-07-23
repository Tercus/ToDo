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
#include "entryclass.h"

class Request : public QObject
{
    Q_OBJECT

public:
    explicit Request(QObject *parent = 0);
    void set_request_method(QString transmit_method);
    void set_body(QByteArray transmit_body);
    void send_request();
private:
    QByteArray body;
    QString request_method;
    QNetworkRequest request;
    QNetworkAccessManager manager;
    QMap<QString, QString> NodeRunner(QDomNode Node);
    void sendUpdates(QString url, QString etag, QString ics);
public slots:
    void requestFinished(QNetworkReply *reply);
};

#endif // REQUEST_H
