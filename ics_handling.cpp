#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::icsToTable(QString fullText) {
    QString cutBeginning = fullText.mid(fullText.indexOf("BEGIN:VTODO"));
    QString cleanedText = cutBeginning.left(cutBeginning.lastIndexOf("END:VTODO")+9);
    QStringList lines = cleanedText.split("\n");

    foreach (QString text, lines) {
        int x = 0;
        if (!text.isEmpty())
        {
            // Add new row to table for each TODO item in the text
            if(text == "BEGIN:VTODO") {
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            }

            QStringList line = text.split(':');

            // If the table is empty, add first column, loop through existing columns and check if header already exists, add it if not
            if(ui->tableWidget->columnCount() == 0) {
                ui->tableWidget->setColumnCount(1);
                ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(line[0]));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(line[1]));
            }
            else {
                while(x < ui->tableWidget->columnCount()) {
                    if(ui->tableWidget->horizontalHeaderItem(x)->text() == line[0]) {
                        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, x, new QTableWidgetItem(line[1]));
                        break;
                    }
                    else if(x == ui->tableWidget->columnCount()-1 && ui->tableWidget->horizontalHeaderItem(x)->text() != line[0]) {
                        ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()+1);
                        ui->tableWidget->setHorizontalHeaderItem(x+1, new QTableWidgetItem(line[0]));
                        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, x+1, new QTableWidgetItem(line[1]));
                    }
                    x++;
                }
            }
        }
    }
}
