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

    void on_pushButton_parse_clicked();

    void on_pushButton_openFile_clicked();

    void on_pushButton_demo_clicked();

    void on_pushButton_beautify_clicked();

    void onListWidgetlItemClicked(QListWidgetItem *);

    void on_pushButton_closeView_clicked();

    void on_pushButton_getCalendarList_clicked();

    void on_pushButton_getTodoList_clicked();

public slots:
    void requestFinished(QNetworkReply *reply);

private:
    bool debugMode;
    Ui::MainWindow *ui;

    void icsToTable(QString fullText);
    void debugMessage(QString message);
    QString requestBody(QString requestType);
    void buildRequest(QUrl url, QString username, QString password, QString requestType);
};


#endif // MAINWINDOW_H
