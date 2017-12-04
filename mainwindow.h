#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtNetwork/QNetworkReply>
#include <QDomElement>
#include "entryclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void debugMessage(QString message);

private slots:
    void on_actionExit_triggered();

    void onListWidgetlItemClicked(QListWidgetItem *);

    void on_actionImport_ToDo_s_triggered();

    void on_actionDemo_Data_triggered();

    void on_actionGet_ToDo_s_from_Server_triggered();

    void on_actionGet_Calendars_from_Server_triggered();

    void on_pushButton_clicked();

    void on_pushButton_SaveChanges_clicked();

public slots:
    void requestFinished(QNetworkReply *reply);

private:
    bool debugMode;
    QVector<EntryClass *> todoList;
    Ui::MainWindow *ui;

    void icsToTable(QString fullText);
    QString requestBody(QString requestType);
    void buildRequest(QString requestType);
    QString createAuth();
    void parseIcs(QString fullText);
    void importFile(QString path);
    void sendUpdates(QString URL, QString UID, QString ics);
    QMap<QString, QString> NodeRunner(QDomNode Node);
};


#endif // MAINWINDOW_H
