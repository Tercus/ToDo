#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void onListWidgetlItemClicked(QListWidgetItem *);

    void on_actionImport_ToDo_s_triggered();

    void on_actionDemo_Data_triggered();

    void on_actionGet_ToDo_s_from_Server_triggered();

    void on_actionGet_Calendars_from_Server_triggered();

public slots:
    void requestFinished(QNetworkReply *reply);

private:
    bool debugMode;
    Ui::MainWindow *ui;

    void icsToTable(QString fullText);
    void debugMessage(QString message);
    QString requestBody(QString requestType);
    void buildRequest(QString requestType);
    QString createAuth();
    QString getValueFromIcs(QString fullText, QString searchvalue);
    QString changeValueInIcs(QString fullText, QString searchValue, QString newValue);
    QString insertValueInIcs(QString fullText, QString searchValue, QString newValue);
    void parseIcs(QString fullText);
};


#endif // MAINWINDOW_H
