#include "connectclass.h"

ConnectClass::ConnectClass(QObject *parent) : QObject(parent)
{
    qDebug() << "A new ConnectionClass object has been created";


//    propfind.setAttribute("xmlns:d", "DAV:");
//    getctag.setAttribute("xmlns:cs", "http://calendarserver.org/ns/");
//    calendar_query.setAttribute("xmlns:d", "DAV:");
//    calendar_query.setAttribute("xmlns:c", "urn:ietf:params:xml:ns:caldav");
//        comp_filter.setAttribute("name", "VCALENDAR");
//        comp_filter.setAttribute("name", "VTODO");
}

bool ConnectClass::get_lists()
{
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

bool ConnectClass::get_list(QString list_name)
{
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


    qDebug() << list_name;
    return false;
}

bool ConnectClass::get_updates()
{
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


    return false;
}

bool ConnectClass::send_edits(QString edited_entries)
{
    qDebug() << edited_entries;
    return false;
}
