#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

void MainWindow::buildRequest(QUrl url, QString username, QString password, QString requestType)
{
//    Set the main URL for the thingy
//    QUrl url(raw_url);
    QNetworkRequest request(url);

//    Set the username and Password
    QString concatenated = username + ":" + password;
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

//    No idea why this is needed, but apparently Nextcloud 11+ needs it
    request.setRawHeader("OCS-APIRequest", "true");

//    we set a user agent to prevent troubles with some Nextcloud server hosting providers
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");

//    build the request body
    QString body = requestBody(requestType);

//    acquire the size for the body to set in header
    QByteArray *dataToSend = new QByteArray(body.toUtf8());
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QBuffer *buffer = new QBuffer(dataToSend);

//    Init new NAM and send the request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->sendCustomRequest(request, "PROPFIND", buffer);

//    Connect the NAM with the SLOT requestFinished
    connect(manager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(requestFinished(QNetworkReply*))
            );
}

QString MainWindow::requestBody(QString requestType)
{
    QString bodyContent;

    if(requestType == "get_calendar_list") {
        //body to get a list of all the available calendars
        bodyContent = "<d:propfind xmlns:d=\"DAV:\" xmlns:cs=\"http://sabredav.org/ns\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\"> \
                            <d:prop> \
                                <d:resourcetype /> \
                                <d:displayname /> \
                                <cs:getctag /> \
                                <c:supported-calendar-component-set /> \
                            </d:prop> \
                       </d:propfind>";
    }
    else if(requestType == "get_todo") {
        bodyContent = "<c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\"> \
                            <d:prop> \
                                <d:getetag /> \
                                <d:getlastmodified /> \
                            </d:prop> \
                            <c:filter> \
                                <c:comp-filter name=\"VCALENDAR\"> \
                                    <c:comp-filter name=\"VTODO\" /> \
                                </c:comp-filter> \
                            </c:filter> \
                       </c:calendar-query>";
    }
    else if(requestType == "test") {
        bodyContent = "Nothing but a little test";
    }
    else {
        bodyContent = "";
        debugMessage("requested bodyType not found");
    }
    return bodyContent;
}
