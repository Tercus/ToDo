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
    void set_request_method(QString transmit_method);
    void set_body(QByteArray transmit_body);
private:
    QString request_method;
    QByteArray body;
    QMap<QString, QString> NodeRunner(QDomNode Node);
    void sendUpdates(QString url, QString etag, QString ics);
public slots:
    void requestFinished(QNetworkReply *reply);
};

#endif // REQUEST_H
