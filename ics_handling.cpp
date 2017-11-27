#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::parseIcs(QString fullText)
{
    // RFC 5545: 3.1. -> requires long lines to be folded. Unfold them here
    fullText.replace("\n ", "");

    if(fullText.count("BEGIN:VTODO") > 1) {
        QStringList multipleTodo = fullText.split("END:VTODO");
        foreach (QString singleTodo, multipleTodo) {
            if(singleTodo.contains("BEGIN:VTODO")) {
                icsToTable(singleTodo + "END:VTODO");
            }
        }
    }
    else if(fullText.count("BEGIN:VTODO") == 1) {
//        icsToTable(fullText);
        icsToMap(fullText);
    }
    else {
        debugMessage("The provided Text does not contain any ToDo's. Please check your file.");
    }
}

void MainWindow::icsToMap(QString fullText)
{
    QMap<QString, QString> values;
    QString UID;

    QStringList icsFields = fullText.split("\n");
    foreach (QString entry, icsFields) {
        QStringList keyAndValue = entry.split(":");
        QString key = keyAndValue[0];
        keyAndValue.removeFirst();
        QString value = keyAndValue.join(":");
        values[key] = value;
    }
    if(values.contains("UID")) {
        todoList[values["UID"]] = values;

        // Just for testing, adding to table to read out
        int newRow = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(newRow+1);
        if(values.contains("UID")) ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(values["UID"]));
        if(values.contains("COMPLETION")) ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(values["COMPLETION"]));
        if(values.contains("SUMMARY")) {
            ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(values["SUMMARY"]));
            ui->listWidget->addItem(values["SUMMARY"]);
        }
        if(values.contains("DESCRIPTION")) ui->tableWidget->setItem(newRow, 3, new QTableWidgetItem(values["DESCRIPTION"]));
        if(values.contains("DUE")) ui->tableWidget->setItem(newRow, 4, new QTableWidgetItem(values["DUE"]));
    }
}

void MainWindow::icsToTable(QString fullText)
{
    QString todoUID = getValueFromIcs(fullText, "UID:");
    QString todoCompletion = getValueFromIcs(fullText, "PERCENT-COMPLETE:");
    QString todoSummary = getValueFromIcs(fullText, "SUMMARY:");
    QString todoDescription = getValueFromIcs(fullText, "DESCRIPTION:");
    QString todoDue = getValueFromIcs(fullText, "DUE:");
    QString todoDuration = getValueFromIcs(fullText, "DURATION:");

    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(newRow+1);
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(todoUID));
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(todoCompletion));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(todoSummary));
    ui->tableWidget->setItem(newRow, 3, new QTableWidgetItem(todoDescription));
    ui->tableWidget->setItem(newRow, 4, new QTableWidgetItem(todoDue));
    ui->tableWidget->setItem(newRow, 5, new QTableWidgetItem(todoDuration));

    ui->listWidget->addItem(todoSummary);
}

QString MainWindow::getValueFromIcs(QString fullText, QString searchvalue)
{
    QStringList icsFields = fullText.split("\n");
    QStringList filtered_entries = icsFields.filter(searchvalue);
    if(filtered_entries.size() > 0) {
        QString fullEntry = icsFields.at(icsFields.indexOf(filtered_entries.at(0)));
        QStringList splitEntry = fullEntry.split(":");
        debugMessage("Following entry found for \"" + searchvalue + "\" -> " + splitEntry.at(1));
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
