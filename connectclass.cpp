#include "connectclass.h"

ConnectClass::ConnectClass(QObject *parent) : QObject(parent)
{
    qDebug() << "A new ConnectionClass object has been created";
}

bool ConnectClass::get_lists()
{
//    connect to the server and ask for a list of all available lists for the specific user.
//    -> info can later be used to select and manage different lists. unused for now.

//    create this DOM document:
//    <d:propfind xmlns:d=\"DAV:\">
//        <d:prop>
//            <d:displayname/>
//            <cs:getctag xmlns:cs=\"http://calendarserver.org/ns/\"/>
//        </d:prop>
//    </d:propfind>

    doc.appendChild(propfind);
    propfind.appendChild(prop);
    prop.appendChild(displayname);
    prop.appendChild(getctag);
    getctag.setAttribute("xmlns:cs", "http://calendarserver.org/ns/");

    qDebug() << doc.toByteArray(4);

    return false;
}

bool ConnectClass::get_list()
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


    qDebug() << doc.toByteArray(4);
    return false;
}

bool ConnectClass::get_updates()
{
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

    return false;
}

bool ConnectClass::send_edits(QString edited_entries)
{
    qDebug() << edited_entries;
    return false;
}
