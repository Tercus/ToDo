#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

void MainWindow::sendUpdates(QString url, QString etag, QString ics)
{
    QNetworkRequest request(url);

    QByteArray *dataToSend = new QByteArray(ics.toUtf8());
    QBuffer *buffer = new QBuffer(dataToSend);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

    // set header data
    request.setRawHeader("Authorization", createAuth().toLocal8Bit());
    request.setRawHeader("If-Match", etag.toUtf8());
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());

    manager->sendCustomRequest(request, "PUT", buffer);
}

void MainWindow::buildRequest(QString requestType)
{
    QNetworkRequest request(ui->lineEdit_server->text());
    QString body = requestBody(requestType);
    QByteArray *dataToSend = new QByteArray(body.toUtf8());
    QBuffer *buffer = new QBuffer(dataToSend);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    QString requestMethod;


    // set header data
    request.setRawHeader("Authorization", createAuth().toLocal8Bit());
    request.setRawHeader("Depth", "1");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());


    if(requestType == "get_calendar_list") {
        requestMethod = "PROPFIND";
    }
    else if(requestType == "get_todo_list") {
        requestMethod = "REPORT";
    }
    else if(requestType == "check_updates") {
        requestMethod = "REPORT";
    }

    manager->sendCustomRequest(request, requestMethod.toLocal8Bit(), buffer);
}

QString MainWindow::createAuth()
{
    QString concatenated = ui->lineEdit_username->text() + ":" + ui->lineEdit_password->text();
    QByteArray authData = concatenated.toLocal8Bit().toBase64();
    QString headerAuthData = "Basic " + authData;
    return headerAuthData;
}

QString MainWindow::requestBody(QString requestType)
{
    QString bodyContent;

    if(requestType == "get_calendar_list") {
        //body to get a list of all the available calendars
        bodyContent = "<d:propfind xmlns:d=\"DAV:\"> \
                            <d:prop> \
                                <d:displayname /> \
                                <cs:getctag xmlns:cs=\"http://calendarserver.org/ns/\" /> \
                            </d:prop> \
                       </d:propfind>";
    }
    else if(requestType == "get_todo_list") {
        bodyContent = "<c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\"> \
                            <d:prop> \
                                <d:getetag /> \
                                <d:getlastmodified /> \
                                <c:calendar-data /> \
                            </d:prop> \
                            <c:filter> \
                                <c:comp-filter name=\"VCALENDAR\"> \
                                    <c:comp-filter name=\"VTODO\" /> \
                                </c:comp-filter> \
                            </c:filter> \
                       </c:calendar-query>";
    }
    else if(requestType == "check_updates") {
        bodyContent = "<c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\"> \
                            <d:prop> \
                                <d:getetag /> \
                            </d:prop> \
                            <c:filter> \
                                <c:comp-filter name=\"VCALENDAR\"> \
                                    <c:comp-filter name=\"VTODO\" /> \
                                </c:comp-filter> \
                            </c:filter> \
                       </c:calendar-query>";
    }
    else {
        bodyContent = "";
        qDebug() << "requested bodyType not found";
    }
    return bodyContent;
}
