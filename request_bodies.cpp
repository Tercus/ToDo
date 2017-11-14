#include "mainwindow.h"
#include "ui_mainwindow.h"


QString MainWindow::requestBody(QString bodyType)
{
    QString bodyContent;

    if(bodyType == "get_ctag") {
        bodyContent = "<d:propfind xmlns:d=\"DAV:\" "
                      "xmlns:cs=\"http://sabredav.org/ns\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\"> \
                      <d:prop> \
                         <d:resourcetype /> \
                         <d:displayname /> \
                         <cs:getctag /> \
                         <c:supported-calendar-component-set /> \
                      </d:prop> \
                    </d:propfind>";
    }
    else if(bodyType == "test") {
        bodyContent = "Nothing but a little test";
    }
    return bodyContent;
}
