#include "request.h"

Request::Request(QObject *parent) : QObject(parent)
{
    qDebug() << "Making a new request.";
    QString url = "https://nextcloud.timesinks.de/remote.php/dav/calendars/Test/test_list/";
    QNetworkRequest request(url);
//    QString body = make_body();
    QString body;
    QByteArray *dataToSend = new QByteArray(body.toUtf8());
    QBuffer *buffer = new QBuffer(dataToSend);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
    QString requestMethod;


    // set header data
    QString concatenated = "Test:Testotest";
    QByteArray authData = concatenated.toLocal8Bit().toBase64();
    QString headerAuthData = "Basic " + authData;

    request.setRawHeader("Authorization", headerAuthData.toLocal8Bit());
    request.setRawHeader("Depth", "1");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());


//    if(requestType == "get_calendar_list") {
//        requestMethod = "PROPFIND";
//    }
//    else if(requestType == "get_todo_list") {
//        requestMethod = "REPORT";
//    }
//    else if(requestType == "check_updates") {
//        requestMethod = "REPORT";
//    }

    manager->sendCustomRequest(request, requestMethod.toLocal8Bit(), buffer);
}

QString Request::make_body(QString requestType)
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

void Request::sendUpdates(QString url, QString etag, QString ics)
{
    QNetworkRequest request(url);

    QByteArray *dataToSend = new QByteArray(ics.toUtf8());
    QBuffer *buffer = new QBuffer(dataToSend);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

    // set header data
    QString concatenated = "Test:Testotest";
    QByteArray authData = concatenated.toLocal8Bit().toBase64();
    QString headerAuthData = "Basic " + authData;

    request.setRawHeader("Authorization", headerAuthData.toLocal8Bit());
    request.setRawHeader("If-Match", etag.toUtf8());
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());

    manager->sendCustomRequest(request, "PUT", buffer);
}

void Request::requestFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString urlPath = url.path();
    QString replyText = reply->readAll();
    qDebug() << url;

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Darnit, something went wrong: Error" << QString::number(reply->error()) << "from url" << url.toString();
        qDebug() << reply->errorString();
    }

    if(urlPath.endsWith(".ics")) {
        // Most likely a reply from editing a task
        qDebug() << "This is likely a reply from editing a task. I'll have to refresh the task list";
//        todoList[ui->listWidget->currentRow()]->set_etag(reply->rawHeader("ETag"));
//        refresh_View();
    }
    else if(replyText.contains("BEGIN:VTODO")) {
        QDomDocument doc("mydocument");
        doc.setContent(replyText);
        QDomNodeList responseNodes = doc.elementsByTagName("d:response");

        for(int x = 0; x < responseNodes.count(); x++) {
            QMap<QString, QString> node = NodeRunner(responseNodes.at(x));

            // Creating a new Entry object and adding it to the todoList
//            EntryClass *tempEntry = new EntryClass;
//            tempEntry->set_etag(node.value("d:getetag"));
//            tempEntry->set_href(node.value("d:href"));
//            tempEntry->set_ics(node.value("cal:calendar-data"));
//            todoList.push_back(tempEntry);

            // adding the entry to the listwidget
//            add_todo_entry(*tempEntry);
            qDebug() << node.value("cal:calendar-data");
        }
    }
}

QMap<QString, QString> Request::NodeRunner(QDomNode Node)
{
    QMap<QString, QString> values;
    QString currentNodeName = Node.nodeName().toUtf8();
    if(currentNodeName == "d:href" || currentNodeName == "d:getetag" || currentNodeName == "cal:calendar-data") {
        values.insert(currentNodeName, Node.toElement().QDomElement::text());
//        qDebug() << Node.toElement().QDomElement::text();
    }
    for (int x = 0; x < Node.childNodes().count(); x++) {
        values.unite(NodeRunner(Node.childNodes().at(x)));
    }
    return(values);
}
