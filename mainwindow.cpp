#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entryclass.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMultiMap>
#include <QMap>

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
    importFile(file_name);
}

void MainWindow::on_actionDemo_Data_triggered()
{
    debugMessage("Using demo ics file.");
    importFile(":/exampleData/data/tasks.ics");
}

void MainWindow::importFile(QString path)
{
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::information(this, "Title", "File not opened");
    }
    else {
        QTextStream in(&file);
        QString text = in.readAll();
        parseIcs(text);
        file.close();
    }
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
    ui->lineEdit_summary->setText(list[ui->listWidget->currentRow()]->returnKeyValue("SUMMARY"));
    ui->textEdit_description->setText(list[ui->listWidget->currentRow()]->returnKeyValue("DESCRIPTION"));
}

void MainWindow::debugMessage(QString message)
{
    if(debugMode) {
        ui->debugField->appendPlainText(message + "\n");
    }
}

void MainWindow::on_pushButton_clicked()
{

}
