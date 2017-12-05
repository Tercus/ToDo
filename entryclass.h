#ifndef ENTRYCLASS_H
#define ENTRYCLASS_H

#include "mainwindow.h"

class EntryClass
{
public:
    EntryClass(QString etagValue, QString hrefValue, QString icsValue);
    QString returnIcs();
    QString returnKeyValue(QString key);
    int editKeyValue(QString key, QString newValue);
    void setEtag(QString etagValue);
    QString returnEtag();
    QString returnHref();
    int addKeyValue(QString newKey, QString newValue);
private:
    QString etag;
    QString href;
    QVector<QString> keys;
    QVector<QString> values;
    int flagEdited;
    void fillIcsData(QString icsData);
};

#endif // ENTRYCLASS_H
