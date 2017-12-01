#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entryclass.h"

EntryClass::EntryClass()
{
    qDebug() << "EntryClass created";
}

void EntryClass::fillIcsData(QString icsData)
{
    // RFC 5545: 3.1. -> requires long lines to be folded. Unfold them here
    icsData.replace("\n ", "");

    QStringList icsFields = icsData.split("\n");
    foreach (QString entry, icsFields) {
        QStringList keyAndValue = entry.split(":");
        QString key = keyAndValue[0];
        keyAndValue.removeFirst();
        QString value = keyAndValue.join(":");
        values[key] = value;
    }
    if(values.contains("UID")) {
//        todoList[values["UID"]] = values;
    }
}

void EntryClass::setEtag(QString etagValue)
{
    this->etag = etagValue;
}

QString EntryClass::returnIcs()
{
    QStringList keysAndValues;
    foreach (QString key, this->values.keys()) {
        keysAndValues << key + ":" + this->values[key];
    }
    return(keysAndValues.join("\n"));
}

QString EntryClass::returnKeyValue(QString key)
{
    if(this->values.keys().contains(key)) {
        return this->values[key];
    }
    else {
        qDebug() << "Error: Key" << key << "doesn't exist for entry" << this->returnKeyValue("SUMMARY");
        return("");
    }
}

int EntryClass::editKeyValue(QString key, QString value)
{
    if(this->values.keys().contains(key)) {
        this->values[key] = value;
        return 1;
    }
    else {
        qDebug() << "Error: Key doesn't exist";
        return -1;
    }
}
