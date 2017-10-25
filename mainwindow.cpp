#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_pushButton_table_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "", "*.ics");
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this,"Title","File not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    file.close();
}
