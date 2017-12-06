#ifndef ENTRYCLASS_H
#define ENTRYCLASS_H

#include "mainwindow.h"

class EntryClass
{
public:
    EntryClass();
    QString get_ics();
    QString get_key_value(QString key);
    int edit_key_value(QString key, QString newValue);
    void set_etag(QString etagValue);
    QString get_etag();
    QString get_href();
    int add_key_value(QString newKey, QString newValue);
    void set_href(QString hrefValue);
    void set_ics(QString icsValue);
private:
    QString etag;
    QString href;
    QVector<QString> keys;
    QVector<QString> values;
    int flagEdited;
    void extract_ics(QString icsValue);
};

#endif // ENTRYCLASS_H
