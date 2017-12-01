#ifndef ENTRYCLASS_H
#define ENTRYCLASS_H

#include "mainwindow.h"

class EntryClass
{
public:
    EntryClass();
    QString returnIcs();
    QString returnKeyValue(QString key);
    int editKeyValue(QString key, QString value);
    void setEtag(QString etagValue);
    void fillIcsData(QString icsData);
private:
    QMap<QString, QString> valueMap;
    QString etag;
};

#endif // ENTRYCLASS_H
