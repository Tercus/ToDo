#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomElement>

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString urlPath = url.path();
    debugMessage("Reply came from:" + urlPath);
    QString replyText = reply->readAll();

    if (reply->error() != QNetworkReply::NoError) {
        debugMessage("Darnit, something went wrong: \n Error " + QString::number(reply->error()) + " from url " + url.toString() + ": " + reply->errorString());
    }


    QDomDocument doc("mydocument");
    doc.setContent(replyText);
    debugMessage(doc.toString(4));


//    d:response
//     |-> d:href
//     |-> d:propstat
//          |-> d:prop
//               |-> d:getetag
//               |-> d:getlastmodified
//               |-> c:calender-data
//          |-> d:status

    QDomNodeList responseNodes = doc.elementsByTagName("d:response");
    QList<QMap<QString, QString>> testing;
    for(int x = 0; x < responseNodes.count(); x++) {
        testing.append(NodeRunner(responseNodes.at(x)));
    }
    qDebug() << testing;
//    for(int x = 0; x < responseNodes.count(); x++) {
//        QDomNode singleResponseNode = responseNodes.at(x);
//        QString URL = singleResponseNode.childNodes().at(0).toElement().QDomElement::text();
//        QString etag = singleResponseNode.childNodes().at(1).childNodes().at(0).childNodes().at(0).toElement().QDomElement::text();
//        QString calenderData = singleResponseNode.childNodes().at(1).childNodes().at(0).childNodes().at(2).toElement().QDomElement::text();
//        qDebug() << URL;
//        qDebug() << calenderData;
//    }


//    QDomNodeList todos = doc.elementsByTagName("d:prop");
//    qDebug() << "Number of ToDos:" << todos.count();
//    for(int x = 0; x < todos.count(); x++) {
//        QDomNode root = todos.at(x);
////        debugMessage(root.nodeName().toUtf8() + " has " + root.childNodes().count() + " childnodes");
//        for(int y = 0; y < root.childNodes().count(); y++) {
//            QDomNode node = root.childNodes().at(y);
////            debugMessage(node.nodeName().toUtf8() + ":\n" + node.toElement().QDomElement::text());
//            if(node.nodeName().toUtf8() == "cal:calendar-data" && node.toElement().QDomElement::text().contains("BEGIN:VTODO")) {
//                parseIcs(node.toElement().QDomElement::text());
//            }
//        }
//    }

}

QMap<QString, QString> MainWindow::NodeRunner(QDomNode Node)
{
    QMap<QString, QString> values;
    QString currentNodeName = Node.nodeName().toUtf8();
    qDebug() << "Current Node Name:" << currentNodeName;
    if(currentNodeName == "d:href" || currentNodeName == "d:getetag" || currentNodeName == "cal:calendar-data") {
        values.insert(currentNodeName, Node.toElement().QDomElement::text());
    }
    qDebug() << "Node" << currentNodeName << "has" << Node.childNodes().count() << "children";
    for (int x = 0; x < Node.childNodes().count(); x++) {
        values.unite(NodeRunner(Node.childNodes().at(x)));
    }
    return(values);
}
