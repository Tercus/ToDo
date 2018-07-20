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
private:
    QString make_body(QString requestType);
    QMap<QString, QString> NodeRunner(QDomNode Node);
    void sendUpdates(QString url, QString etag, QString ics);
public slots:
    void requestFinished(QNetworkReply *reply);
};

#endif // REQUEST_H
