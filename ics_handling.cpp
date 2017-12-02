#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::parseIcs(QString fullText)
{
    int firstBreak = fullText.indexOf("BEGIN:VTODO");
    int secondBreak = fullText.indexOf("BEGIN:VTODO", firstBreak + 10); //skip the actual first one
    int thirdBreak = fullText.lastIndexOf("END:VTODO") + 10; // >END:VTODO\n< those are 10 characters

    // Everything before the first TODO entry
    QString leftPart = fullText.left(firstBreak);

    // The whole of the first TODO entry
    QString juicyPart = fullText.mid(firstBreak, secondBreak - firstBreak);

    // Everything after the end of the first TODO entry until the end of the last TODO entry
    QString leftoverPart = fullText.mid(secondBreak, thirdBreak - secondBreak);

    // Everything after the last TODO entry
    QString endPart = fullText.mid(thirdBreak);

    QString completeTodo = leftPart + juicyPart + endPart;
    QString restTodo = leftPart + leftoverPart + endPart;

    // juicy Part is not in restTodo if there is more than one TODO, so start recursive loop
    if(!restTodo.contains(juicyPart)){
        parseIcs(restTodo);
    }

    // Create the entry and push into the main Todo-List
    EntryClass *tempEntry = new EntryClass;
    tempEntry->fillIcsData(completeTodo);
    todoList.push_back(tempEntry);

    // Add the newly created entry and add it to the listwidget
    QListWidgetItem *tempItem = new QListWidgetItem(tempEntry->returnKeyValue("SUMMARY"), ui->listWidget);
    tempItem->setFlags(tempItem->flags() | Qt::ItemIsUserCheckable);
    if(tempEntry->returnKeyValue("STATUS") == "COMPLETED") {
        tempItem->setCheckState(Qt::Checked);
    }
    else {
        tempItem->setCheckState(Qt::Unchecked);
    }
    ui->listWidget->addItem(tempItem);
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
