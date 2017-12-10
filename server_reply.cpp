#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomElement>

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString urlPath = url.path();
    QString replyText = reply->readAll();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Darnit, something went wrong: Error" << QString::number(reply->error()) << "from url" << url.toString();
        qDebug() << reply->errorString();
    }

    if(urlPath.endsWith(".ics")) {
        // Most likely a reply from editing a task
        todoList[ui->listWidget->currentRow()]->set_etag(reply->rawHeader("ETag"));
        refresh_View();
    }
    else if(replyText.contains("BEGIN:VTODO")) {
        QDomDocument doc("mydocument");
        doc.setContent(replyText);
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
            add_todo_entry(*tempEntry);
        }
    }
}

QMap<QString, QString> MainWindow::NodeRunner(QDomNode Node)
{
    QMap<QString, QString> values;
    QString currentNodeName = Node.nodeName().toUtf8();
    if(currentNodeName == "d:href" || currentNodeName == "d:getetag" || currentNodeName == "cal:calendar-data") {
        values.insert(currentNodeName, Node.toElement().QDomElement::text());
    }
    for (int x = 0; x < Node.childNodes().count(); x++) {
        values.unite(NodeRunner(Node.childNodes().at(x)));
    }
    return(values);
}



//############################
// Example response node
//############################
//    d:response
//     |-> d:href
//     |-> d:propstat
//          |-> d:prop
//               |-> d:getetag
//               |-> d:getlastmodified
//               |-> c:calender-data
//          |-> d:status
