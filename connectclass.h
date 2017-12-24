#ifndef CONNECTCLASS_H
#define CONNECTCLASS_H

#include <QObject>
#include <QBuffer>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

class ConnectClass : public QObject
{
    Q_OBJECT

public:
    explicit ConnectClass(QObject *parent = 0);
private:
    QString url;
    QString requestType;
    QString username;
    QString password;
    QString createAuth();
    QString requestBody(QString requestType);
    void buildRequest();
public slots:
    void requestFinished(QNetworkReply *reply);
};

#endif // CONNECTCLASS_H
