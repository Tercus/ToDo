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
    QString textToParse = ui->plainTextEdit->toPlainText();
    if(textToParse.count("BEGIN:VTODO") > 1) {
        QStringList multipleTodo = textToParse.split("END:VTODO");
        foreach (QString singleTodo, multipleTodo) {
            if(singleTodo.contains("BEGIN:VTODO")) {
                icsToTable(singleTodo + "END:VTODO");
            }
        }
    }
    else if(textToParse.count("BEGIN:VTODO") == 1) {
        icsToTable(textToParse);
    }
    else {
        debugMessage("The provided Text does not contain any ToDo's. Please check your file.");
    }
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
    for (int var = 0; var < ui->tableWidget->rowCount(); var++) {
        ui->listWidget->addItem(ui->tableWidget->item(var,1)->text());
    }
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem*)
{
    // unhide the groupbox and show more detailed information (currently gets it from the tablewidget)
    ui->groupBox->setHidden(false);

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
