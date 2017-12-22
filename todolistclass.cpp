#include "todolistclass.h"

todoListClass::todoListClass()
{
    qDebug() << "new todoListClass object created";
}

// Creates a new Entry Object and stores it in internal QVector
void todoListClass::entry_createNew()
{
    qDebug() << "Supposed to create new EntryClass";
}

void todoListClass::entry_modify()
{
    qDebug() << "Supposed to modify an Entry";
}

void todoListClass::entry_delete()
{
    qDebug() << "Supposed to delete an Entry";
}

void todoListClass::list_getFromServer()
{
    qDebug() << "Supposed to get List from Server";
}

void todoListClass::list_refreshFromServer()
{
    qDebug() << "Supposed to refresh List from Server";
}

void todoListClass::list_clear()
{
    qDebug() << "Supposed to clear the list";
}
