#include "request.h"

Request::Request(QObject *parent) : QObject(parent)
{
    qDebug() << "Making a new request.";

//    setting general settings

    request.setUrl(QUrl("https://nextcloud.timesinks.de/remote.php/dav/calendars/Test/test_list/"));
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));

//    set header data

    QString headerAuthData = "Basic " + QByteArray(QString("Test:Testotest").toLocal8Bit()).toBase64();
    request.setRawHeader("Authorization", headerAuthData.toLocal8Bit());
    request.setRawHeader("Depth", "1");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml; charset=utf-8");
}

void Request::send_request()
{
    request.setHeader(QNetworkRequest::ContentLengthHeader, body.size());
    QBuffer *buffer = new QBuffer(&body);
    manager.sendCustomRequest(request, request_method.toLocal8Bit(), buffer);
}

void Request::set_request_method(QString transmit_method)
{
//    Set the request method. This will later include safetychecks.
//    getting avaliable lists should be PROPFIND, while getting a certain TODO list or checking updates should be REPORT

    if(transmit_method == "REPORT" || transmit_method == "PROPFIND") {
        request_method = transmit_method;
    }
}

void Request::set_body(QByteArray transmit_body)
{
//    Set the body of the request. This will later include some checks to secure no breaking of data

    body = transmit_body;
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
