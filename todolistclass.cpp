#include "todolistclass.h"

todoListClass::todoListClass(QObject *parent) : QObject(parent)
{

}

void todoListClass::entry_new()
{
    qDebug() << "Call for new entry";
//    ConnectClass new_connection;
}

void todoListClass::entry_edit()
{
    qDebug() << "Call for entry edit";
}

void todoListClass::entry_delete()
{
    qDebug() << "Call for entry delete";
}

void todoListClass::list_get()
{
    qDebug() << "Call for initializing list";
}

void todoListClass::list_check()
{
    qDebug() << "Call for checking the list for updates";
}

void todoListClass::list_clear()
{
    qDebug() << "Call for clearing the list";
}
