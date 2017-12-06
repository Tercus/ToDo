#include "mainwindow.h"
#include "ui_mainwindow.h"

QStringList MainWindow::split_ics(QString icsValue)
{
    QStringList icsList;
    int firstBreak = icsValue.indexOf("BEGIN:VTODO");
    int secondBreak = icsValue.indexOf("BEGIN:VTODO", firstBreak + 10); //skip the actual first one
    int thirdBreak = icsValue.lastIndexOf("END:VTODO") + 10; // >END:VTODO\n< those are 10 characters

    // Everything before the first TODO entry
    QString leftPart = icsValue.left(firstBreak);
    // The whole of the first TODO entry
    QString juicyPart = icsValue.mid(firstBreak, secondBreak - firstBreak);
    // Everything after the end of the first TODO entry until the end of the last TODO entry
    QString leftoverPart = icsValue.mid(secondBreak, thirdBreak - secondBreak);
    // Everything after the last TODO entry
    QString endPart = icsValue.mid(thirdBreak);

    QString completeTodo = leftPart + juicyPart + endPart;
    QString restTodo = leftPart + leftoverPart + endPart;

    icsList << completeTodo;

    // juicy Part is not in restTodo if there is more than one TODO, so start recursive loop
    if(!restTodo.contains(juicyPart)){
        icsList << split_ics(restTodo);
    }
    return icsList;
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
