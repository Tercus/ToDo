#ifndef TODOLISTCLASS_H
#define TODOLISTCLASS_H

#include <QObject>
#include <QDebug>

class todoListClass : public QObject
{
    Q_OBJECT
public:
    explicit todoListClass(QObject *parent = 0);

public slots:
    void testmessage();
    void testmessage(bool);
};

#endif // TODOLISTCLASS_H
