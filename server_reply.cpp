#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QString text = reply->readAll();
    debugMessage("Got following reply from Server:");
    debugMessage(text);
}
