#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::icsToTable(QString fullText) {
    QStringList lines = fullText.split("\n");
    QStringList headers;
    int index = 0;
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
