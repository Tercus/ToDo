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
    connect(ui->listWidget,
            SIGNAL(itemClicked(QListWidgetItem*)),
            this,
            SLOT(onListWidgetlItemClicked(QListWidgetItem*))
            );

    debugMode = true;
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

void MainWindow::on_actionImport_ToDo_s_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "", "*.ics");
    QFile file(file_name);
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream in(&file);
        QString text = in.readAll();
        parseIcs(text);
        file.close();
    }
}

void MainWindow::on_actionDemo_Data_triggered()
{
    debugMessage("Filling plainTextField with demo ics file.");
    QFile file(":/exampleData/data/tasks.ics");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this,"Title","File not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    parseIcs(text);
    file.close();
}

void MainWindow::on_actionGet_ToDo_s_from_Server_triggered()
{
    buildRequest("get_todo_list");
}

void MainWindow::on_actionGet_Calendars_from_Server_triggered()
{
    buildRequest("get_calendar_list");
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem*)
{
    if(ui->tableWidget->item(ui->listWidget->currentRow(), 1)) {
        ui->lineEdit_summary->setText(ui->tableWidget->item(ui->listWidget->currentRow(), 1)->text());
    }
    else {
        ui->lineEdit_summary->setText("");
    }
    if(ui->tableWidget->item(ui->listWidget->currentRow(), 2)) {
        ui->textEdit_description->setText(ui->tableWidget->item(ui->listWidget->currentRow(), 2)->text());
    }
    else {
        ui->textEdit_description->setText("");
    }
}

void MainWindow::debugMessage(QString message)
{
    if(debugMode) {
        ui->debugField->appendPlainText(message + "\n");
    }
}
