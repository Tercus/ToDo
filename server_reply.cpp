#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomElement>

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString urlPath = url.path();
    QString text = reply->readAll();
//    debugMessage("Got following reply from " + urlPath + ":");
//    debugMessage(text);

    if (reply->error() != QNetworkReply::NoError) {
        debugMessage("Darnit, something went wrong: \n Error " + QString::number(reply->error()) + " from url " + url.toString() + ": " + reply->errorString());
    }


    QDomDocument doc("mydocument");
    doc.setContent(text);
//    debugMessage(doc.toString(4));

    QDomNodeList todos = doc.elementsByTagName("d:prop");
    qDebug() << "Number of ToDos:" << todos.count();
    for(int x = 0; x < todos.count(); x++) {
        QDomNode root = todos.at(x);
//        debugMessage(root.nodeName().toUtf8() + " has " + root.childNodes().count() + " childnodes");
        for(int y = 0; y < root.childNodes().count(); y++) {
            QDomNode node = root.childNodes().at(y);
//            debugMessage(node.nodeName().toUtf8() + ":\n" + node.toElement().QDomElement::text());
            if(node.nodeName().toUtf8() == "cal:calendar-data" && node.toElement().QDomElement::text().contains("BEGIN:VTODO")) {
                parseIcs(node.toElement().QDomElement::text());
//                icsToTable(node.toElement().QDomElement::text());
//                getValueFromIcs(node.toElement().QDomElement::text(), "DESCRIPTION:");
            }
        }
    }

}
