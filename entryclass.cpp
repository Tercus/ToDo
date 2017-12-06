#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entryclass.h"

EntryClass::EntryClass()
{
    qDebug() << "EntryClass created";
}

void EntryClass::extract_ics(QString icsValue)
{
    // RFC 5545: 3.1. -> requires long lines to be folded. Unfold them here
    icsValue.replace("\n ", "");

    // Each line *must* be a new key-value pair.
    // Splitting at \n ignores \\n inside of multiline-text
    QStringList icsFields = icsValue.split("\n");
    foreach (QString entry, icsFields) {
        QStringList keyAndValue = entry.split(":");
        this->keys.append(keyAndValue[0]);
        keyAndValue.removeFirst();
        this->values.append(keyAndValue.join(":"));
    }
}

void EntryClass::set_ics(QString icsValue)
{
    extract_ics(icsValue);
}

void EntryClass::set_etag(QString etagValue)
{
    this->etag = etagValue;
}

void EntryClass::set_href(QString hrefValue)
{
    this->href = hrefValue;
}

QString EntryClass::get_etag()
{
    return etag;
}

QString EntryClass::get_href()
{
    return href;
}

QString EntryClass::get_ics()
{
    QStringList keysAndValues;
    for(int x = 0; x < this->keys.size(); x++) {
        keysAndValues << this->keys.value(x) + ":" + this->values.value(x);
    }
    return(keysAndValues.join("\n"));
}

QString EntryClass::get_key_value(QString key)
{
    if(this->keys.contains(key)) {
        return this->values.value(this->keys.indexOf(key));
    }
    else {
        qDebug() << "Error: Key" << key << "could not be found";
        return("");
    }
}

int EntryClass::edit_key_value(QString key, QString newValue)
{
    if(this->keys.contains(key)) {
        this->values[this->keys.indexOf(key)] = newValue;
        this->flagEdited = 1;
        return 1;
    }
    else {
        qDebug() << "Error:" << key << "didn't exist, so creating it.";
        this->add_key_value(key, newValue);
        return 1;
    }
}

int EntryClass::add_key_value(QString newKey, QString newValue)
{
    if(this->keys.contains(newKey)) {
        this->edit_key_value(newKey, newValue);
        return 1;
    }
    else {
        this->keys.insert(this->keys.indexOf("SUMMARY"), newKey);
        this->values.insert(this->keys.indexOf(newKey), newValue);
        return 1;
    }
}
