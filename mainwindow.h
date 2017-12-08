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
    void onListWidgetlItemClicked(QListWidgetItem *listItem);
    void on_actionGet_ToDo_s_from_Server_triggered();
    void on_pushButton_test_clicked();
    void on_pushButton_SaveChanges_clicked();

    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

public slots:
    void requestFinished(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    bool debugMode;
    QVector<EntryClass *> todoList;

    void icsToTable(QString fullText);
    QString requestBody(QString requestType);
    void buildRequest(QString requestType);
    QString createAuth();
    void importFile(QString path);
    void sendUpdates(QString url, QString etag, QString ics);
    QMap<QString, QString> NodeRunner(QDomNode Node);
    QStringList split_ics(QString icsValue);
    void add_todo_entry(EntryClass entry);
};


#endif // MAINWINDOW_H
