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
                EntryClass *tempEntry = new EntryClass;
                tempEntry->fillIcsData(singleTodo + "END:VTODO");
                todoList.push_back(tempEntry);
                ui->listWidget->addItem(tempEntry->returnKeyValue("SUMMARY"));
            }
        }
    }
    else if(fullText.count("BEGIN:VTODO") == 1) {
        EntryClass *tempEntry = new EntryClass;
        tempEntry->fillIcsData(fullText);
        todoList.push_back(tempEntry);
        ui->listWidget->addItem(tempEntry->returnKeyValue("SUMMARY"));
    }
    else {
        debugMessage("The provided Text does not contain any ToDo's. Please check your file.");
    }
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
