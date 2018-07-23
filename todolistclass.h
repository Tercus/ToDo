#ifndef TODOLISTCLASS_H
#define TODOLISTCLASS_H

#include <QObject>
#include <QDebug>
#include "request.h"

class todoListClass : public QObject
{
    Q_OBJECT

public:
    explicit todoListClass(QObject *parent = 0);

private:
    QString todoListName;
    QUrl sourceUrl;
    QVector<QString> entries;
    QVector<QString> uids;
    QVector<QString> etag;
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

public slots:
    void entry_new();       // create a new entry (new task)
    void entry_edit();      // edit an existing entry
    void entry_delete();    // delete an existing entry
    void lists_get();       // get available lists from server url [!!UNUSED!!]
    void list_get();        // get full list from Server
    void list_update();     // only get etags from server (to check for updates)
    void list_clear();      // clear the list (eg. to re-init)
};

#endif // TODOLISTCLASS_H
