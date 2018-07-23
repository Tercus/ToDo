#ifndef TODOLISTCLASS_H
#define TODOLISTCLASS_H

#include <QObject>
#include <QDebug>
#include "connectclass.h"

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

public slots:
    void entry_new();       // create a new entry (new task)
    void entry_edit();      // edit an existing entry
    void entry_delete();    // delete an existing entry
    void list_get();        // get full list from Server
    void list_update();     // only get etags from server (to check for updates)
    void list_clear();      // clear the list (eg. to re-init)
};

#endif // TODOLISTCLASS_H
