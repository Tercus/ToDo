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
    for(int x = 0; x < responseNodes.count(); x++) {
        QMap<QString, QString> node = NodeRunner(responseNodes.at(x));

        // Creating a new Entry object and adding it to the todoList
        EntryClass *tempEntry = new EntryClass;
        tempEntry->set_etag(node.value("d:getetag"));
        tempEntry->set_href(node.value("d:href"));
        tempEntry->set_ics(node.value("cal:calendar-data"));
        todoList.push_back(tempEntry);

        // adding the entry to the listwidget
        add_todo_entry(tempEntry->get_key_value("SUMMARY"), ((tempEntry->get_key_value("STATUS") == "COMPLETED")?true:false));
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
