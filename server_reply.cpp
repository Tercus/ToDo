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
    QList<QMap<QString, QString>> todoNodes;
    for(int x = 0; x < responseNodes.count(); x++) {
        todoNodes.append(NodeRunner(responseNodes.at(x)));
//        parseIcs(todoNodes.at(x).value("cal:calendar-data"));
        EntryClass *tempEntry = new EntryClass(todoNodes.at(x).value("d:getetag"),todoNodes.at(x).value("d:href"),todoNodes.at(x).value("cal:calendar-data"));
        todoList.push_back(tempEntry);

        addEntrytoList(tempEntry->returnKeyValue("SUMMARY"), ((tempEntry->returnKeyValue("STATUS") == "COMPLETED")?true:false));
    }
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
