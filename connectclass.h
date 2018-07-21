#ifndef CONNECTCLASS_H
#define CONNECTCLASS_H

#include <QObject>
#include <QDebug>
#include <QDomElement>

class ConnectClass : public QObject
{
    Q_OBJECT

public:
    explicit ConnectClass(QObject *parent = 0);
    bool get_lists();
    bool get_list();
    bool get_updates();
    bool send_edits(QString edited_entries);
protected:
    QDomDocument doc;
    QDomElement propfind = doc.createElement("d:propfind");
    QDomElement prop = doc.createElement("d:prop");
    QDomElement displayname = doc.createElement("d:displayname");
    QDomElement getctag = doc.createElement("cs:getctag");
    QDomElement calendar_query = doc.createElement("c:calendar-query");
    QDomElement getetag = doc.createElement("d:getetag");
    QDomElement getlastmodified = doc.createElement("d:getlastmodified");
    QDomElement calendar_data = doc.createElement("c:calendar-data");
    QDomElement filter = doc.createElement("c:filter");
    QDomElement comp_filter = doc.createElement("c:comp-filter");
    QDomElement comp_filter2 = doc.createElement("c:comp-filter");
};

#endif // CONNECTCLASS_H
