#include "todolistclass.h"

todoListClass::todoListClass(QObject *parent) : QObject(parent)
{
    qDebug() << "New todolist has been created.";
}

void todoListClass::entry_new()
{
    qDebug() << "Call for new entry.";
}

void todoListClass::entry_edit()
{
    qDebug() << "Call for entry edit.";
}

void todoListClass::entry_delete()
{
    qDebug() << "Call for entry delete.";
}

void todoListClass::list_get()
{
//    get the complete list of TODOs. This includes etags and their last modified timestamps.

//    create this DOM document:
//    <c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\">
//        <d:prop>
//            <d:getetag />
//            <d:getlastmodified />
//            <c:calendar-data />
//        </d:prop>
//        <c:filter>
//            <c:comp-filter name=\"VCALENDAR\">
//                <c:comp-filter name=\"VTODO\" />
//            </c:comp-filter>
//        </c:filter>
//    </c:calendar-query>
    qDebug() << "Button pressed to get full list from server.";

    doc.appendChild(calendar_query);
        calendar_query.setAttribute("xmlns:d", "DAV:");
        calendar_query.setAttribute("xmlns:c", "urn:ietf:params:xml:ns:caldav");
    calendar_query.appendChild(prop);
    prop.appendChild(getetag);
    prop.appendChild(getlastmodified);
    prop.appendChild(calendar_data);
    calendar_query.appendChild(filter);
    filter.appendChild(comp_filter);
        comp_filter.setAttribute("name", "VCALENDAR");
    comp_filter.appendChild(comp_filter2);
        comp_filter2.setAttribute("name", "VTODO");

    qDebug() << "using following body:";
    qDebug() << doc.toByteArray(4);

    Request *transmitter = new Request;
    connect(&transmitter->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
//    transmitter->set_request_method("REPORT");
//    transmitter->set_body(doc.toByteArray(4));
    transmitter->send_request("REPORT", doc.toByteArray(4));
}

void todoListClass::list_update()
{
    qDebug() << "Call for checking the list for updates.";
//    get a list of etags. Comparing etags quickly allows to check if the local data is still up to date.
//    -> Changed/Added entries have new etags

//    create this DOM document:
//    <c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\">
//        <d:prop>
//            <d:getetag />
//        </d:prop>
//        <c:filter>
//            <c:comp-filter name=\"VCALENDAR\">
//                <c:comp-filter name=\"VTODO\" />
//            </c:comp-filter>
//        </c:filter>
//    </c:calendar-query>

    doc.appendChild(calendar_query);
        calendar_query.setAttribute("xmlns:d", "DAV:");
        calendar_query.setAttribute("xmlns:c", "urn:ietf:params:xml:ns:caldav");
    calendar_query.appendChild(prop);
    prop.appendChild(getetag);
    calendar_query.appendChild(filter);
    filter.appendChild(comp_filter);
            comp_filter.setAttribute("name", "VCALENDAR");
        comp_filter.appendChild(comp_filter2);
            comp_filter2.setAttribute("name", "VTODO");

    qDebug() << doc.toByteArray(4);
}

void todoListClass::list_clear()
{
    qDebug() << "Call for clearing the list.";
}

void todoListClass::requestFinished(QNetworkReply *reply)
{
    qDebug() << "Request got a reply:" << reply;
    QUrl url = reply->url();
    QString urlPath = url.path();
    QString replyText = reply->readAll();
    qDebug() << url;

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Darnit, something went wrong: Error" << QString::number(reply->error()) << "from url" << url.toString();
        qDebug() << reply->errorString();
    }

    if(urlPath.endsWith(".ics")) {
        // Most likely a reply from editing a task
    }
    else if(replyText.contains("BEGIN:VTODO")) {
        // Most likely reply from getting a whole list of TODOs

        QDomDocument doc;
        doc.setContent(replyText);
        QDomNodeList responseNodes = doc.elementsByTagName("d:response");

        for(int x = 0; x < responseNodes.count(); x++) {
            QMap<QString, QString> node = NodeRunner(responseNodes.at(x));

            // Creating a new Entry object and adding it to the todoList
//            EntryClass *tempEntry = new EntryClass;
//            tempEntry->set_etag(node.value("d:getetag"));
//            tempEntry->set_href(node.value("d:href"));
//            tempEntry->set_ics(node.value("cal:calendar-data"));

//            todoList.push_back(tempEntry);

            // adding the entry to the listwidget
//            add_todo_entry(*tempEntry);
            qDebug() << node.value("cal:calendar-data");
        }
    }
}

QMap<QString, QString> todoListClass::NodeRunner(QDomNode Node)
{
    QMap<QString, QString> values;
    QString currentNodeName = Node.nodeName().toUtf8();
    if(currentNodeName == "d:href" || currentNodeName == "d:getetag" || currentNodeName == "cal:calendar-data") {
        values.insert(currentNodeName, Node.toElement().QDomElement::text());
//        qDebug() << Node.toElement().QDomElement::text();
    }
    for (int x = 0; x < Node.childNodes().count(); x++) {
        values.unite(NodeRunner(Node.childNodes().at(x)));
    }
    return(values);
}
