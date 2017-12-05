#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entryclass.h"

EntryClass::EntryClass(QString etagValue, QString hrefValue, QString icsValue)
{
    qDebug() << "EntryClass created";
    etag = etagValue;
    href = hrefValue;
    this->fillIcsData(icsValue);
}

void EntryClass::fillIcsData(QString icsData)
{
    // RFC 5545: 3.1. -> requires long lines to be folded. Unfold them here
    icsData.replace("\n ", "");

    // Each line *must* be a new key-value pair.
    // Splitting at \n ignores \\n inside of multiline-text
    QStringList icsFields = icsData.split("\n");
    foreach (QString entry, icsFields) {
        QStringList keyAndValue = entry.split(":");
        this->keys.append(keyAndValue[0]);
        keyAndValue.removeFirst();
        this->values.append(keyAndValue.join(":"));
    }
}

void EntryClass::setEtag(QString etagValue)
{
    this->etag = etagValue;
}

QString EntryClass::returnEtag()
{
    return etag;
}

QString EntryClass::returnHref()
{
    return href;
}

QString EntryClass::returnIcs()
{
    QStringList keysAndValues;
    for(int x = 0; x < this->keys.size(); x++) {
        keysAndValues << this->keys.value(x) + ":" + this->values.value(x);
    }
    return(keysAndValues.join("\n"));
}

QString EntryClass::returnKeyValue(QString key)
{
    if(this->keys.contains(key)) {
        return this->values.value(this->keys.indexOf(key));
    }
    else {
        qDebug() << "Error: Key"
                 << key
                 << "doesn't exist for entry"
                 << this->returnKeyValue("SUMMARY");
        return("");
    }
}

int EntryClass::editKeyValue(QString key, QString newValue)
{
    if(this->keys.contains(key)) {
        this->values[this->keys.indexOf(key)] = newValue;
        this->flagEdited = 1;
        return 1;
    }
    else {
        qDebug() << "Error: Key doesn't exist";
        return -1;
    }
}

int EntryClass::addKeyValue(QString newKey, QString newValue)
{
    if(this->keys.contains(newKey)) {
        this->values[this->keys.indexOf(newKey)] = newValue;
        this->flagEdited = 1;
        return 1;
    }
    else {
        this->keys.insert(this->keys.indexOf("SUMMARY"), newKey);
        this->values.insert(this->keys.indexOf(newKey), newValue);
        return 1;
    }
}
