#include "todolistclass.h"

todoListClass::todoListClass(QObject *parent) : QObject(parent)
{

}

void todoListClass::testmessage()
{
    qDebug() << "Does this work?";
}

void todoListClass::testmessage(bool)
{
    qDebug() << "Was this everything?!";
}
