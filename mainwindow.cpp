#include "mainwindow.h"
#include "ui_mainwindow.h"
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_todo_entry(EntryClass entry)
{
    QListWidgetItem *tempItem = new QListWidgetItem(entry.get_key_value("SUMMARY"), ui->listWidget);
    tempItem->setFlags(tempItem->flags() | Qt::ItemIsUserCheckable);
    tempItem->setCheckState((entry.is_completed())?Qt::Checked:Qt::Unchecked);
    ui->listWidget->addItem(tempItem);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionGet_ToDo_s_from_Server_triggered()
{
    buildRequest("get_todo_list");
}

void MainWindow::onListWidgetlItemClicked(QListWidgetItem* listItem)
{
    EntryClass *entry = todoList[ui->listWidget->row(listItem)];
    ui->checkBox->setChecked(entry->is_completed());
    ui->lineEdit_summary->setText(entry->get_key_value("SUMMARY"));
    ui->textEdit_description->setPlainText(entry->get_key_value("DESCRIPTION"));
}

void MainWindow::on_pushButton_SaveChanges_clicked()
{
    EntryClass *entry = todoList[ui->listWidget->currentRow()];
    entry->edit_key_value("DESCRIPTION",ui->textEdit_description->toPlainText());
    entry->edit_key_value("SUMMARY",ui->lineEdit_summary->text());
    entry->set_completion(ui->checkBox->isChecked());
    sendUpdates("https://nextcloud.timesinks.de" + entry->get_href(), entry->get_etag(), entry->get_ics());
}

void MainWindow::refresh_View()
{
    ui->listWidget->clear();
    foreach (EntryClass *entry, todoList) {
        add_todo_entry(*entry);
    }
}

void MainWindow::on_pushButton_clicked()
{
    on_actionGet_ToDo_s_from_Server_triggered();
}
