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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_todo_entry(QString entryName, bool completed)
{
    QListWidgetItem *tempItem = new QListWidgetItem(entryName, ui->listWidget);
    tempItem->setFlags(tempItem->flags() | Qt::ItemIsUserCheckable);
    tempItem->setCheckState((completed)?Qt::Checked:Qt::Unchecked);
    ui->listWidget->addItem(tempItem);

    QFrame *frame = new QFrame;
    QLabel *label1 = new QLabel("Summary:");
    QLineEdit *linedit = new QLineEdit(entryName);
    QLabel *label2 = new QLabel("Description:");
    QTextEdit *textedit = new QTextEdit();
    QPushButton *button = new QPushButton("Save changes");

    QVBoxLayout *box = new QVBoxLayout();
    box->addWidget(label1);
    box->addWidget(linedit);
    box->addWidget(label2);
    box->addWidget(textedit);
    box->addWidget(button);
    frame->setLayout(box);

    ui->toolBox->addItem(frame, entryName);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionGet_ToDo_s_from_Server_triggered()
{
    buildRequest("get_todo_list");
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem*)
{
    ui->lineEdit_summary->setText(todoList[ui->listWidget->currentRow()]->get_key_value("SUMMARY"));
    ui->textEdit_description->setText(todoList[ui->listWidget->currentRow()]->get_key_value("DESCRIPTION").replace("\\n", "\n"));
}

void MainWindow::debugMessage(QString message)
{
    if(debugMode) {
        ui->debugField->appendPlainText(message + "\n");
    }
}

void MainWindow::on_pushButton_test_clicked()
{
//    sendUpdates(QString URL, QString UID, QString ics);
    todoList.at(ui->listWidget->currentRow())->add_key_value("STATUS", "COMPLETED");
    QString url = "https://nextcloud.timesinks.de" + todoList.at(ui->listWidget->currentRow())->get_href();
    QString etag = todoList.at(ui->listWidget->currentRow())->get_etag();
    QString ics = todoList.at(ui->listWidget->currentRow())->get_ics();
    sendUpdates(url, etag, ics);
}

void MainWindow::on_pushButton_SaveChanges_clicked()
{
    todoList[ui->listWidget->currentRow()]->edit_key_value("DESCRIPTION",ui->textEdit_description->toPlainText());
    todoList[ui->listWidget->currentRow()]->edit_key_value("SUMMARY",ui->lineEdit_summary->text());
}

void MainWindow::on_pushButton_clicked()
{
    QFrame *frame1 = new QFrame;
    QLabel *label1 = new QLabel("Summary:");
    QLineEdit *linedit = new QLineEdit();
    QLabel *label2 = new QLabel("Description:");
    QTextEdit *textedit = new QTextEdit();
    QPushButton *button = new QPushButton("Save changes");

    QVBoxLayout *box = new QVBoxLayout();
    box->addWidget(label1);
    box->addWidget(linedit);
    box->addWidget(label2);
    box->addWidget(textedit);
    box->addWidget(button);
    frame1->setLayout(box);

    ui->toolBox->addItem(frame1, "Shabam");
}
