#ifndef TODOLISTCLASS_H
#define TODOLISTCLASS_H

#include "mainwindow.h"

class todoListClass
{
public:
    todoListClass();
private:
    QVector<EntryClass> mainList;
    QVector<QString> uidList;
    QVector<QString> etagList;
public slots:
    void entry_createNew();
    void entry_modify();
    void entry_delete();
    void list_getFromServer();
    void list_refreshFromServer();
    void list_clear();
};

#endif // TODOLISTCLASS_H
