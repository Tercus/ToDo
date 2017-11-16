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

    ui->groupBox->setHidden(true);

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

void MainWindow::on_pushButton_parse_clicked()
{
    debugMessage("populating the table");
    icsToTable(ui->plainTextEdit->toPlainText());
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
    debugMessage("Filling plainTextField with demo ics file.");
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
    debugMessage("Using data from table to view them nicely");
    ui->listWidget->clear();
    QStringList tableHeaders;
    for(int x = 0; x < ui->tableWidget->columnCount(); x++) {
        tableHeaders << ui->tableWidget->horizontalHeaderItem(x)->text();
    }
    for (int var = 0; var < ui->tableWidget->rowCount(); var++) {
        ui->listWidget->addItem(ui->tableWidget->item(var,tableHeaders.indexOf("SUMMARY"))->text());
    }
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem*)
{
    QStringList tableHeaders;
    for(int x = 0; x < ui->tableWidget->columnCount(); x++) {
        tableHeaders << ui->tableWidget->horizontalHeaderItem(x)->text();
    }
    // unhide the groupbox and show more detailed information (currently gets it from the tablewidget)
    ui->groupBox->setHidden(false);
    if(ui->tableWidget->item(ui->listWidget->currentRow(), tableHeaders.indexOf("SUMMARY"))) {
        ui->lineEdit_summary->setText(ui->tableWidget->item(ui->listWidget->currentRow(), tableHeaders.indexOf("SUMMARY"))->text());
    }
    else {
        ui->lineEdit_summary->setText("");
    }
    if(ui->tableWidget->item(ui->listWidget->currentRow(), tableHeaders.indexOf("DESCRIPTION"))) {
        ui->textEdit_description->setText(ui->tableWidget->item(ui->listWidget->currentRow(), tableHeaders.indexOf("DESCRIPTION"))->text());
    }
    else {
        ui->textEdit_description->setText("");
    }
}

void MainWindow::on_pushButton_closeView_clicked()
{
    ui->groupBox->setHidden(true);
}

void MainWindow::on_pushButton_getCalendarList_clicked()
{
    buildRequest("get_calendar_list");
}

void MainWindow::debugMessage(QString message)
{
    if(debugMode) {
        ui->debugField->setPlainText(ui->debugField->toPlainText() + message + "\n");
    }
}

void MainWindow::on_pushButton_getTodoList_clicked()
{
    buildRequest("get_todo_list");
}
