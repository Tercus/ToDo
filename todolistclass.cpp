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
    qDebug() << "Button pressed to get full list from server.";
    ConnectClass *newConnect = new ConnectClass;
    newConnect->get_list();
}

void todoListClass::list_update()
{
    qDebug() << "Call for checking the list for updates.";
}

void todoListClass::list_clear()
{
    qDebug() << "Call for clearing the list.";
}
