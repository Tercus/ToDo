#ifndef TODOLISTCLASS_H
#define TODOLISTCLASS_H

//#include "mainwindow.h"
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

private:
    QString standardVar;
};

#endif // TODOLISTCLASS_H
