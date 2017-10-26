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
// This would make the have checkboxes, but sadly that does not work and makes them unclickable.
//        ui->listWidget->item(var)->setFlags(Qt::ItemIsUserCheckable);
//        ui->listWidget->item(var)->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem*)
{
    ui->groupBox->setHidden(false);
    QString summary = "";
    QString description = "";
    if(ui->tableWidget->item(ui->listWidget->currentRow(), 2)) summary = ui->tableWidget->item(ui->listWidget->currentRow(), 2)->text();
    if(ui->tableWidget->item(ui->listWidget->currentRow(), 4)) description = ui->tableWidget->item(ui->listWidget->currentRow(), 4)->text();
    ui->lineEdit_summary->setText(summary);
    ui->textEdit_description->setText(description);
}

void MainWindow::on_pushButton_closeView_clicked()
{
    ui->groupBox->setHidden(true);
}
