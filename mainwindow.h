#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtNetwork/QNetworkReply>
#include <QDomElement>
#include "entryclass.h"
#include "todolistclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ui_add_entry(EntryClass entry);

private slots:
    void on_actionExit_triggered();
    void onListWidgetlItemClicked(QListWidgetItem *listItem);
    void on_actionGet_ToDo_s_from_Server_triggered();
    void on_pushButton_SaveChanges_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QVector<EntryClass *> todoList;
    todoListClass a;

    void icsToTable(QString fullText);
    QString requestBody(QString requestType);
    void buildRequest(QString requestType);
    QString createAuth();
    void importFile(QString path);
    void sendUpdates(QString url, QString etag, QString ics);
    QMap<QString, QString> NodeRunner(QDomNode Node);
    QStringList split_ics(QString icsValue);
    void refresh_View();
};


#endif // MAINWINDOW_H
