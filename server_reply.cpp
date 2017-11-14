#include "mainwindow.h"
#include "ui_mainwindow.h"

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

}
