#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QBuffer>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(onListWidgetlItemClicked(QListWidgetItem*)));
    ui->groupBox->setHidden(true);
//    ui->tableWidget->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_pushButton_parse_clicked()
{
    int index = 0;
    QStringList headers;
    QString plainTextEditContents = ui->plainTextEdit->toPlainText();
    QStringList lines = plainTextEditContents.split("\n");

    foreach (QString text, lines) {
        if (!text.isEmpty())
        {
            if(text == "BEGIN:VTODO") index++;

            if(text.contains("UID") ||
            text.contains("DTSTAMP") ||
            text.contains("DUE;VALUE=DATE") ||
            text.contains("LAST-MODIFIED") ||
            text.contains("PRIORITY") ||
            text.contains("SUMMARY") ||
            text.contains("DESCRIPTION")) {
                QStringList line = text.split(':');
                if(!headers.contains(line[0])) {
                    // Add new header
                    headers << line[0];
                    ui->tableWidget->setColumnCount(headers.count());
                    ui->tableWidget->setHorizontalHeaderItem(headers.count()-1, new QTableWidgetItem(line[0]));
                }
                ui->tableWidget->setRowCount(index);
                ui->tableWidget->setItem(index-1, headers.indexOf(line[0]), new QTableWidgetItem(line[1]));
            }
        }
    }
    index = 0;
}

void MainWindow::on_pushButton_openFile_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "", "*.ics");
    QFile file(file_name);
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&file);
        QString text = in.readAll();
        ui->plainTextEdit->setPlainText(text);
        file.close();
    }
}

void MainWindow::on_pushButton_demo_clicked()
{
    QFile file(":/exampleData/data/tasks.ics");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this,"Title","File not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}

void MainWindow::on_pushButton_beautify_clicked()
{
    for (int var = 0; var < ui->tableWidget->rowCount(); var++) {
        ui->listWidget->addItem(ui->tableWidget->item(var,2)->text());
    }
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem*)
{
    ui->groupBox->setHidden(false);
    QString summary = "";
    QString description = "";
    if(ui->tableWidget->item(ui->listWidget->currentRow(), 2)) summary = ui->tableWidget->item(ui->listWidget->currentRow(), 2)->text();
    if(ui->tableWidget->item(ui->listWidget->currentRow(), 3)) description = ui->tableWidget->item(ui->listWidget->currentRow(), 3)->text();
    ui->lineEdit_summary->setText(summary);
    ui->textEdit_description->setText(description);
}

void MainWindow::on_pushButton_closeView_clicked()
{
    ui->groupBox->setHidden(true);
}

void MainWindow::on_pushButton_serverConnect_clicked()
{
//    Set the main URL for the thingy
    QUrl url(ui->lineEdit_server->text());
    QNetworkRequest request(url);

//    Set the username and Password
    QString concatenated = ui->lineEdit_username->text() + ":" + ui->lineEdit_password->text();
    QByteArray data = concatenated.toLocal8Bit().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toLocal8Bit());

//    we set a user agent to prevent troubles with some Nextcloud server hosting providers
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9a3pre) Gecko/20070330");

//    build the request body
    QString body = "<d:propfind xmlns:d=\"DAV:\" "
            "xmlns:cs=\"http://sabredav.org/ns\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\"> \
            <d:prop> \
               <d:resourcetype /> \
               <d:displayname /> \
               <cs:getctag /> \
               <c:supported-calendar-component-set /> \
            </d:prop> \
          </d:propfind>";

//    acquire the size for the body to set in header
    QByteArray *dataToSend = new QByteArray(body.toUtf8());
    request.setHeader(QNetworkRequest::ContentLengthHeader, dataToSend->size());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QBuffer *buffer = new QBuffer(dataToSend);

//    Init new NAM and send the request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->sendCustomRequest(request, "PROPFIND", buffer);

//    Connect the NAM with the SLOT requestFinished
    connect(manager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(requestFinished(QNetworkReply*))
            );
}

void MainWindow::requestFinished(QNetworkReply *reply)
{
    QString text = reply->readAll();
    qDebug() << text;
    ui->plainTextEdit->setPlainText(text);
}
