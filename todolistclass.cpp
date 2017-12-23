#include "todolistclass.h"

todoListClass::todoListClass(QObject *parent) : QObject(parent)
{
    standardVar = "Standard Value";
}

void todoListClass::testmessage()
{
    qDebug() << "Does this work?" << standardVar;
}

void todoListClass::testmessage(bool)
{
    qDebug() << "Was this everything?!";
}
