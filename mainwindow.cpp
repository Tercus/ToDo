#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(":/exampleData/data/tasks.ics");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this,"Title","File not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_pushButton_connect_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString server = ui->lineEdit_server->text();

    if(username == "" || password == "" || server == "") {
        QMessageBox::information(this,"Missing data","You have to fill out all the information");
    }

}

void MainWindow::on_pushButton_parse_clicked()
{
    QFile file(":/exampleData/data/tasks.ics");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this,"Title","File not open");
    }
    QTextStream in(&file);
    int index = 0;
    QMap<QString, QString> map;
    QList<QString> headers;

    while (!in.atEnd())
    {
        QString text = in.readLine();
        if (!text.isEmpty())
        {
            if(text == "BEGIN:VTODO") index++;

            if( text.contains("UID") ||
                text.contains("DTSTAMP") ||
                text.contains("DUE;VALUE=DATE") ||
                text.contains("LAST-MODIFIED") ||
                text.contains("PRIORITY") ||
                text.contains("SUMMARY") ||
                text.contains("DESCRIPTION")){
                QStringList line = text.split(':');
                if(!headers.contains(line[0])) {
                    // Add new header
                    headers << line[0];
                    ui->tableWidget->setColumnCount(headers.count());
                    ui->tableWidget->setHorizontalHeaderItem(headers.count()-1, new QTableWidgetItem(line[0]));
                }
                ui->tableWidget->setRowCount(index);
                ui->tableWidget->setItem(index-1, headers.indexOf(line[0]), new QTableWidgetItem(line[1]));

                QString name = QString("%1-%2").arg(line[0]).arg(index);
                map[name] = line[1];
            }
        }
    }
    index = 0;

//  Debug Output:
//    foreach (QString key, map.keys()) {
//        qDebug() << key << ":" << map.value(key);
//    }
//    qDebug() << headers;
    map.clear();

//###################################
//      Sample Data
//BEGIN             VTODO
//UID               20171022T222604Z-23706-1000-1952-2@tobias-PC-linux
//DTSTAMP           20171022T222604Z
//SUMMARY           with date
//DESCRIPTION       and a description
//DUE;VALUE=DATE    20171026
//PRIORITY          2
//SEQUENCE          1
//LAST-MODIFIED     20171022T222624Z
//END               VTODO
}

void MainWindow::on_pushButton_table_clicked()
{
//    for(int col = 0; col < ui->tableWidget->columnCount(); ++col){
//        qDebug() << ui->tableWidget->horizontalHeaderItem(col)->text();
//    }
}
