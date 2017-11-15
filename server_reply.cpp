#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomElement>

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString urlPath = url.path();
    debugMessage("Got following reply from " + urlPath + ":");

    QString text = reply->readAll();
    debugMessage(text);

    if (reply->error() != QNetworkReply::NoError) {
        debugMessage("Darnit, something went wrong: \n Error " + QString::number(reply->error()) + " from url " + url.toString() + ": " + reply->errorString());
    }




    QDomDocument doc("mydocument");
    doc.setContent(text);

    QDomNodeList todos = doc.elementsByTagName("d:prop");
    qDebug() << todos.count();
    for(int x = 0; x < todos.count(); x++) {
        QDomNode root = todos.at(x);
        qDebug() << root.nodeName().toUtf8() << "has" << root.childNodes().count() << "childnodes";
        for(int y = 0; y < root.childNodes().count(); y++) {
            QDomNode node = root.childNodes().at(y);
            qDebug() << node.nodeName().toUtf8() << ":" << node.toElement().QDomElement::text();
//            QString str;
//            QTextStream stream(&str);
//            node.save(stream, QDomNode::CDATASectionNode /* = 4 */);
//            qDebug() << str;
        }
    }

}
