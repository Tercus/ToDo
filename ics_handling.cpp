#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::icsToTable(QString fullText)
{
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

QString MainWindow::getValueFromIcs(QString fullText, QString searchvalue)
{
    QStringList icsFields = fullText.split("\n");
    QStringList filtered_entries = icsFields.filter(searchvalue);
    if(filtered_entries.size() > 0) {
        QString fullEntry = icsFields.at(icsFields.indexOf(filtered_entries.at(0)));
        QStringList splitEntry = fullEntry.split(":");
        debugMessage("Following entry found for \"" + searchvalue + "\":\n" + splitEntry.at(1));
        return splitEntry.at(1);
    }
    debugMessage("Could not find specified entry \"" + searchvalue + "\" in the ics");
    return "";
}

QString MainWindow::changeValueInIcs(QString fullText, QString searchValue, QString newValue)
{
    QStringList icsFields = fullText.split("\n");
    QStringList filtered_entries = icsFields.filter(searchValue);
    if(filtered_entries.size() > 0) {
        int index = icsFields.indexOf(filtered_entries.at(0));
        QString fullEntry = icsFields.at(index);
        QStringList splitEntry = fullEntry.split(":");
        icsFields[index] = splitEntry[0] + ":" + newValue;
        debugMessage("Following entry found for \"" + searchValue + "\" from:\n" + splitEntry.at(1) + "\nto:\n" + newValue);
        return icsFields.join("\n");
    }
    debugMessage("Could not find specified entry \"" + searchValue + "\" in the ics.");
    return "";
}

QString MainWindow::insertValueInIcs(QString fullText, QString searchValue, QString newValue)
{
    QStringList icsFields = fullText.split("\n");
    QStringList filtered_entries = icsFields.filter(searchValue);
    if(filtered_entries.size() == 0) {
        int vtodoEnd = icsFields.indexOf("END:VTODO")-1;
        searchValue = searchValue.replace(":", "");
        icsFields.insert(vtodoEnd, searchValue + ":" + newValue);
        debugMessage("Following new entry added: \"" + searchValue + ":" + newValue + "\"");
        return icsFields.join("\n");
    }
    debugMessage("Could not add entry \"" + searchValue + ":" + newValue + "\" in the ics, as that entry already exists.");
    return "";
}


//#############################
//      Sample VTODO
//#############################
//    BEGIN:VCALENDAR
//    VERSION:2.0
//    PRODID:-//Nextcloud Tasks v0.9.5
//    BEGIN:VTODO
//    CREATED:20171116T011409
//    DTSTAMP:20171116T011447
//    LAST-MODIFIED:20171116T011447
//    UID:pc97f4hjce
//    SUMMARY:Fourth item completed
//    PRIORITY:0
//    PERCENT-COMPLETE:100
//    X-OC-HIDESUBTASKS:0
//    COMPLETED:20171116T011447
//    STATUS:COMPLETED
//    END:VTODO
//    END:VCALENDAR
