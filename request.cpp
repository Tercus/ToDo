#include "request.h"

Request::Request(QObject *parent) : QObject(parent)
{
    qDebug() << "A new request has been created.";

//    set header data

    request.setUrl(QUrl("https://nextcloud.timesinks.de/remote.php/dav/calendars/Test/test_list/"));
    QString headerAuthData = "Basic " + QByteArray(QString("Test:Testotest").toLocal8Bit()).toBase64();
    request.setRawHeader("Authorization", headerAuthData.toLocal8Bit());
    request.setRawHeader("Depth", "1");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
}

void Request::send_request(QString transmit_method, QByteArray transmit_body)
{
    request.setHeader(QNetworkRequest::ContentLengthHeader, transmit_body.size());
    manager.sendCustomRequest(request, transmit_method.toLocal8Bit(), transmit_body);
}

//void Request::sendUpdates(QString url, QString etag, QString ics)
//{
//    QNetworkRequest request(url);

//    QByteArray *dataToSend = new QByteArray(ics.toUtf8());
//    QBuffer *buffer = new QBuffer(dataToSend);

//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

//    // set header data
//    QString concatenated = "Test:Testotest";
//    QByteArray authData = concatenated.toLocal8Bit().toBase64();
//    QString headerAuthData = "Basic " + authData;

//    request.setRawHeader("Authorization", headerAuthData.toLocal8Bit());
//    request.setRawHeader("If-Match", etag.toUtf8());
//    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
//    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());

//    manager->sendCustomRequest(request, "PUT", buffer);
//}
